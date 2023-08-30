#include "leg_motors.h"
#include <string.h>

LegMotor_TypeDef** legMotor;


hyperdog_uros_msgs__srv__InitLegMotors_Response*
check_init_motor_valid(hyperdog_uros_msgs__msg__InitMotor* init_msg)
{
    hyperdog_uros_msgs__srv__InitLegMotors_Response* res;
    res->done = true;
    if(init_msg->params.can_id <1 && init_msg->params.can_id > 255){
        res->done=false;
        strcpy(&res->error_msg.data, "can_id must be in range of 1~225!");
    }          
    if(init_msg->params.position.min != -init_msg->params.position.max){
        res->done=false;
        strcpy(&res->error_msg.data, "max/min position values are not valid!");
    }     
    if(init_msg->params.velocity.min != -init_msg->params.velocity.max){
        res->done=false;
        strcpy(&res->error_msg.data, " max/min velocity values are not valid!");
    }
    if(init_msg->params.kp.min != 0 && init_msg->params.kp.max != 500 ){
        res->done=false;
        strcpy(&res->error_msg.data, "max/min kp values are not valid");
    }    
    if(init_msg->params.kd.min != 0 && init_msg->params.kd.max != 5){
        res->done=false;
        strcpy(&res->error_msg.data, "max/min kd values are not valid");
    }       
    if(init_msg->params.i_ff.min != -init_msg->params.i_ff.max){
        res->done=false;
        strcpy(&res->error_msg.data, "max/min i_ff values are not valid");
    }             

    if(init_msg->ctrl_limits.position.min < init_msg->params.position.min 
    && init_msg->ctrl_limits.position.max > init_msg->params.position.max){
        res->done=false;
        strcpy(&res->error_msg.data, "position ctrl limits of should be within the motor position params!");
    }    
    if(init_msg->ctrl_limits.velocity.min < init_msg->params.velocity.min 
    && init_msg->ctrl_limits.velocity.max > init_msg->params.velocity.max){
        res->done=false;
        strcpy(&res->error_msg.data, "velocity ctrl limits should be within the motor velocity params!");
    }   
    if(init_msg->ctrl_limits.current.min < -MAX_MOTOR_CURRENT
    && init_msg->ctrl_limits.current.max > MAX_MOTOR_CURRENT){
        res->done=false;
        strcpy(&res->error_msg.data, "motor current ctrl limits should be within max motor current!");
    }                
    return res;
}

bool init_motorCAN(LegMotor_TypeDef* m, CAN_HandleTypeDef* hcan){
    /* copy hcan pointer to motor instance */
    m->hcan = hcan;
    /* config can rx filter */
    m->canRx.filter.FilterMode = CAN_FILTERMODE_IDMASK;
    m->canRx.filter.FilterScale = CAN_FILTERSCALE_32BIT;
    m->canRx.filter.FilterIdHigh = 0 << 5; // motors sends can frame with Id number 0, 1st byte of data frame is the motor Id
    m->canRx.filter.FilterIdLow  = 0x0;
    m->canRx.filter.FilterMaskIdHigh = 0xFFF;
    m->canRx.filter.FilterMaskIdLow = 0;
    m->canRx.filter.FilterFIFOAssignment = CAN_FilterFIFO0;
    m->canRx.filter.FilterActivation = ENABLE;
    // motor[m].canRx.filter.FilterBank = filterbank;
    HAL_CAN_ConfigFilter(hcan, &m->canRx.filter);

    /* config can tx header */
    m->canTx.header.StdId = m->self.params.can_id;
    m->canTx.header.IDE = CAN_ID_STD;
    m->canTx.header.DLC = NUM_OF_CAN_TX_BYETS;
    m->canTx.header.RTR = CAN_RTR_DATA;

    /* If there is a CAN state error, update motor init_state, state and error_code */
    if(m->hcan->ErrorCode == HAL_ERROR)
    {
        m->init_status &= ~MOTOR_INIT_STATUS_CAN_SET;
        m->state.error_code |= MOTOR_ERROR_HAL_CAN;
        m->state.is_error = 1;
        m->debug_state = ERROR;
        return 0;
    }else{
        m->init_status |= MOTOR_INIT_STATUS_CAN_SET;
        m->state.error_code &= ~MOTOR_ERROR_HAL_CAN;
        m->state.is_error = 0;
        m->debug_state = MOTOR_INITIALIZED;
        return 1;
    }    
}


void init_legMotors(CAN_HandleTypeDef* hcan, 
hyperdog_uros_msgs__srv__InitLegMotors_Request* req, 
hyperdog_uros_msgs__srv__InitLegMotors_Response* res)
{
    /* create 2D array of legMotor object, [leg][joint] */
    legMotor = (LegMotor_TypeDef**)malloc(NUM_OF_LEGS * sizeof(LegMotor_TypeDef*));
    for (int i=0; i<NUM_OF_LEGS; i++){
        legMotor[i] = (LegMotor_TypeDef*)malloc(NUM_OF_JOINTS_PER_LEG * sizeof(LegMotor_TypeDef));
    }
    
    /* FR Leg joint motors {0:HIP_ROLL, 1:HIP_PITCH, 2:KNEE} */
    if(check_init_motor_valid(&req->data.fr_hip_roll)->done){
        legMotor[0][0].self = req->data.fr_hip_roll;
        legMotor[0][0].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[0][0], hcan)){
            legMotor[0][0].state.error_code &= ~ MOTOR_ERROR_NOT_INITIALIZED;
            legMotor[0][0].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        legMotor[0][0].state.error_code |= MOTOR_ERROR_NOT_INITIALIZED;
        legMotor[0][0].state.is_error = 1;
        legMotor[0][0].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[0][0].debug_state = MOTOR_NOT_INITIALIZED;
    }
    if(check_init_motor_valid(&req->data.fr_hip_pitch)->done){
        legMotor[0][1].self = req->data.fr_hip_pitch;
        legMotor[0][1].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[0][1], hcan)){
            legMotor[0][1].state.error_code &= ~ MOTOR_ERROR_NOT_INITIALIZED;
            legMotor[0][1].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        legMotor[0][1].state.error_code |= MOTOR_ERROR_NOT_INITIALIZED;
        legMotor[0][1].state.is_error = 1;
        legMotor[0][1].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[0][1].debug_state = MOTOR_NOT_INITIALIZED;
    }
    if(check_init_motor_valid(&req->data.fr_knee)->done){
        legMotor[0][2].self = req->data.fr_knee;
        legMotor[0][2].state.is_error = 0;
        legMotor[0][2].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[0][2], hcan)){
            legMotor[0][2].state.error_code &= ~ MOTOR_ERROR_NOT_INITIALIZED;
            legMotor[0][2].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        legMotor[0][2].state.error_code |= MOTOR_ERROR_NOT_INITIALIZED;
        legMotor[0][2].state.is_error = 1;
        legMotor[0][2].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[0][2].debug_state = MOTOR_NOT_INITIALIZED;
    }

    /* FL Leg joint motors {0:HIP_ROLL, 1:HIP_PITCH, 2:KNEE} */
    if(check_init_motor_valid(&req->data.fl_hip_roll)->done)     {
        legMotor[1][0].self = req->data.fl_hip_roll;
        legMotor[1][0].state.is_error = 0;
        legMotor[1][0].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[1][0], hcan)){
            legMotor[1][0].state.error_code &= ~ MOTOR_ERROR_NOT_INITIALIZED;
            legMotor[1][0].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        legMotor[1][0].state.error_code |= MOTOR_ERROR_NOT_INITIALIZED;
        legMotor[1][0].state.is_error = 1;
        legMotor[1][0].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[1][0].debug_state = MOTOR_NOT_INITIALIZED;
    }
    if(check_init_motor_valid(&req->data.fl_hip_pitch)->done)    {
        legMotor[1][1].self = req->data.fl_hip_pitch;  
        legMotor[1][1].state.is_error = 0;
        legMotor[1][1].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[1][1], hcan)){
            legMotor[1][1].state.error_code &= ~ MOTOR_ERROR_NOT_INITIALIZED;
            legMotor[1][1].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        legMotor[1][1].state.error_code |= MOTOR_ERROR_NOT_INITIALIZED;
        legMotor[1][1].state.is_error = 1;
        legMotor[1][1].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[1][1].debug_state = MOTOR_NOT_INITIALIZED;
    }
    if(check_init_motor_valid(&req->data.fl_knee)->done)         {
        legMotor[1][2].self = req->data.fl_knee;    
        legMotor[1][2].state.is_error = 0;
        legMotor[1][2].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[1][2], hcan)){
            legMotor[1][2].state.error_code &= ~ MOTOR_ERROR_NOT_INITIALIZED;
            legMotor[1][2].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        legMotor[1][2].state.error_code |= MOTOR_ERROR_NOT_INITIALIZED;
        legMotor[1][2].state.is_error = 1;
        legMotor[1][2].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[1][2].debug_state = MOTOR_NOT_INITIALIZED;
    }
    
    /* RR Leg joint motors {0:HIP_ROLL, 1:HIP_PITCH, 2:KNEE} */
    if(check_init_motor_valid(&req->data.rr_hip_roll)->done)     {
        legMotor[2][0].self = req->data.rr_hip_roll;
        legMotor[2][0].state.is_error = 0;
        legMotor[2][0].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[2][0], hcan)){
            legMotor[2][0].state.error_code &= ~ MOTOR_ERROR_NOT_INITIALIZED;
            legMotor[2][0].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        legMotor[2][0].state.error_code |= MOTOR_ERROR_NOT_INITIALIZED;
        legMotor[2][0].state.is_error = 1;
        legMotor[2][0].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[2][0].debug_state = MOTOR_NOT_INITIALIZED;
    }
    if(check_init_motor_valid(&req->data.rr_hip_pitch)->done)    {
        legMotor[2][1].self = req->data.rr_hip_pitch;
        legMotor[2][1].state.is_error = 0;
        legMotor[2][1].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[2][1], hcan)){
            legMotor[2][1].state.error_code &= ~ MOTOR_ERROR_NOT_INITIALIZED;
            legMotor[2][1].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        legMotor[2][1].state.error_code |= MOTOR_ERROR_NOT_INITIALIZED;
        legMotor[2][1].state.is_error = 1;
        legMotor[2][1].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[2][1].debug_state = MOTOR_NOT_INITIALIZED;
    }
    if(check_init_motor_valid(&req->data.rr_knee)->done)         {
        legMotor[2][2].self = req->data.rr_knee;
        legMotor[2][2].state.is_error = 0;
        legMotor[2][2].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[2][2], hcan)){
            legMotor[2][2].state.error_code &= ~ MOTOR_ERROR_NOT_INITIALIZED;
            legMotor[2][2].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        legMotor[2][2].state.error_code |= MOTOR_ERROR_NOT_INITIALIZED;
        legMotor[2][2].state.is_error = 1;
        legMotor[2][2].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[2][2].debug_state = MOTOR_NOT_INITIALIZED;
    }

    /* RL Leg joint motors {0:HIP_ROLL, 1:HIP_PITCH, 2:KNEE} */
    if(check_init_motor_valid(&req->data.rl_hip_roll)->done)     {
        legMotor[3][0].self = req->data.rl_hip_roll;
        legMotor[3][0].state.is_error = 0;
        legMotor[3][0].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[3][0], hcan)){
            legMotor[3][0].state.error_code &= ~ MOTOR_ERROR_NOT_INITIALIZED;
            legMotor[3][0].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        legMotor[3][0].state.error_code |= MOTOR_ERROR_NOT_INITIALIZED;
        legMotor[3][0].state.is_error = 1;
        legMotor[3][0].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[3][0].debug_state = MOTOR_NOT_INITIALIZED;
    }
    if(check_init_motor_valid(&req->data.rl_hip_pitch)->done)    {
        legMotor[3][1].self = req->data.rl_hip_pitch;
        legMotor[3][1].state.is_error = 0;
        legMotor[3][1].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[3][1], hcan)){
            legMotor[3][1].state.error_code &= ~ MOTOR_ERROR_NOT_INITIALIZED;
            legMotor[3][1].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        legMotor[3][1].state.error_code |= MOTOR_ERROR_NOT_INITIALIZED;
        legMotor[3][1].state.is_error = 1;
        legMotor[3][1].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[3][1].debug_state = MOTOR_NOT_INITIALIZED;
    }
    if(check_init_motor_valid(&req->data.rl_knee)->done)         {
        legMotor[3][2].self = req->data.rl_knee;
        legMotor[3][2].state.is_error = 0;
        legMotor[3][2].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[3][2], hcan)){
            legMotor[3][2].state.error_code &= ~ MOTOR_ERROR_NOT_INITIALIZED;
            legMotor[3][2].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        legMotor[3][2].state.error_code |= MOTOR_ERROR_NOT_INITIALIZED;
        legMotor[3][2].state.is_error = 1;
        legMotor[3][2].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[3][2].debug_state = MOTOR_NOT_INITIALIZED;
    }
}




void destroy_legMotors(){
    for(int i=0; i<NUM_OF_LEGS; i++){
        free(legMotor[i]);
    }
    free(legMotor);
}