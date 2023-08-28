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

#include "hyperdog_uros_app.h"
#include "hyperdog_uros_node.h"


uros_app_t uros;


/**========================================================================================
 * To start the micro-ROS
 * 
 * 
 ========================================================================================*/
int start_HyperDog_UROS_APP(UART_HandleTypeDef* huart)
{
    /* Initialize micro-ROS ----------------------------------------------------------*/
    if(initMicroROS(huart)){
        /* Initialize node 1 ----------------------------------------*/
        init_hyperdog_node();
        rclc_executor_spin(&hyperdog_node.executor);

        /* clean ---------------------------------------------------*/
        _destroy_hyperdog_node();
        return 0;
    }
    return -1;
}




/**============================================================================================
 * To initialize the micro ros.
 * \return 1 if succeeded, 0 if failed.
 ============================================================================================*/
bool initMicroROS(UART_HandleTypeDef* huart)
{
    uros.state = UROS_INITIALIZING; // update state

    /* initialize transport -----------------------------------------------------------*/
    uros.rmw_ret = rmw_uros_set_custom_transport(
        true, 
        (void *) huart, 
        cubemx_transport_open, 
        cubemx_transport_close, 
        cubemx_transport_write, 
        cubemx_transport_read);

    /* check error and update state and error code ------------------------------------*/
    if(uros.rmw_ret != RMW_RET_OK){
        uros.state = UROS_ERROR; //update state
        uros.error_code |= UROS_ERROR_RMW_TRANSPORT; // set rmw transport error
        return 0;
    }
    uros.error_code &= ~ UROS_ERROR_RMW_TRANSPORT; //reset rmw transport error 

    /* allocate memory for FreeRTOS ---------------------------------------------------*/
    rcl_allocator_t freeRTOS_allocator = rcutils_get_zero_initialized_allocator();
    freeRTOS_allocator.allocate = microros_allocate;
    freeRTOS_allocator.deallocate = microros_deallocate;
    freeRTOS_allocator.reallocate = microros_reallocate;
    freeRTOS_allocator.zero_allocate = microros_zero_allocate;
    if (!rcutils_set_default_allocator(&freeRTOS_allocator)){
        uros.state = UROS_ERROR;
        uros.error_code |= UROS_ERROR_FREERTOS_ALLOC;
        return 0;
    }
    uros.allocator = rcl_get_default_allocator();
    uros.error_code &= ~UROS_ERROR_FREERTOS_ALLOC; //reset rcl freeRTOS alloc error

    /* create rcl support -------------------------------------------------------------*/
    _init_rcl_support();

    return 1;
}


/**
 * To initialize rclc support
 * This function will be waiting until the micro-ROS agent is connected.
*/
void _init_rcl_support()
{
    init_support:
    /* initialize rclc support object-------------------------------------*/
    uros.state = UROS_WAITING_FOR_AGENT;
    uros.rcl_ret = rclc_support_init(&uros.support, 0, NULL, &uros.allocator);

    /* check error -------------------------------------------------------*/
    if(uros.rcl_ret != RCL_RET_OK){
        fail:
        /* destroy rclc support ---------------------------*/
        uros.rcl_ret = rclc_support_fini(&uros.support);

        /* update state and error code -------------------*/
        if(uros.rcl_ret != RCL_RET_OK){
            uros.state = UROS_ERROR;
            uros.error_code |= UROS_ERROR_RCL_SUPPORT;
            goto fail;
        }
        uros.error_code |= UROS_ERROR_RCL_SUPPORT;
        goto init_support;
    }
    /* if no error ------------------------------------------------------*/
    uros.state = UROS_RUNNING;
    uros.error_code &= ~UROS_ERROR_RCL_SUPPORT;
}

/**
 * Call this function in case of the connection with agent is lost while running the nodes.
 * This will destroy all the nodes, and rclc support. then wait till the the agent is back online.
 * Once the agent is connected all the nodes will be initialized again.
 */
void restartMicroROS()
{
    uros.state = UROS_WAITING_FOR_AGENT;

    /* destroy all the initialized nodes and their entities------------*/
    /// TODO: Call the function of destroy_node of each nodes
    _destroy_hyperdog_node();
    // destroy_node_x();
    // destroy_node_y();
    // ....


    /* destroy the rclc support--------------------------------------- */
    fini:
    uros.rcl_ret = rclc_support_fini(&uros.support);
    if(uros.rcl_ret != RCL_RET_OK){
        osDelay(100);
        goto fini;
    }

    /* initialize rcl support object again ----------------------------*/
    _init_rcl_support();

    /* initialize all the nodes again ---------------------------------*/
    /// TODO: call the initialization function for each nodes.
    init_hyperdog_node();
    // init_node_x();
    // init_node_y();
    // ...


    /* spin the executors  --------------------------------------------*/
    rclc_executor_spin(&hyperdog_node.executor);
    // rclc_executor_spin(& node_x.executor)
    // rclc_executor_spin(& node_y.executor)

    
}