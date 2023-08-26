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

#ifndef UROS_TASKS_H__
#define  UROS_TASKS_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "stdint.h"
#include "float.h"
#include "math.h"
#include <stdbool.h>

#include <time.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <uxr/client/transport.h>
#include <rmw_microxrcedds_c/config.h>
#include <rmw_microros/rmw_microros.h>
#include <rmw/ret_types.h>

#include <std_msgs/msg/int32.h>
#include <std_msgs/msg/float64_multi_array.h>
#include <std_msgs/msg/float32_multi_array.h>
#include <std_msgs/msg/header.h>
#include <hyperdog_uros_msgs/msg/motor_cmd.h>


#include "error_indicator.h"
// #include "minicheetah_motor.h"

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){printk("Failed status on line %d: %d. Aborting.\n",__LINE__,(int)temp_rc);}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){printk("Failed status on line %d: %d. Continuing.\n",__LINE__,(int)temp_rc);}}

#define UROS_ERROR_NONE                     0b00000000  /*!<  No error*/
#define UROS_ERROR_RMW_TRANSPORT            0b00000001  /*!<  Failed to create RMW transport*/
#define UROS_ERROR_FREERTOS_ALLOC           0b00000010  /*!<  Failed to allocate memory for FreeRTOS*/
#define UROS_ERROR_RCL_SUPPORT_INIT         0b00000100  /*!<  Failed to connect with the Agent or create rcl support*/
#define UROS_ERROR_RCL_NODE_INIT            0b00001000  /*!<  Failed to initialize the node*/
#define UROS_ERROR_RCL_MOTOR_FB_PUB_INIT    0b00010000  /*!<  Failed to initialize the motor feedback publisher*/
#define UROS_ERROR_RCL_MOTOR_FB_PUB         0b00100000  /*!<  Failed to publish motor feedback*/
// #define UROS_ERROR_RCL_

#define UROS_STATUS_NOT_INIT            0b00000000
#define UROS_STATUS_CONFIG              0b00000001
#define UROS_STATUS_ALLOC_FREERTOS      0b00000010
#define UROS_STATUS_RCL_SUPPORT         0b00000100
#define UROS_STATUS_NODE                0b00001000
#define UROS_STATUS_MOTOR_FB_PUB        0b00010000


bool cubemx_transport_open(struct uxrCustomTransport * transport);
bool cubemx_transport_close(struct uxrCustomTransport * transport);

size_t cubemx_transport_write(struct uxrCustomTransport* transport, const uint8_t * buf, size_t len, uint8_t * err);
size_t cubemx_transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err);

void * microros_allocate(size_t size, void * state);
void microros_deallocate(void * pointer, void * state);
void * microros_reallocate(void * pointer, size_t size, void * state);
void * microros_zero_allocate(size_t number_of_elements, size_t size_of_element, void * state);


/* States of the node */
enum UROS_STATE{
UROS_INITIALIZING = 0,
UROS_ERROR = 1,
UROS_WAITING_FOR_AGENT = 2,
UROS_RUNNING = 3,
UROS_NODE_DESTROYED = 4,
};

/* TypeDef of UROS default Node */
struct{
    rcl_allocator_t                     allocator;
    rclc_support_t                      support;
    rcl_node_t                          node;
    rcl_publisher_t                     motor_fb_pub;       /*!< motor feedback publisher */
    std_msgs__msg__Float32MultiArray    motor_fb_msg;
    uint8_t                             stm32_;
    hyperdog_uros_msgs__msg__MotorCmd   motor_cmd_msg;
    std_msgs__msg__Int32                msg;
    uint8_t                             error_code;
    rmw_ret_t                           rmw_ret;
    rcl_ret_t                           rcl_ret;
    enum UROS_STATE                     state;
    uint8_t                             status;
}typedef UROS_t;

/* declaye uros node */
extern UROS_t uros;


// functions
void init_uros_node();
void spin_uros_node(int os_delay);

bool _config_uros();
bool _maloc4FreeRTOS();
bool _create_rcl_support();
bool _create_uros_node();
bool _create_motor_feedback_publisher();
void _destroy_support();
void _destroy_node();

#ifdef __cplusplus
}
#endif //__cplusplus
#endif // UROS_TASKS_H__
