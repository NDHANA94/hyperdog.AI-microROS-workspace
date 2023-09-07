/* ========================================================================================
MIT License                                                                               |
                                                                                          |
Copyright (c) 2023 Nipun Dhananjaya Weerakkodi                                            |
                                                                                          |
Permission is hereby granted, free of charge, to any person obtaining a copy              |
of this software and associated documentation files (the "Software"), to deal             |
in the Software without restriction, including without limitation the rights              |
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                 |
copies of the Software, and to permit persons to whom the Software is                     |
furnished to do so, subject to the following conditions:                                  |
                                                                                          |
The above copyright notice and this permission notice shall be included in all            |
copies or substantial portions of the Software.                                           |
                                                                                          |
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                |
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                  |
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE               |
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                    |
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,             |
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE             |
SOFTWARE.                                                                                 |
                                                                                          |
==========================================================================================*/
#include "main.h"
#include "hyperdog_uros_node.h"
// #include "motor_typedefs.h"
#include "leg_motors.h"
#include "time.h"
#include <stdio.h>

#include "std_msgs/msg/int32.h"


uint32_t dt;
uint32_t t_prev;

hyperdogUROS_Node_t hyperdog_node;
hyperdog_uros_interfaces__msg__MotorStates motor_states_;

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

        hyperdog_node.exe_servers = rclc_executor_get_zero_initialized_executor();
        hyperdog_node.exe_timers  = rclc_executor_get_zero_initialized_executor();
        hyperdog_node.exe_subs    = rclc_executor_get_zero_initialized_executor();

        hyperdog_node.rcl_ret = rclc_executor_init(
                                &hyperdog_node.exe_servers,
                                &uros.support.context,
                                4,
                                &uros.allocator);
        
        hyperdog_node.rcl_ret += rclc_executor_init(
                                &hyperdog_node.exe_timers,
                                &uros.support.context,
                                1,
                                &uros.allocator);
        
        hyperdog_node.rcl_ret += rclc_executor_init(
                                &hyperdog_node.exe_subs,
                                &uros.support.context,
                                1,
                                &uros.allocator);
        

        
        /* 3. If no error, init node entities -------------------------------*/
        if(hyperdog_node.rcl_ret == RCL_RET_OK)
        {
            /* - init publishers ------------------------------*/
            _init_motors_states_publisher(); /* @bug Can't publish data with best_effort subscriber.  */
            /// TODO: legsStates_publisher
            /// accelrometer/gyroscope data publisher


            /* - init subscribers -----------------------------*/
            _init_motorCmdSubscription();
            // / TODO: legsCmd_subscriber
            


            /* - init services --------------------------------*/
            _init_initLegMotors_srv();
            _init_enableAllMotors_srv();
            _init_disableAllMotors_srv();
            _init_setMotorZeroPosition_srv();
            /// TODO: setWatchdogFrequency_srv
            /// TODO: setMotorCmdFrequency_srv
            /// TODO: setLegStiffness_srv
            /// TODO: setLegDamping_srv
            /// TODO: setMotorIff_srv
           


            /* - init timers ----------------------------------*/
            _init_motorWatchDog_timer();

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
void _init_initLegMotors_srv()
{
    hyperdog_node.initLegMotors_srv.srv_name = "/initLegMotors";

    /// get srv type support
    const rosidl_service_type_support_t * type_support = 
        ROSIDL_GET_SRV_TYPE_SUPPORT(hyperdog_uros_interfaces, srv, InitLegMotors);

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
    hyperdog_node.initLegMotors_srv.rcl_ret = 
        rclc_executor_add_service(
            &hyperdog_node.exe_servers,
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
    hyperdog_uros_interfaces__srv__InitLegMotors_Request* req_in  
        = (hyperdog_uros_interfaces__srv__InitLegMotors_Request*) req;
    hyperdog_uros_interfaces__srv__InitLegMotors_Response* res_in 
        = (hyperdog_uros_interfaces__srv__InitLegMotors_Response*) res;
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
    hyperdog_node.enableAllMotors_srv.srv_name = "/enableAllMotors";

    /// Initiaalize server with default configuration
    hyperdog_node.enableAllMotors_srv.rcl_ret = 
        rclc_service_init_default(&hyperdog_node.enableAllMotors_srv.service,
                          &hyperdog_node.node,
                          ROSIDL_GET_SRV_TYPE_SUPPORT(hyperdog_uros_interfaces, srv, EnableAllMotors), 
                          hyperdog_node.enableAllMotors_srv.srv_name);
    if(hyperdog_node.enableAllMotors_srv.rcl_ret != RCL_RET_OK){
        hyperdog_node.state = HYPERDOG_NODE_ERROR;
        hyperdog_node.error_code |= NODE_HYPERDOG_ERROR_FAILED_SRV2;
    }else{
        hyperdog_node.state = HYPERDOG_NODE_INITIALIZING;
        hyperdog_node.error_code &= ~NODE_HYPERDOG_ERROR_FAILED_SRV2;
    }

    // add server callback to the executor
    hyperdog_node.enableAllMotors_srv.rcl_ret = 
        rclc_executor_add_service(
            &hyperdog_node.exe_servers,
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
    // RCLC_UNUSED(req);
    hyperdog_uros_interfaces__srv__EnableAllMotors_Response* res_in 
        = (hyperdog_uros_interfaces__srv__EnableAllMotors_Response*) res;

    if(motor_objects_created) enable_allMotors();
    
    for(int i=0; i<NUM_OF_LEGS; i++){
        for(int j=0; j<NUM_OF_JOINTS_PER_LEG; j++){
            if(motor_objects_created)
                res_in->error_code[i*NUM_OF_JOINTS_PER_LEG+j] = legMotor[i][j].state.error_code;
            else{
                res_in->error_code[i*NUM_OF_JOINTS_PER_LEG+j] = 0xFFFF;
            }
        }
    }
}

/* ================================================================================== */
/*                         DISABLE_ALL_MOTORS SERVER                                   */
/* ================================================================================== */

/* ------------------------- INITIATE THE SERVICE ------------------------------- */
void _init_disableAllMotors_srv()
{
    hyperdog_node.disableAllMotors_srv.srv_name = "/disableAllMotors";

    /// Initiaalize server with default configuration
    hyperdog_node.disableAllMotors_srv.rcl_ret = 
        rclc_service_init_default(&hyperdog_node.disableAllMotors_srv.service,
                          &hyperdog_node.node,
                          ROSIDL_GET_SRV_TYPE_SUPPORT(hyperdog_uros_interfaces, srv, DisableAllMotors), 
                          hyperdog_node.disableAllMotors_srv.srv_name);
    if(hyperdog_node.disableAllMotors_srv.rcl_ret != RCL_RET_OK){
        hyperdog_node.state = HYPERDOG_NODE_ERROR;
        hyperdog_node.error_code |= NODE_HYPERDOG_ERROR_FAILED_SRV3;
    }else{
        hyperdog_node.state = HYPERDOG_NODE_INITIALIZING;
        hyperdog_node.error_code &= ~NODE_HYPERDOG_ERROR_FAILED_SRV3;
    }

    // add server callback to the executor
    hyperdog_node.disableAllMotors_srv.rcl_ret = 
        rclc_executor_add_service(
            &hyperdog_node.exe_servers,
            &hyperdog_node.disableAllMotors_srv.service,
            &hyperdog_node.disableAllMotors_srv.req_msg,
            &hyperdog_node.disableAllMotors_srv.res_msg,
            _disableAllMotors_srv_callback);
    if(hyperdog_node.disableAllMotors_srv.rcl_ret != RCL_RET_OK){
        hyperdog_node.state = HYPERDOG_NODE_ERROR;
        hyperdog_node.error_code |= NODE_HYPERDOG_ERROR_FAILED_SRV3;
    }else{
        hyperdog_node.state = HYPERDOG_NODE_INITIALIZING;
        hyperdog_node.error_code &= ~NODE_HYPERDOG_ERROR_FAILED_SRV3;
    }
}

/* ------------------ ENABLE ALL MOTORS SERVER CALLBACK ----------------------- */
void _disableAllMotors_srv_callback(const void* req, void* res){
    // RCLC_UNUSED(req);
    hyperdog_uros_interfaces__srv__DisableAllMotors_Response* res_in 
        = (hyperdog_uros_interfaces__srv__DisableAllMotors_Response*) res;

    if(motor_objects_created) disable_allMotors();
    
    for(int i=0; i<NUM_OF_LEGS; i++){
        for(int j=0; j<NUM_OF_JOINTS_PER_LEG; j++){
            if(motor_objects_created)
                res_in->error_code[i*NUM_OF_JOINTS_PER_LEG+j] = legMotor[i][j].state.error_code;
            else{
                res_in->error_code[i*NUM_OF_JOINTS_PER_LEG+j] = 0xFFFF;
            }
        }
    }
}


/* ================================================================================== */
/*                         SET_MOTOR_ZERO_POSITON SERVER                                */
/* ================================================================================== */

/* ------------------------- INITIATE THE SERVICE ------------------------------- */
void _init_setMotorZeroPosition_srv()
{
    hyperdog_node.setMotorZeroPosition_srv.srv_name = "/setMotorZeroPosition";

    /// Initiaalize server with default configuration
    hyperdog_node.setMotorZeroPosition_srv.rcl_ret = 
        rclc_service_init_default(&hyperdog_node.setMotorZeroPosition_srv.service,
                          &hyperdog_node.node,
                          ROSIDL_GET_SRV_TYPE_SUPPORT(hyperdog_uros_interfaces, srv, SetZeroPosition), 
                          hyperdog_node.setMotorZeroPosition_srv.srv_name);
    if(hyperdog_node.setMotorZeroPosition_srv.rcl_ret != RCL_RET_OK){
        hyperdog_node.state = HYPERDOG_NODE_ERROR;
        hyperdog_node.error_code |= NODE_HYPERDOG_ERROR_FAILED_SRV4;
    }else{
        hyperdog_node.state = HYPERDOG_NODE_INITIALIZING;
        hyperdog_node.error_code &= ~NODE_HYPERDOG_ERROR_FAILED_SRV4;
    }

    // add server callback to the executor
    hyperdog_node.setMotorZeroPosition_srv.rcl_ret = 
        rclc_executor_add_service(
            &hyperdog_node.exe_servers,
            &hyperdog_node.setMotorZeroPosition_srv.service,
            &hyperdog_node.setMotorZeroPosition_srv.req_msg,
            &hyperdog_node.setMotorZeroPosition_srv.res_msg,
            _setMotorZeroPosition_srv_callback);
    if(hyperdog_node.setMotorZeroPosition_srv.rcl_ret != RCL_RET_OK){
        hyperdog_node.state = HYPERDOG_NODE_ERROR;
        hyperdog_node.error_code |= NODE_HYPERDOG_ERROR_FAILED_SRV4;
    }else{
        hyperdog_node.state = HYPERDOG_NODE_INITIALIZING;
        hyperdog_node.error_code &= ~NODE_HYPERDOG_ERROR_FAILED_SRV4;
    }
}

/* ------------------ ENABLE ALL MOTORS SERVER CALLBACK ----------------------- */
void _setMotorZeroPosition_srv_callback(const void* req, void* res){
    hyperdog_uros_interfaces__srv__SetZeroPosition_Request* req_in 
        = (hyperdog_uros_interfaces__srv__SetZeroPosition_Request*) req;
    hyperdog_uros_interfaces__srv__SetZeroPosition_Response* res_in 
        = (hyperdog_uros_interfaces__srv__SetZeroPosition_Response*) res;

    /// TODO: Find the condition to set motor zero position (enbled or disanled)
    ///       Only the condition is valid, do set_zero_position, otherwise response error
    if(motor_objects_created){
        set_motor_zero_position(&legMotor[req_in->leg][req_in->joint]);
        res_in->error_code = legMotor[req_in->leg][req_in->joint].state.error_code;
    }else{
        res_in->error_code = 0xFFFF;
    }

}




/* ================================================================================== */
/*                         MOTORS STATES PUBLISHER                                    */
/* ================================================================================== */

/* ------------------------- INITIATE THE PUBLISHER ------------------------------ */
/**
 * \bug
 * This publisher publishes msgs in a rate of 40 Hz with reliable QOS mode.
 * In order to get a higher frequency data, best_effort QOS must be implemented.
 * Since this publisher's msg size is 768 Bytes, MTU is set to 1024 Bytes. 
 * Now the publish rate is 50Hz. Still not improved well.
*/
void _init_motors_states_publisher()
{
    /// TODO: best effort publisher gives rcl_ret 1 error no matter what.
    ///       Find a solution for it and implement the rclc_publisher_init_best_effort!
    ///       otherwise, withe the default publisher we get around 47 publishing rate.
    hyperdog_node.motorsStates_pub.rcl_ret
        = rclc_publisher_init_best_effort(
            &hyperdog_node.motorsStates_pub.publisher,
            &hyperdog_node.node,
            ROSIDL_GET_MSG_TYPE_SUPPORT(hyperdog_uros_interfaces, msg, MotorsStatesEncoded),
            // ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32), // for frequency test
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
    /* // to publish msg using a timer
    /// initialize timer callback       
    ///   * set callback function
    hyperdog_node.motorsStates_pub.callback = _motors_states_timer_callback;
    ///   * set timer period           
    hyperdog_node.motorsStates_pub.timer_period = RCL_MS_TO_NS(MOTORS_STATES_PUB_TIMER_PERIOD_NS);
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
                &hyperdog_node.exe_timers, 
                &hyperdog_node.motorsStates_pub.timer);

        if(hyperdog_node.motorsStates_pub.rcl_ret != RCL_RET_OK){
            hyperdog_node.state = HYPERDOG_NODE_ERROR;
            hyperdog_node.error_code |= NODE_HYPERDOG_ERROR_FAILED_PUB1;
        }
        else{hyperdog_node.error_code &= ~NODE_HYPERDOG_ERROR_FAILED_PUB1;}
    } 
    */
}

/* ------------------------ PUBLISHER CALLBACK -------------------------------------- */
/*
 */
// void _motors_states_timer_callback(rcl_timer_t * timer, int64_t last_call_time)
void publish_motors_states()
{
    // RCLC_UNUSED(last_call_time);
    // timer != NULL && 
    if(motor_objects_created) {
        /// update motor state.status_msg
        for(int i=0; i<NUM_OF_LEGS; i++){
            for (int j=0; j<NUM_OF_JOINTS_PER_LEG; j++){
                switch (legMotor[i][j].debug_state)
                {
                case MOTOR_NOT_INITIALIZED:
                    legMotor[i][j].state.status_msg.data = "NOT_INITIALIZED";
                    legMotor[i][j].state.status_msg.size = strlen(legMotor[i][j].state.status_msg.data);
                    break;
                case MOTOR_INITIALIZED:
                    legMotor[i][j].state.status_msg.data = "INITIALIZED";
                    legMotor[i][j].state.status_msg.size = strlen(legMotor[i][j].state.status_msg.data);
                    break;
                case MOTOR_DISABLED:
                    legMotor[i][j].state.status_msg.data = "DISABLED";
                    legMotor[i][j].state.status_msg.size = strlen(legMotor[i][j].state.status_msg.data);
                    break;
                case MOTOR_ENABLED:
                    legMotor[i][j].state.status_msg.data = "ENABLED";
                    legMotor[i][j].state.status_msg.size = strlen(legMotor[i][j].state.status_msg.data);
                    break;
                case MOTOR_OFFLINE:
                    legMotor[i][j].state.status_msg.data = "OFFLINE";
                    legMotor[i][j].state.status_msg.size = strlen(legMotor[i][j].state.status_msg.data);
                    break;
                case MOTOR_ERROR:
                    legMotor[i][j].state.status_msg.data = "ERROR";
                    legMotor[i][j].state.status_msg.size = strlen(legMotor[i][j].state.status_msg.data);
                    break;
                case CAN_ERROR:
                    legMotor[i][j].state.status_msg.data = "CAN_ERROR";
                    legMotor[i][j].state.status_msg.size = strlen(legMotor[i][j].state.status_msg.data);
                    break;
                default:
                    break;
                }
            }
        }

        /// update msg
            hyperdog_node.motorsStates_pub.msg.fr_hip_roll  = legMotor[0][0].state;
            hyperdog_node.motorsStates_pub.msg.fr_hip_pitch = legMotor[0][1].state;
            hyperdog_node.motorsStates_pub.msg.fr_knee      = legMotor[0][2].state;
        
            hyperdog_node.motorsStates_pub.msg.fl_hip_roll  = legMotor[1][0].state;
            hyperdog_node.motorsStates_pub.msg.fl_hip_pitch = legMotor[1][1].state;
            hyperdog_node.motorsStates_pub.msg.fl_knee      = legMotor[1][2].state;

            hyperdog_node.motorsStates_pub.msg.rr_hip_roll  = legMotor[2][0].state;
            hyperdog_node.motorsStates_pub.msg.rr_hip_pitch = legMotor[2][1].state;
            hyperdog_node.motorsStates_pub.msg.rr_knee      = legMotor[2][2].state;

            hyperdog_node.motorsStates_pub.msg.rl_hip_roll  = legMotor[3][0].state;
            hyperdog_node.motorsStates_pub.msg.rl_hip_pitch = legMotor[3][1].state;
            hyperdog_node.motorsStates_pub.msg.rl_knee      = legMotor[3][2].state;

        int msg_size = sizeof(hyperdog_node.motorsStates_pub.msg); // 336 Bytes
        
        std_msgs__msg__Int32 msg; // for frequency test
        msg.data = dt;            // for frequency test
        t_prev = HAL_GetTick();
        /// publish msg 
        hyperdog_node.motorsStates_pub.rcl_ret 
            = rcl_publish(
                &hyperdog_node.motorsStates_pub.publisher, 
                &hyperdog_node.motorsStates_pub.msg, 
                // &msg,         // for frequency test
                NULL);
        dt = HAL_GetTick() - t_prev;
        if(hyperdog_node.motorsStates_pub.rcl_ret  != RCL_RET_OK){
            hyperdog_node.error_code |= NODE_HYPERDOG_ERROR_FAILED_PUB1;
            // restartMicroROS(); /// Assuming error occured due to the connectiorn lost with the agent
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
/*                         MOTORS CMD SUBSCRIPTION                                    */
/* ================================================================================== */

/* ------------------------- INITIATE THE SUBSCRIBER -------------------------------- */
void _init_motorCmdSubscription()
{
    const char* topic_name = "/motor_cmd";
    const rosidl_message_type_support_t* type_support = 
        ROSIDL_GET_MSG_TYPE_SUPPORT(hyperdog_uros_interfaces, msg, MotorCmd);
    /* initialize the subscription------------------------------------- */
    hyperdog_node.motorCmd_sub.rcl_ret = 
        rclc_subscription_init_best_effort(
            &hyperdog_node.motorCmd_sub.subscriber,
            &hyperdog_node.node,
            type_support,
            topic_name);

    /* add subscription to the executor  */
    hyperdog_node.motorCmd_sub.rcl_ret += 
        rclc_executor_add_subscription(
            &hyperdog_node.exe_subs, &hyperdog_node.motorCmd_sub.subscriber, 
            &hyperdog_node.motorCmd_sub.msg, 
            &_motor_cmd_sub_callback, ON_NEW_DATA);

    /* check error */
    if(hyperdog_node.motorCmd_sub.rcl_ret != RCL_RET_OK){
        hyperdog_node.state = HYPERDOG_NODE_ERROR;
        hyperdog_node.error_code |= NODE_HYPERDOG_ERROR_FAILED_SUB1;
    }else{
        hyperdog_node.error_code &= ~NODE_HYPERDOG_ERROR_FAILED_SUB1;
    }



}

/* -------------------------- SUBSCRIPTION CALLBACK --------------------------------- */
void _motor_cmd_sub_callback(const void* msg)
{
    dt = HAL_GetTick();
    const hyperdog_uros_interfaces__msg__MotorCmd* cmd =
        (const hyperdog_uros_interfaces__msg__MotorCmd*) msg;

    LegMotor_TypeDef* m;
    m = &legMotor[cmd->leg][cmd->joint];

    if(motor_objects_created){
        /* check for special cmds */
        if(cmd->disable == true) disable_motor(m);
        else if(cmd->enable == true) enable_motor(m);
        else if(cmd->set_zero == true) set_motor_zero_position(m);
        else if(m->debug_state == MOTOR_ENABLED){
            m->cmd.desire_position = cmd->desire_position;
            m->cmd.desire_velocity = cmd->desire_velocity;
            m->cmd.kp = cmd->kp;
            m->cmd.kd = cmd->kd;
            m->cmd.i_ff = cmd->i_ff;
            _pack_cmd(m);
            motor_sendTx_getRx(m);
            publish_motors_states();
        }
        
    }
    
    
}

/* ================================================================================== */
/*                               MOTOR WATCHDOG                                       */
/* ================================================================================== */
void _init_motorWatchDog_timer()
{
    hyperdog_node.motorWatchdog_timer.callback = _motor_watchdog_timer_callback;
    hyperdog_node.motorWatchdog_timer.timer_period = RCL_MS_TO_NS(MOTOR_WATCHDOG_TIMER_PERIOD);
    hyperdog_node.motorWatchdog_timer.rcl_ret = 
        rclc_timer_init_default(
            &hyperdog_node.motorWatchdog_timer.timer,
            &uros.support,
            hyperdog_node.motorWatchdog_timer.timer_period,
            hyperdog_node.motorWatchdog_timer.callback);

    hyperdog_node.motorWatchdog_timer.rcl_ret +=
         rclc_executor_add_timer(
            &hyperdog_node.exe_timers,
            &hyperdog_node.motorWatchdog_timer.timer);

    if(hyperdog_node.motorWatchdog_timer.rcl_ret != RCL_RET_OK){
        hyperdog_node.state = HYPERDOG_NODE_ERROR;
        hyperdog_node.error_code |= NODE_HYPERDOG_ERROR_FAILED_TIM2;
    }else{
        hyperdog_node.error_code &= ~NODE_HYPERDOG_ERROR_FAILED_TIM2;
    }
}
/* --------------------- MOTOR WATCHDOG TIMER CALLBACK ----------------------------- */
void _motor_watchdog_timer_callback(rcl_timer_t * timer, int64_t last_call_time)
{
    if(motor_objects_created){
        for(int i=0; i<NUM_OF_LEGS; i++){
            for(int j=0; j<NUM_OF_JOINTS_PER_LEG; j++){       
                int32_t t = HAL_GetTick();
                int32_t dt_ = t - legMotor[i][j].last_update_time;
                if(legMotor[i][j].debug_state != MOTOR_ENABLED){
                    disable_motor(&legMotor[i][j]);
                    publish_motors_states();
                }else if(legMotor[i][j].debug_state == MOTOR_ENABLED 
                && dt_ > MAX_NO_UPDATE_TIME){
                    motor_sendTx_getRx(&legMotor[i][j]);
                    publish_motors_states();
                }
            }
        }
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
    hyperdog_node.rcl_ret = rclc_executor_fini(&hyperdog_node.exe_servers);
    hyperdog_node.rcl_ret = rclc_executor_fini(&hyperdog_node.exe_timers);
    hyperdog_node.rcl_ret = rclc_executor_fini(&hyperdog_node.exe_subs);
    //// * destroy motor_states_pub's timer
    hyperdog_node.rcl_ret += rcl_timer_fini(&hyperdog_node.motorsStates_pub.timer);
    //// * destroy motorsStates publisher
    hyperdog_node.rcl_ret += rcl_publisher_fini(
                             &hyperdog_node.motorsStates_pub.publisher,
                             &hyperdog_node.node);
    //// * destroy motorCmd subscriber
    hyperdog_node.rcl_ret += rcl_subscription_fini(
                             &hyperdog_node.motorCmd_sub.subscriber,
                             &hyperdog_node.node);
    //// * destroy initLegMotors service
    hyperdog_node.rcl_ret += rcl_service_fini(&hyperdog_node.initLegMotors_srv.service, &hyperdog_node.node);
    //// * destroy enableALlMotors service
    hyperdog_node.rcl_ret += rcl_service_fini(&hyperdog_node.enableAllMotors_srv.service, &hyperdog_node.node);
    //// * destroy disableAllMotors service
    hyperdog_node.rcl_ret += rcl_service_fini(&hyperdog_node.disableAllMotors_srv.service, &hyperdog_node.node);
    //// * destroy setMotorZeroPosition service
    hyperdog_node.rcl_ret += rcl_service_fini(&hyperdog_node.setMotorZeroPosition_srv.service, &hyperdog_node.node);
    

    /// TODO: 

    /// then destroy the node itself
    hyperdog_node.rcl_ret = rcl_node_fini(&hyperdog_node.node);



}


