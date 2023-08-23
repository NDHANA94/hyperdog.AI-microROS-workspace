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

#include <stdio.h>
#include <string.h>
#include "usart.h"

#include "uros_tasks.h"
#include "minicheetah_motor.h"


UROS_t uros;



void init_uros_node()
{   
    /* config micro ros */
    if(_config_uros()){
        /* allocate memory for FreeRTOS */
        if(_maloc4FreeRTOS())
        {
            /* init micro-ROS app */
            uros.allocator = rcl_get_default_allocator(); 

            /* create rcl support */
            a:  
            if(_create_rcl_support())
            {
                /* create node */
                if(_create_uros_node())
                {
                    /* create motor feedback publisher */
                    _create_motor_feedback_pub();
                }
            }

            /* if failed to init support */
            else
            {
                while((uros.status & UROS_STATUS_RCL_SUPPORT) != UROS_STATUS_RCL_SUPPORT)
                {
                    uros.state = UROS_WAITING_FOR_AGENT;
                    osDelay(100); /*!< othewise FreeRTOS has no time space to run other tasks*/
                    goto a;
                }
            } 
        }
    }
}


/**
 * @brief motor_node spin.
 * 
 */
void spin_uros_node(int os_delay)
{
    uros.motor_feedback_msg.data.size = uros.motor_feedback_msg.data.capacity;
    while(1)
    {
        if (uros.status == 0b00011111)
        {
            for(int m=0; m<NUM_OF_MOTORS; m++)
            {
                uros.motor_feedback_msg.data.data[0] = motor[m].id;
                uros.motor_feedback_msg.data.data[1] = motor[m].feedback.position;
                uros.motor_feedback_msg.data.data[2] = motor[m].feedback.velocity;
                uros.motor_feedback_msg.data.data[3] = motor[m].feedback.current;
                uros.motor_feedback_msg.data.data[4] = motor[m].feedback.vb;
                uros.rcl_ret = rcl_publish(&uros.publisher, &uros.motor_feedback_msg, NULL);
                if (uros.rcl_ret != RCL_RET_OK)
                {
                    uros.state = UROS_ERROR;
                    uros.error_code |= UROS_ERROR_RCL_MOTOR_FB_PUB;
                    uros.state = UROS_WAITING_FOR_AGENT;
                    init_uros_node();                 
                }
                else{
                    uros.state = UROS_RUNNING;
                }
            }   
        }
        else{
            uros.state = UROS_WAITING_FOR_AGENT;
            init_uros_node();
        }
        
        printf("microros\n");
        // motor.send_heartbeat();
        osDelay(os_delay);
    }
}


/**
 * @brief To configure micro-ROS.
 * 
 * @return true: if rcl support is successfully created.
 * @return false: if error.
 */
bool _config_uros()
{
    /* micro-ROS configuration */
    uros.rmw_ret = rmw_uros_set_custom_transport(
                    true,(void *) &huart2, 
                    cubemx_transport_open,
                    cubemx_transport_close, 
                    cubemx_transport_write,
                    cubemx_transport_read);

    /* check error */
    if(uros.rmw_ret != RMW_RET_OK)
    {
        uros.state = UROS_ERROR;
        uros.status &= ~UROS_STATUS_CONFIG;
        uros.error_code |= UROS_ERROR_RMW_TRANSPORT;
        return 0;
    }

    /* if no error */
    if(uros.state != UROS_WAITING_FOR_AGENT) uros.state = UROS_INITIALIZING;
    uros.status |= UROS_STATUS_CONFIG;
    uros.error_code &= ~UROS_ERROR_RMW_TRANSPORT;
    return 1;
}

/**
 * @brief To allocate memory for FreeRTOS.
 * 
 * @return true: if rcl support is successfully created.
 * @return false: if error.
 */
bool _maloc4FreeRTOS()
{
    /* Allocationg memory for FreeRTOS */
    rcl_allocator_t freeRTOS_allocator = rcutils_get_zero_initialized_allocator();
    freeRTOS_allocator.allocate = microros_allocate;
    freeRTOS_allocator.deallocate = microros_deallocate;
    freeRTOS_allocator.reallocate = microros_reallocate;
    freeRTOS_allocator.zero_allocate =  microros_zero_allocate;

    /* allocate and check error */
    if (!rcutils_set_default_allocator(&freeRTOS_allocator))
    {
        uros.state = UROS_ERROR;
        uros.status &= ~UROS_STATUS_ALLOC_FREERTOS;
        uros.error_code |= UROS_ERROR_FREERTOS_ALLOC;
        // printf("Error on default allocators (line %d)\n", __LINE__); 
        return 0;
    }

    /* if no error */
    if(uros.state != UROS_WAITING_FOR_AGENT)uros.state = UROS_INITIALIZING;
    uros.status |= UROS_STATUS_ALLOC_FREERTOS;
    uros.error_code &= ~UROS_ERROR_FREERTOS_ALLOC;
    return 1;
}


/**
 * @brief To create the rcl support.
 * 
 * @return true: if rcl support is successfully created.
 * @return false: if error.
 */
bool _create_rcl_support()
{
    /* If allready initialized, destroy */
    if((uros.status & UROS_STATUS_RCL_SUPPORT)  == UROS_STATUS_RCL_SUPPORT  ){_destroy_support();}

    /* initialize */
    uros.rcl_ret = rclc_support_init(&uros.support, 0, NULL, &uros.allocator);

    /* check error */
    if(uros.rcl_ret != RCL_RET_OK)
    {
        uros.state = UROS_WAITING_FOR_AGENT;            /*!< update state           */
        uros.status &= ~UROS_STATUS_RCL_SUPPORT;        /*!< reset rcl support      */
        uros.error_code |= UROS_ERROR_RCL_SUPPORT_INIT; /*!< set error              */
        return 0;
    }
    /* if no error */
    if(uros.state != UROS_WAITING_FOR_AGENT)uros.state = UROS_INITIALIZING; /*!< update state           */
    uros.status |= UROS_STATUS_RCL_SUPPORT;                                 /*!< set rcl support        */
    uros.error_code &= ~UROS_ERROR_RCL_SUPPORT_INIT;                        /*!< set error              */
    return 1;
}


/**
 * @brief To create the main node "motor_node".
 * 
 * @return true: if node is successfully created.
 * @return false: if error.
 */
bool _create_uros_node()
{
    /* If already exist, destroy the node and its entities (pubs, subs, etc.) */
    if((uros.status & UROS_STATUS_MOTOR_FB_PUB) == UROS_STATUS_MOTOR_FB_PUB ){_destroy_node();}
    if((uros.status & UROS_STATUS_NODE)         == UROS_STATUS_NODE         ){_destroy_node();}

    /* Initialize the node */
    uros.rcl_ret = rclc_node_init_default(&uros.node, "motor_node", "", &uros.support);

    /* check error */
    if (uros.rcl_ret != RCL_RET_OK)
    {
        uros.state = UROS_ERROR;                            /*!< update state */
        uros.status &= ~UROS_STATUS_NODE;
        uros.error_code |= UROS_ERROR_RCL_NODE_INIT;        /*!< set error */
        return 0;
    }    

    /* if no error */                  
    if(uros.state != UROS_WAITING_FOR_AGENT)uros.state = UROS_INITIALIZING; /*!< update state */
    uros.status |= UROS_STATUS_NODE;
    uros.error_code &= ~UROS_ERROR_RCL_NODE_INIT;                           /*!< reset error */
    return 1;
}

/**
 * @brief To create the motoer feedback publisher
 * 
 * @return true: if publisher is successfully created.
 * @return false: if error.
 */
bool _create_motor_feedback_pub()
{
    /* create msg */
    uros.motor_feedback_msg.data.capacity = 5;              /*  to allocate memory */
    uros.motor_feedback_msg.data.data = (float*) malloc(uros.motor_feedback_msg.data.capacity * sizeof(float));

    /* initialize publisher */
    uros.rcl_ret = rclc_publisher_init_default(
                    &uros.publisher,
                    &uros.node,
                    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32MultiArray),
                    "motor_feedback");
    
    /* check error */
    if(uros.rcl_ret == RCL_RET_ERROR)
    {
        uros.state = UROS_ERROR;                            /*!< update state */
        uros.status &= ~UROS_STATUS_MOTOR_FB_PUB;
        uros.error_code |= UROS_ERROR_RCL_MOTOR_FB_PUB_INIT;         /*!< set error */
        return 0;
    }

    /* if no error */
    if(uros.state != UROS_WAITING_FOR_AGENT) uros.state = UROS_INITIALIZING; 
    uros.status |= UROS_STATUS_MOTOR_FB_PUB;
    uros.error_code &= ~UROS_ERROR_RCL_MOTOR_FB_PUB_INIT;            /*!< set error */
    return 1;
}


/**
 * @brief To destroy the rcl support
 * 
 */
void _destroy_support()
{
    _destroy_node();
    uros.rcl_ret = rclc_support_fini(&uros.support);
    uros.state = UROS_INITIALIZING;
    uros.status &= ~ UROS_STATUS_RCL_SUPPORT;
    uros.error_code &= ~ UROS_ERROR_RCL_SUPPORT_INIT;
}

/**
 * @brief To destroy the node and its entities
 * 
 */
void _destroy_node()
{
    if((uros.status & UROS_STATUS_MOTOR_FB_PUB) == UROS_STATUS_MOTOR_FB_PUB)
    {
        /* destroy node entities */
        uros.rcl_ret = rcl_publisher_fini(&uros.publisher, &uros.node);
        uros.status &= ~UROS_STATUS_MOTOR_FB_PUB;
        uros.error_code &= ~ UROS_ERROR_RCL_MOTOR_FB_PUB_INIT;
    }
    
    if((uros.status & UROS_STATUS_NODE) == UROS_STATUS_NODE)
    {
        /* destroy node itself */
        uros.rcl_ret = rcl_node_fini(&uros.node);
        uros.state = UROS_NODE_DESTROYED;
        uros.status &= ~UROS_STATUS_NODE;
        uros.error_code &= ~ UROS_ERROR_RCL_NODE_INIT;
    } 
}






