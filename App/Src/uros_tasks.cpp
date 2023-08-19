#include <stdio.h>
#include <string.h>
#include "usart.h"

#include "uros_tasks.h"
#include "minicheetah_motor.h"


rcl_allocator_t allocator;
rclc_support_t support;
rcl_node_t node;
rcl_publisher_t publisher;
std_msgs__msg__Int32 msg;
std_msgs__msg__Float32MultiArray motor_feedback_msg;

rmw_ret_t ret_rmw;
rcl_ret_t ret_rcl;

Motor m;

void init_uros_node()
{
    // micro-ROS configuration
    rmw_err_code = rmw_uros_set_custom_transport(
                true,
                (void *) &huart2,
                cubemx_transport_open,
                cubemx_transport_close,
                cubemx_transport_write,
                cubemx_transport_read);

    rcl_allocator_t freeRTOS_allocator = rcutils_get_zero_initialized_allocator();
    freeRTOS_allocator.allocate = microros_allocate;
    freeRTOS_allocator.deallocate = microros_deallocate;
    freeRTOS_allocator.reallocate = microros_reallocate;
    freeRTOS_allocator.zero_allocate =  microros_zero_allocate;

    if (!rcutils_set_default_allocator(&freeRTOS_allocator)) {
        printf("Error on default allocators (line %d)\n", __LINE__); 
    }

    // micro-ROS app
    allocator = rcl_get_default_allocator();

    //create init_options
    rcl_err_code = rclc_support_init(&support, 0, NULL, &allocator);

    // create node
    rcl_err_code = rclc_node_init_default(&node, "motor_node", "", &support);

    // create msg
    motor_feedback_msg.data.capacity = 10; // to allocate memory
    motor_feedback_msg.data.data = (float*) malloc(motor_feedback_msg.data.capacity * sizeof(float));

    // create publisher
    rcl_err_code = rclc_publisher_init_default(
                    &publisher,
                    &node,
                    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32MultiArray),
                    "motor_feedback");

}


void spin_uros_node(int os_delay)
{
    msg.data = 0;
    
    while(1)
    {
        
        motor_feedback_msg.data.size = 6;
        for(int i=0; i<6; i++){
            motor_feedback_msg.data.data[i] = 10.0; // can_rx_data[i]
        }

        rcl_err_code = rcl_publish(&publisher, &motor_feedback_msg, NULL);
        if (rcl_err_code != RCL_RET_OK)
        {
        printf("Error publishing (line %d)\n", __LINE__); 
        }
        printf("microros\n");
        // motor.send_heartbeat();
        osDelay(os_delay);
    }
}



