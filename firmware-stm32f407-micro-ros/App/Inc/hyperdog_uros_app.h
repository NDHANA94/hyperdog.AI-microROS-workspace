#ifndef _HYPERDOG_UROS_APP_H_
#define _HYPERDOG_UROS_APP_H_

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

/* general includes */
#include "stdint.h"
#include "float.h"
#include "math.h"
#include <stdbool.h>
#include <time.h>
#include "usart.h"
/* microros inculde */
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <uxr/client/transport.h>
#include <rmw_microxrcedds_c/config.h>
#include <rmw_microros/rmw_microros.h>
#include <rmw/ret_types.h>

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){printk("Failed status on line %d: %d. Aborting.\n",__LINE__,(int)temp_rc);}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){printk("Failed status on line %d: %d. Continuing.\n",__LINE__,(int)temp_rc);}}

/* 4-bits error defines */
#define UROS_ERROR_NONE                 0b0000 /* No errors */
#define UROS_ERROR_RMW_TRANSPORT        0b0001 /* Failed to create RMW trnsport */
#define UROS_ERROR_FREERTOS_ALLOC       0b0010 /* Failed to allocate memory for freeRTOS */ 
#define UROS_ERROR_RCL_SUPPORT          0b0100 /* Failed to connect wiwth microros agent or create rcl support */
#define UROS_ERROR_RCL_NODE             0b1000 /* Failed to initialize node */

// #define UROS_INIT_STATUS_NONE           0b0000
// #define UROS_INIT_STATUS_RMW_TRANSPORT  0b0001
// #define UROS_INIT_STATUS_FREERTOS_ALLOC 0b0010
// #define UROS_INIT_STATUS_RCL_SUPPORT    0b0100
// #define UROS_INIT_STATUS_OK             0b0111

/* states of uros app */
enum UROS_STATE{
    UROS_NOT_INITIALIZED    = 0,
    UROS_INITIALIZING       = 1,
    UROS_WAITING_FOR_AGENT  = 2,
    UROS_RUNNING            = 3,
    UROS_ERROR              = 4
};

/* typedef struct of the microros app */
struct{
    rcl_allocator_t         allocator;
    rclc_support_t          support;
    enum UROS_STATE         state;
    uint8_t                 init_status;
    uint8_t                 error_code;
    rmw_ret_t               rmw_ret;
    rcl_ret_t               rcl_ret;
}typedef uros_app_t;

extern uros_app_t uros;

/* microros functions */
bool cubemx_transport_open(struct uxrCustomTransport * transport);
bool cubemx_transport_close(struct uxrCustomTransport * transport);
size_t cubemx_transport_write(struct uxrCustomTransport* transport, const uint8_t * buf, size_t len, uint8_t * err);
size_t cubemx_transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err);

void * microros_allocate(size_t size, void * state);
void microros_deallocate(void * pointer, void * state);
void * microros_reallocate(void * pointer, size_t size, void * state);
void * microros_zero_allocate(size_t number_of_elements, size_t size_of_element, void * state);

int start_HyperDog_UROS_APP(UART_HandleTypeDef* huart);
bool initMicroROS(UART_HandleTypeDef* huart);
void restartMicroROS();


void _init_rcl_support();

#ifdef __cplusplus
}
#endif
#endif //_HYPERDOG_UROS_APP_H_