
#include "main.h"
#include "hyperdog_uros_node.h"
// #include "motor_typedefs.h"
#include "leg_motors.h"


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

        hyperdog_node.executor = rclc_executor_get_zero_initialized_executor();
        hyperdog_node.rcl_ret = rclc_executor_init(
                                &hyperdog_node.executor,
                                &uros.support.context,
                                3,
                                &uros.allocator);
        

        
        /* 3. If no error, init node entities -------------------------------*/
        if(hyperdog_node.rcl_ret == RCL_RET_OK)
        {
            /* - init publishers ------------------------------*/
            _init_motors_states_publisher();


            /* - init subscribers -----------------------------*/


            /* - init services --------------------------------*/
             _init_legMotors_srv();
            _init_enableAllMotors_srv();
           


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
/*                         INIT LEG MOTORS SERVER                                     */
/* ================================================================================== */

/* ------------------------- INITIATE THE SERVICE ------------------------------- */
void _init_legMotors_srv()
{
    hyperdog_node.initLegMotors_srv.srv_name = "/initlegmotors";

    /// get srv type support
    const rosidl_service_type_support_t * type_support = 
        ROSIDL_GET_SRV_TYPE_SUPPORT(hyperdog_uros_msgs, srv, InitLegMotors);

    /// Initiaalize server with default configuration
    
    hyperdog_node.initLegMotors_srv.rcl_ret = 
        rclc_service_init_default(&hyperdog_node.initLegMotors_srv.service,
                                  &hyperdog_node.node,
                                  type_support, 
                                  hyperdog_node.initLegMotors_srv.srv_name);
    if(hyperdog_node.initLegMotors_srv.rcl_ret != RCL_RET_OK){
        hyperdog_node.state = HYPERDOG_NODE_ERROR;
        hyperdog_node.error_code |= NODE_HYPERDOG_ERROR_FAILED_SRV1;
    }else{
        hyperdog_node.state = HYPERDOG_NODE_INITIALIZING;
        hyperdog_node.error_code &= ~NODE_HYPERDOG_ERROR_FAILED_SRV1;
    }

    // add server callback to the executor
    hyperdog_node.initLegMotors_srv.res_msg.error_msg.capacity = 100;
    hyperdog_node.initLegMotors_srv.rcl_ret = 
        rclc_executor_add_service(
            &hyperdog_node.executor,
            &hyperdog_node.initLegMotors_srv.service,
            &hyperdog_node.initLegMotors_srv.req_msg,
            &hyperdog_node.initLegMotors_srv.res_msg,
            _initLegMotors_srv_callback);
    if(hyperdog_node.initLegMotors_srv.rcl_ret != RCL_RET_OK){
        hyperdog_node.state = HYPERDOG_NODE_ERROR;
        hyperdog_node.error_code |= NODE_HYPERDOG_ERROR_FAILED_SRV1;
    }else{
        hyperdog_node.state = HYPERDOG_NODE_INITIALIZING;
        hyperdog_node.error_code &= ~NODE_HYPERDOG_ERROR_FAILED_SRV1;
    }
}

/* ------------------ INIT LEG MOTORS SERVER CALLBACK ----------------------- */
void _initLegMotors_srv_callback(const void* req, void* res)
{
    hyperdog_uros_msgs__srv__InitLegMotors_Request* req_in = (hyperdog_uros_msgs__srv__InitLegMotors_Request*) req;
    hyperdog_uros_msgs__srv__InitLegMotors_Response* res_in = (hyperdog_uros_msgs__srv__InitLegMotors_Response*) res;
    res_in->error_msg.capacity = 100;
    init_legMotors(
        &hcan1, 
        req_in,
        res_in);
    // disable_allMotors();
}


/* ================================================================================== */
/*                         ENABLE_ALL_MOTORS SERVER                                   */
/* ================================================================================== */

/* ------------------------- INITIATE THE SERVICE ------------------------------- */
void _init_enableAllMotors_srv()
{
    hyperdog_node.enableAllMotors_srv.srv_name = "/enableallmotors";

    /// Initiaalize server with default configuration
    hyperdog_node.enableAllMotors_srv.rcl_ret = 
        rclc_service_init_default(&hyperdog_node.enableAllMotors_srv.service,
                          &hyperdog_node.node,
                          ROSIDL_GET_SRV_TYPE_SUPPORT(hyperdog_uros_msgs, srv, EnableAllMotors), 
                          hyperdog_node.enableAllMotors_srv.srv_name);
    if(hyperdog_node.enableAllMotors_srv.rcl_ret != RCL_RET_OK){
        hyperdog_node.state = HYPERDOG_NODE_ERROR;
        hyperdog_node.error_code |= NODE_HYPERDOG_ERROR_FAILED_SRV2;
    }else{
        hyperdog_node.state = HYPERDOG_NODE_INITIALIZING;
        hyperdog_node.error_code &= ~NODE_HYPERDOG_ERROR_FAILED_SRV2;
    }

    // add server callback to the executor
    hyperdog_node.enableAllMotors_srv.res_msg.error_msg.capacity = 100;
    hyperdog_node.enableAllMotors_srv.rcl_ret = 
        rclc_executor_add_service(
            &hyperdog_node.executor,
            &hyperdog_node.enableAllMotors_srv.service,
            &hyperdog_node.enableAllMotors_srv.req_msg,
            &hyperdog_node.enableAllMotors_srv.res_msg,
            _enableAllMotors_srv_callback);
    if(hyperdog_node.enableAllMotors_srv.rcl_ret != RCL_RET_OK){
        hyperdog_node.state = HYPERDOG_NODE_ERROR;
        hyperdog_node.error_code |= NODE_HYPERDOG_ERROR_FAILED_SRV2;
    }else{
        hyperdog_node.state = HYPERDOG_NODE_INITIALIZING;
        hyperdog_node.error_code &= ~NODE_HYPERDOG_ERROR_FAILED_SRV2;
    }
}

/* ------------------ ENABLE ALL MOTORS SERVER CALLBACK ----------------------- */
void _enableAllMotors_srv_callback(const void* req, void* res){
    hyperdog_uros_msgs__srv__EnableAllMotors_Request* req_in = (hyperdog_uros_msgs__srv__EnableAllMotors_Request*) req;
    hyperdog_uros_msgs__srv__EnableAllMotors_Response* res_in = (hyperdog_uros_msgs__srv__EnableAllMotors_Response*) res;
    res_in->error_msg.capacity = 200;

    if (req_in->enable == true)
    {
        enable_allMotors();
        char err_m[500] = "";

        for(int i=0; i<NUM_OF_LEGS; i++){
            for(int j=0; j<NUM_OF_JOINTS_PER_LEG; j++){
                if(legMotor[i][j].debug_state == MOTOR_ENABLED){
                    res_in->is_enabled = true;
                }else{
                    res_in->is_enabled = false;
                    switch (i+j){
                    case 0:strcat(err_m, "fr_hip_roll:\n")  ;break;
                    case 1:strcat(err_m, "fr_hip_pitch:\n") ;break;
                    case 2:strcat(err_m, "fr_knee:\n")      ;break;
                    case 3:strcat(err_m, "fl_hip_roll:\n")  ;break;
                    case 4:strcat(err_m, "fl_hip_pitch:\n") ;break;
                    case 5:strcat(err_m, "fl_knee:\n")      ;break;
                    case 6:strcat(err_m, "rr_hip_roll:\n")  ;break;
                    case 7:strcat(err_m, "rr_hip_pitch:\n") ;break;
                    case 8:strcat(err_m, "rr_knee:\n")      ;break;
                    case 9:strcat(err_m, "rl_hip_roll:\n")  ;break;
                    case 10:strcat(err_m, "rl_hip_pitch:\n");break;
                    case 11:strcat(err_m, "rl_knee:\n")     ;break;
                    default:break;}
                    
                    if((legMotor[i][j].state.error_code & MOTOR_ERROR_NOT_INITIALIZED)==MOTOR_ERROR_NOT_INITIALIZED)
                        strcat(err_m, "motor is not initialized.\n");
                    if((legMotor[i][j].state.error_code & MOTOR_ERROR_PARAM)==MOTOR_ERROR_PARAM)
                        strcat(err_m, "motor params error.\n");
                    if((legMotor[i][j].state.error_code & MOTOR_ERROR_HAL_CAN)==MOTOR_ERROR_HAL_CAN)
                        strcat(err_m, "HAL CAN error.\n");
                    if((legMotor[i][j].state.error_code & MOTOR_ERROR_OFFLINE)==MOTOR_ERROR_OFFLINE)
                        strcat(err_m, "Motor is not online.\n");
                    if((legMotor[i][j].state.error_code & MOTOR_ERROR_OOR)==MOTOR_ERROR_OOR)
                        strcat(err_m, "Motor position is out of range.\n");
                    if((legMotor[i][j].state.error_code & MOTOR_ERROR_OH)==MOTOR_ERROR_OH)
                        strcat(err_m, "Motor is over-heated.\n");
                    if((legMotor[i][j].state.error_code & MOTOR_ERROR_OC)==MOTOR_ERROR_OC)
                        strcat(err_m, "Motor is using over curent.\n");
                    if((legMotor[i][j].state.error_code & MOTOR_ERROR_EN)==MOTOR_ERROR_EN)
                        strcat(err_m, "Failed to enable.\n");
                    
                }
            }
        }
        res_in->error_msg.size = strlen(err_m);
        res_in->error_msg.data = err_m;
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

    ///   * set callback function
    hyperdog_node.motorsStates_pub.callback = _motors_states_timer_callback;

    ///   * set timer period           
    hyperdog_node.motorsStates_pub.timer_period = MOTORS_STATES_PUB_TIMER_PERIOD_NS;

    ///   * initialize timer object    
    hyperdog_node.motorsStates_pub.rcl_ret 
        = rclc_timer_init_default(
            &hyperdog_node.motorsStates_pub.timer,
            &uros.support,
            hyperdog_node.motorsStates_pub.timer_period,
            hyperdog_node.motorsStates_pub.callback);

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

    if(timer != NULL && motor_objects_created) {
        /// update msg
        if(legMotor[0][0].debug_state != MOTOR_INITIALIZED)
            hyperdog_node.motorsStates_pub.msg.fr_hip_roll  = legMotor[0][0].state;
        if(legMotor[0][1].debug_state != MOTOR_INITIALIZED)
            hyperdog_node.motorsStates_pub.msg.fr_hip_pitch = legMotor[0][1].state;
        if(legMotor[0][1].debug_state != MOTOR_INITIALIZED)
            hyperdog_node.motorsStates_pub.msg.fr_knee      = legMotor[0][2].state;
        
        if(legMotor[1][0].debug_state != MOTOR_INITIALIZED)
            hyperdog_node.motorsStates_pub.msg.fl_hip_roll  = legMotor[1][0].state;
        if(legMotor[1][1].debug_state != MOTOR_INITIALIZED)
            hyperdog_node.motorsStates_pub.msg.fl_hip_pitch = legMotor[1][1].state;
        if(legMotor[1][2].debug_state != MOTOR_INITIALIZED)
            hyperdog_node.motorsStates_pub.msg.fl_knee      = legMotor[1][2].state;

        if(legMotor[2][0].debug_state != MOTOR_INITIALIZED)
            hyperdog_node.motorsStates_pub.msg.rr_hip_roll  = legMotor[2][0].state;
        if(legMotor[2][1].debug_state != MOTOR_INITIALIZED)
            hyperdog_node.motorsStates_pub.msg.rr_hip_pitch = legMotor[2][1].state;
        if(legMotor[2][2].debug_state != MOTOR_INITIALIZED)
            hyperdog_node.motorsStates_pub.msg.rr_knee      = legMotor[2][2].state;

        if(legMotor[3][0].debug_state != MOTOR_INITIALIZED)
            hyperdog_node.motorsStates_pub.msg.rl_hip_roll  = legMotor[3][0].state;
        if(legMotor[3][1].debug_state != MOTOR_INITIALIZED)
            hyperdog_node.motorsStates_pub.msg.rl_hip_pitch = legMotor[3][1].state;
        if(legMotor[3][2].debug_state != MOTOR_INITIALIZED)
            hyperdog_node.motorsStates_pub.msg.rl_knee      = legMotor[3][2].state;

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
    //// * destroy executor
    hyperdog_node.rcl_ret = rclc_executor_fini(&hyperdog_node.executor);
    //// * destroy timer
    hyperdog_node.rcl_ret += rcl_timer_fini(&hyperdog_node.motorsStates_pub.timer);
    //// * destroy motorsStates publisher
    hyperdog_node.rcl_ret += rcl_publisher_fini(
                             &hyperdog_node.motorsStates_pub.publisher,
                             &hyperdog_node.node);
    //// * destroy initLegMotors service
    hyperdog_node.rcl_ret += rcl_service_fini(&hyperdog_node.initLegMotors_srv.service, &hyperdog_node.node);
    //// * destroy enableALlMotors service
    hyperdog_node.rcl_ret += rcl_service_fini(&hyperdog_node.enableAllMotors_srv.service, &hyperdog_node.node);
    

    /// TODO: 

    /// then destroy the node itself
    hyperdog_node.rcl_ret = rcl_node_fini(&hyperdog_node.node);

}


