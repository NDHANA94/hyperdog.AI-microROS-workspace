#include "uros.h"


/**
 * Initialize micro-ROS 
 * @param *huart address of uart interface to cmmunicate with uros agent
 * @return if succeeded 1, else 0
 */
bool init_uros(UART_HandleTypeDef* huart)
{
    /* Initialize transport */
    rmw_ret_t ret;
    ret = rmw_uros_set_custom_transport(
        true, 
        (void *) &huart, 
        cubemx_transport_open, 
        cubemx_transport_close, 
        cubemx_transport_write, 
        cubemx_transport_read);
    
    if(ret == RMW_RET_ERROR){return 0;}

    /* allocate memory for freeRTOS */ 
    rcl_allocator_t freeRTOS_allocator = rcutils_get_zero_initialized_allocator();
    freeRTOS_allocator.allocate = microros_allocate;
    freeRTOS_allocator.deallocate = microros_deallocate;
    freeRTOS_allocator.reallocate = microros_reallocate;
    freeRTOS_allocator.zero_allocate =  microros_zero_allocate;
    if (!rcutils_set_default_allocator(&freeRTOS_allocator)){return 0;}

    return 1;
}