
#include "main.h"
#include "hyperdog_uros_node.h"
#include "motor_typedefs.h"

hyperdogUROS_Node_t hyperdog_node;
hyperdog_uros_msgs__msg__MotorStates motor_states_;

/* ================================================================================== */
/*                             NODE INITIALIZATION                                    */
/* ================================================================================== */
void init_hyperdog_node()
{
    hyperdog_node.state = HYPERDOG_NODE_INITIALIZING;

    /*  1. initialize the node --------------------------------------------------------*/
    hyperdog_node.rcl_ret = rclc_node_init_default(
                            &hyperdog_node.node, 
                            "hyperdog_uros_node", 
                            "", 
                            &uros.support);

    /* 2. If no error, init executor --------------------------------------------------*/
    if(hyperdog_node.rcl_ret == RCL_RET_OK)
    {
        hyperdog_node.error_code &= ~NODE_HYPERDOG_ERROR_FAILED_INIT; //update error code

        hyperdog_node.rcl_ret = rclc_executor_init(
                                &hyperdog_node.executor,
                                &uros.support.context,
                                1,
                                &uros.allocator);
        
        /* 3. If no error, init node entities -------------------------------*/
        if(hyperdog_node.rcl_ret == RCL_RET_OK)
        {
            /* - init publishers ------------------------------*/
            _init_motors_states_publisher();


            /* - init subscribers -----------------------------*/


            /* - init services --------------------------------*/


            /* - init timers ----------------------------------*/


        }
        else
        {
            goto fail;
        }

    }
    else
    {
        hyperdog_node.state = HYPERDOG_NODE_ERROR;
        hyperdog_node.error_code |= NODE_HYPERDOG_ERROR_FAILED_INIT;

        /* check if rcl_support has no error ----------------------------------*/
        /// TODO: check rcl_support error, if error exist restartMicroROS()
        fail:
        restartMicroROS(); /// Assuming error ccured due to the agent is not connected
    }

}



/* ================================================================================== */
/*                         MOTORS STATES PUBLISHER                                    */
/* ================================================================================== */

/* ------------------------- INITIATE THE PUBLISHER ------------------------------ */
void _init_motors_states_publisher()
{
    /// TODO: best effort publisher gives rcl_ret 1 error no matter what.
    ///       Find a solution for it and implement the rclc_publisher_init_best_effort!
    ///       otherwise, withe the default publisher we get around 47 publishing rate.
    hyperdog_node.motorsStates_pub.rcl_ret
        = rclc_publisher_init_default(
            &hyperdog_node.motorsStates_pub.publisher,
            &hyperdog_node.node,
            ROSIDL_GET_MSG_TYPE_SUPPORT(hyperdog_uros_msgs, msg, MotorsStates),
            "motors_states"
            );

    if(hyperdog_node.motorsStates_pub.rcl_ret != RCL_RET_OK){
        hyperdog_node.state = HYPERDOG_NODE_ERROR;
        hyperdog_node.error_code |= NODE_HYPERDOG_ERROR_FAILED_PUB1;
        restartMicroROS();
    }
    else{
        hyperdog_node.error_code &= ~NODE_HYPERDOG_ERROR_FAILED_PUB1;
    }

    /// initialize timer callback       

    ///   * set timer period           
    hyperdog_node.motorsStates_pub.timer_period = MOTORS_STATES_PUB_TIMER_PERIOD_NS;

    ///   * initialize timer object    
    hyperdog_node.motorsStates_pub.rcl_ret 
        = rclc_timer_init_default(
            &hyperdog_node.motorsStates_pub.timer,
            &uros.support,
            hyperdog_node.motorsStates_pub.timer_period,
            _motors_states_timer_callback);

    ///   * Add to the executor        
    if(hyperdog_node.motorsStates_pub.rcl_ret == RCL_RET_OK){
        hyperdog_node.motorsStates_pub.rcl_ret 
            = rclc_executor_add_timer(
                &hyperdog_node.executor, 
                &hyperdog_node.motorsStates_pub.timer);

        if(hyperdog_node.motorsStates_pub.rcl_ret != RCL_RET_OK){
            hyperdog_node.state = HYPERDOG_NODE_ERROR;
            hyperdog_node.error_code |= NODE_HYPERDOG_ERROR_FAILED_PUB1;
        }
        else{hyperdog_node.error_code &= ~NODE_HYPERDOG_ERROR_FAILED_PUB1;}
    }
}

/* ------------------------ PUBLISHER CALLBACK -------------------------------------- */
void _motors_states_timer_callback(rcl_timer_t * timer, int64_t last_call_time)
{
    RCLC_UNUSED(last_call_time);

    if(timer != NULL) {
        /// update msg
        hyperdog_node.motorsStates_pub.msg.fr_hip_roll.feedback.id = 1;
        hyperdog_node.motorsStates_pub.msg.fr_hip_roll.feedback.position = 1.22434232;


        /// publish msg 
        hyperdog_node.motorsStates_pub.rcl_ret 
            = rcl_publish(
                &hyperdog_node.motorsStates_pub.publisher, 
                &hyperdog_node.motorsStates_pub.msg, 
                NULL);

        if(hyperdog_node.motorsStates_pub.rcl_ret  != RCL_RET_OK){
            hyperdog_node.error_code |= NODE_HYPERDOG_ERROR_FAILED_PUB1;
            restartMicroROS(); /// Assuming error ccured due to the connectiorn lost with the agent
        }
        else{
            hyperdog_node.error_code &= ~ NODE_HYPERDOG_ERROR_FAILED_PUB1;
        }
    }
    else{
        printf("timer is NULL");
    }
   
}



/* ================================================================================== */
/*                               DESTROY NODE                                         */
/* ================================================================================== */

/**
 * To destroy all the entities of the hyperdog_node and node itself
 */
void _destroy_hyperdog_node(){
    /// first, destroy all the node's entities 
    hyperdog_node.rcl_ret = rclc_executor_fini(&hyperdog_node.executor);
    hyperdog_node.rcl_ret += rcl_timer_fini(&hyperdog_node.motorsStates_pub.timer);
    hyperdog_node.rcl_ret += rcl_publisher_fini(
                             &hyperdog_node.motorsStates_pub.publisher,
                             &hyperdog_node.node);
    /// TODO: 

    /// then destroy the node itself
    hyperdog_node.rcl_ret = rcl_node_fini(&hyperdog_node.node);

}


