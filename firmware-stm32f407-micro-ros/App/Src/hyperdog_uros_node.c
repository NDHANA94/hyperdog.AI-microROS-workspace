
#include "main.h"
#include "hyperdog_uros_node.h"
#include "motor_typedefs.h"

hyperdogUROS_Node_t hyperdog_node;
Motor_TypeDef motor[NUM_OF_MOTORS];

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

        resetMicroROS(); 
    }
    /* if no error */
    hyperdog_node.error_code &= ~NODE_HYPERDOG_ERROR_FAILED_INIT;

    /* create motors states publisher */



}

void _init_motors_state_publisher()
{
    hyperdog_uros_msgs__msg__MotorStates mstate;
    mstate.id = 1;
    char* name = "FR_LEG";
    mstate.motor_name.size = strlen(name);
    mstate.motor_name.capacity =  10;
    mstate.motor_name.data = (char*) malloc(mstate.motor_name.capacity * sizeof(char));

    hyperdog_node.motors_states_msg.fr_hip_roll = mstate;

    
}

void spin_hyperdog_node()
{
    // while (uros.error_code!= UROS_ERROR_)

}


/**
 * To destroy all the entities of the hyperdog_node and node itself
 */
void destroy_hyperdog_node(){
    /* first, destroy all the node's entities */
    /// TODO: 

    /* then destroy the node itself */
    rcl_node_fini(&hyperdog_node.node);

}

/**
 * 
 */
// void _create