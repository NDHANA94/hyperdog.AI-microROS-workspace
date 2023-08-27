
#include "main.h"
#include "hyperdog_uros_node.h"
#include "motor_typedefs.h"

hyperdogUROS_Node_t hyperdog_node;
hyperdog_uros_msgs__msg__MotorStates motor_states_;

void init_hyperdog_node()
{
    hyperdog_node.state = HYPERDOG_NODE_INITIALIZING;

    /* initialize the node */
    hyperdog_node.rcl_ret = rclc_node_init_default(
                            &hyperdog_node.node, 
                            "hyperdog_uros_node", 
                            "", 
                            &uros.support);

    /* check error */
    if(hyperdog_node.rcl_ret != RCL_RET_OK){
        hyperdog_node.state = HYPERDOG_NODE_ERROR;
        hyperdog_node.error_code |= NODE_HYPERDOG_ERROR_FAILED_INIT;

        /* check if rcl_support has no error */
        /// TODO: check rcl_support error, if error exist resetMicroROS()

        // resetMicroROS(); 
    }
    /* if no error */
    hyperdog_node.error_code &= ~NODE_HYPERDOG_ERROR_FAILED_INIT;

    /* init publishers */
    _init_motors_state_publisher();


    /* init subscribers */


    /* init services */


    /* init timers */

}

void _init_motors_state_publisher()
{
    hyperdog_node.rcl_ret = rclc_publisher_init_default(
                            &hyperdog_node.motors_states_pub,
                            &hyperdog_node.node,
                            ROSIDL_GET_MSG_TYPE_SUPPORT(hyperdog_uros_msgs, msg, MotorsStates),
                            "motors_states"
                            );
    if(hyperdog_node.rcl_ret != RCL_RET_OK){
        hyperdog_node.state = HYPERDOG_NODE_ERROR;
        hyperdog_node.error_code |= NODE_HYPERDOG_ERROR_FAILED_PUB1;
    }
    else{
        hyperdog_node.error_code &= ~NODE_HYPERDOG_ERROR_FAILED_PUB1;

        motor_states_.leg.capacity = 2;
        motor_states_.leg.data = (char*) malloc(motor_states_.leg.capacity * sizeof(char));

        motor_states_.joint.capacity = 5;
        motor_states_.joint.data = (char*) malloc(motor_states_.joint.capacity * sizeof(char));

        motor_states_.status_msg.capacity = 20;
        motor_states_.status_msg.data = (char*) malloc(motor_states_.status_msg.capacity * sizeof(char));
    }
}



void spin_hyperdog_node()
{
    // while (uros.error_code!= UROS_ERROR_)
    motor_states_.leg.size = 2;
    motor_states_.leg.data = "FR";
    motor_states_.joint.size = 3;
    motor_states_.joint.data = "HIP";
    motor_states_.is_available = true;
    motor_states_.is_enabled = true;
    motor_states_.error_code = 0;
    motor_states_.feedback.id = 1;
    motor_states_.feedback.position = 1.23;
    motor_states_.feedback.velocity = 0;
    motor_states_.feedback.torque = -1.8;
    motor_states_.feedback.vb = 0;
    motor_states_.status_msg.data = "Test Msg";
    motor_states_.status_msg.size = strlen(motor_states_.status_msg.data);

    hyperdog_node.motors_states_msg.fr_hip_roll = motor_states_;

    while(1){
        hyperdog_node.rcl_ret = rcl_publish(&hyperdog_node.motors_states_pub, &hyperdog_node.motors_states_msg, NULL);
        
        if(hyperdog_node.rcl_ret  != RCL_RET_OK){
            hyperdog_node.error_code |= NODE_HYPERDOG_ERROR_FAILED_PUB1;
        }
        else{
            hyperdog_node.error_code &= ~ NODE_HYPERDOG_ERROR_FAILED_PUB1;
        }
        osDelay(2);
    }
    

}


/**
 * To destroy all the entities of the hyperdog_node and node itself
 */
void _destroy_hyperdog_node(){
    /* first, destroy all the node's entities */
    hyperdog_node.rcl_ret = rcl_publisher_fini(
                            &hyperdog_node.motors_states_pub,
                            &hyperdog_node.node);
    /// TODO: 

    /* then destroy the node itself */
    hyperdog_node.rcl_ret = rcl_node_fini(&hyperdog_node.node);

}

/**
 * 
 */
// void _create