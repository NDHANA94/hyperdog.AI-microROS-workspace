#ifndef _HYPERDOG_UROS_NODE_H_
#define _HYPERDOG_UROS_NODE_H_
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

#ifdef __cplusplus
extern "C"{
#endif

#include "stdint.h"
#include "float.h"
#include "math.h"
#include <stdbool.h>
#include <stdbool.h>

#include "hyperdog_uros_app.h"
#include "hyperdog_uros_msgs/msg/motor_states.h"
#include "hyperdog_uros_msgs/msg/motors_states.h"
#include "hyperdog_uros_msgs/srv/init_leg_motors.h"

#define MOTORS_STATES_PUB_TIMER_PERIOD_NS       RCL_MS_TO_NS(10) /*!< 10ms */

/**
 * |          |   12~10  |     9~7    |   6~4    |    3~1   |  0   |  
 * |          | srvs err | timers err | subs err | pubs err | init |
 */ 
#define NODE_HYPERDOG_ERROR_NONE                0b0000000000000
#define NODE_HYPERDOG_ERROR_FAILED_INIT         0b0000000000001

#define NODE_HYPERDOG_ERROR_FAILED_PUB1         0b0000000000010 /*!< motor states publisher     */
#define NODE_HYPERDOG_ERROR_FAILED_PUB2         0b0000000000100 /*!< 2nd publisher              */
#define NODE_HYPERDOG_ERROR_FAILED_PUB3         0b0000000000110 /*!< 3rd publisher              */
#define NODE_HYPERDOG_ERROR_FAILED_PUB4         0b0000000001000 /*!< 4th publisher              */
#define NODE_HYPERDOG_ERROR_FAILED_PUB5         0b0000000001010 /*!< 5th publisher              */
#define NODE_HYPERDOG_ERROR_FAILED_PUB6         0b0000000001100 /*!< 6th publisher              */
#define NODE_HYPERDOG_ERROR_FAILED_PUB7         0b0000000001110 /*!< 7th publisher              */

#define NODE_HYPERDOG_ERROR_FAILED_SUB1         0b0000000010000 /*!< 1st subscriber             */
#define NODE_HYPERDOG_ERROR_FAILED_SUB2         0b0000000100000 /*!< 2nd subscriber             */
#define NODE_HYPERDOG_ERROR_FAILED_SUB3         0b0000000110000 /*!< 3rd subscriber             */
#define NODE_HYPERDOG_ERROR_FAILED_SUB4         0b0000001000000 /*!< 4th subscriber             */
#define NODE_HYPERDOG_ERROR_FAILED_SUB5         0b0000001010000 /*!< 5th subscriber             */
#define NODE_HYPERDOG_ERROR_FAILED_SUB6         0b0000001100000 /*!< 6th subscriber             */
#define NODE_HYPERDOG_ERROR_FAILED_SUB7         0b0000001110000 /*!< 7th subscriber             */

#define NODE_HYPERDOG_ERROR_FAILED_TIM1         0b0000010000000 /*!< 1st timer                  */
#define NODE_HYPERDOG_ERROR_FAILED_TIM2         0b0000100000000 /*!< 2st timer                  */
#define NODE_HYPERDOG_ERROR_FAILED_TIM3         0b0000110000000 /*!< 3st timer                  */
#define NODE_HYPERDOG_ERROR_FAILED_TIM4         0b0001000000000 /*!< 4st timer                  */
#define NODE_HYPERDOG_ERROR_FAILED_TIM5         0b0001010000000 /*!< 5st timer                  */
#define NODE_HYPERDOG_ERROR_FAILED_TIM6         0b0001100000000 /*!< 6st timer                  */
#define NODE_HYPERDOG_ERROR_FAILED_TIM7         0b0001110000000 /*!< 7st timer                  */

#define NODE_HYPERDOG_ERROR_FAILED_SRV1         0b0010000000000 /*!< 1st service                */
#define NODE_HYPERDOG_ERROR_FAILED_SRV2         0b0100000000000 /*!< 2st service                */
#define NODE_HYPERDOG_ERROR_FAILED_SRV3         0b0110000000000 /*!< 3st service                */
#define NODE_HYPERDOG_ERROR_FAILED_SRV4         0b1000000000000 /*!< 4st service                */
#define NODE_HYPERDOG_ERROR_FAILED_SRV5         0b1010000000000 /*!< 5st service                */
#define NODE_HYPERDOG_ERROR_FAILED_SRV6         0b1100000000000 /*!< 6st service                */
#define NODE_HYPERDOG_ERROR_FAILED_SRV7         0b1110000000000 /*!< 7st service                */

enum State{
    HYPERDOG_NODE_NOT_INITIALIZED,
    HYPERDOG_NODE_INITIALIZING,
    HYPERDOG_NODE_INITIALIZED,    
    HYPERDOG_NODE_RUNNING,
    HYPERDOG_NODE_ERROR
};

typedef void(* motor_states_pub_callback_t)(rcl_timer_t*, int64_t);
struct{
    rcl_publisher_t                         publisher;
    hyperdog_uros_msgs__msg__MotorsStates   msg; 
    rcl_timer_t                             timer; 
    unsigned int                            timer_period; /* Hz */
    rcl_ret_t                               rcl_ret;
    motor_states_pub_callback_t             callback;
}typedef motorStates_publisher_t;


struct{
    rcl_service_t                           service;
    const char*                             srv_name;
    rcl_ret_t                               rcl_ret;
    rclc_service_callback_t                 callback;
    hyperdog_uros_msgs__srv__InitLegMotors_Request* req;
    hyperdog_uros_msgs__srv__InitLegMotors_Response* res;
}typedef legMotorsInit_srv_t;


struct
{
    rcl_node_t                              node;
    rclc_executor_t                         executor;
    legMotorsInit_srv_t                     initLegMotors_srv;
    motorStates_publisher_t                 motorsStates_pub;
    enum State                              state;
    uint16_t                                error_code;             /* 13-bits error-code*/
    rcl_ret_t                               rcl_ret;
}typedef hyperdogUROS_Node_t;

extern hyperdog_uros_msgs__msg__MotorStates motor_states_;
extern hyperdogUROS_Node_t hyperdog_node;

/* function decorators */

void init_hyperdog_node();

void _init_motors_states_publisher();
void _motors_states_timer_callback(rcl_timer_t * timer, int64_t last_call_time);

void _init_legMotors_srv();
void _destroy_hyperdog_node();


#ifdef __cplusplus
}
#endif
#endif //_HYPERDOG_UROS_NODE_H_