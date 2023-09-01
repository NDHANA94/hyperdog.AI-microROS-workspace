#include "leg_motors.h"
#include <string.h>

LegMotor_TypeDef** legMotor;
CANRxMessage_TypeDef  canRx;

bool motor_objects_created;
bool can_filter_created;

uint8_t motor_enable_cmd[NUM_OF_CAN_TX_BYETS] = MOTOR_ENABLE_CMD;
uint8_t motor_disable_cmd[NUM_OF_CAN_TX_BYETS] = MOTOR_DISABLE_CMD;
uint8_t motor_setzero_cmd[NUM_OF_CAN_TX_BYETS] = MOTOR_SETZERO_CMD;

uint16_t
check_init_motor_valid(hyperdog_uros_interfaces__msg__InitMotor* init_msg)
{
    uint16_t error_code = 0;

    if(init_msg->params.can_id <1 && init_msg->params.can_id > 255){
        error_code |= MOTOR_PARAM_ERROR_CAN_ID;
    }          
    if(init_msg->params.position.min != -init_msg->params.position.max){
        error_code |= MOTOR_PARAM_ERROR_P;
    }     
    if(init_msg->params.velocity.min != -init_msg->params.velocity.max){
        error_code |= MOTOR_PARAM_ERROR_V;
    }
    if(init_msg->params.kp.min != 0 && init_msg->params.kp.max != 500 ){
        error_code |= MOTOR_PARAM_ERROR_KP;
    }    
    if(init_msg->params.kd.min != 0 && init_msg->params.kd.max != 5){
        error_code |= MOTOR_PARAM_ERROR_KD;
    }       
    if(init_msg->params.i_ff.min != -init_msg->params.i_ff.max){
        error_code |= MOTOR_PARAM_ERROR_IFF;
    }             

    if(init_msg->ctrl_limits.position.min < init_msg->params.position.min 
    || init_msg->ctrl_limits.position.max > init_msg->params.position.max){
        error_code |= MOTOR_PARAM_ERROR_CTRL_P;
    }    
    if(init_msg->ctrl_limits.velocity.min < init_msg->params.velocity.min 
    || init_msg->ctrl_limits.velocity.max > init_msg->params.velocity.max){
        error_code |= MOTOR_PARAM_ERROR_CTRL_V;
    }   
    if(init_msg->ctrl_limits.current.min < -MAX_MOTOR_CURRENT
    || init_msg->ctrl_limits.current.max > MAX_MOTOR_CURRENT){
        error_code |= MOTOR_PARAM_ERROR_CTRL_I;
    }               
    return error_code;
}


/**
 * To initialize can interface for the motor.
 * This function does following;
 * `1`: pointing motor obj's can interface to given `hcan`
 * `2`: Configuring CAN Rx Filter if it's already no initialized.
 * `3`: Setting Motor CAN ID to the Tx header
 * `4`: Setting CAN Tx buffer with 8 bytes data field
 * `5`: Checking HAL_ERROR in hcan instance.
 * `6`: update motor error code
 * `7`: update motor init_status
 * `8`: update motor debug_status
 * 
 * @param m pointer to initialized LegMotor_TypeDef type instance.
 * @param hcan pointer to initialized can handle typedef
 */
bool init_motorCAN(LegMotor_TypeDef* m, CAN_HandleTypeDef* hcan){
    /* copy hcan pointer to motor instance */
    m->hcan = hcan;
    /* point canRx of the motor to global canRx */
    m->canRx = &canRx;
    /* config global can rx filter */
    if(!can_filter_created){
        canRx.filter.FilterMode = CAN_FILTERMODE_IDMASK;
        canRx.filter.FilterScale = CAN_FILTERSCALE_32BIT;
        canRx.filter.FilterIdHigh = 0 << 5; // motors sends can frame with Id number 0, 1st byte of data frame is the motor Id
        canRx.filter.FilterIdLow  = 0x0;
        canRx.filter.FilterMaskIdHigh = 0xFFF;
        canRx.filter.FilterMaskIdLow = 0;
        canRx.filter.FilterFIFOAssignment = CAN_FilterFIFO0;
        canRx.filter.FilterActivation = ENABLE;
        // motor[m].canRx.filter.FilterBank = filterbank;
        if(HAL_CAN_ConfigFilter(hcan, &canRx.filter) == HAL_OK){
            can_filter_created = true;
        }
    }
    
    /* config can tx header */
    m->canTx.header.StdId = m->self.params.can_id;
    m->canTx.header.IDE = CAN_ID_STD;
    m->canTx.header.DLC = NUM_OF_CAN_TX_BYETS;
    m->canTx.header.RTR = CAN_RTR_DATA;

    /* If there is a CAN state error, update motor init_state, state and error_code */
    if(m->hcan->ErrorCode == HAL_ERROR){ goto can_error; }
    else{ goto can_ok; }    

    can_error:
    m->init_status &= ~MOTOR_INIT_STATUS_CAN_SET;
    m->state.error_code |= MOTOR_ERROR_HAL_CAN;
    m->state.is_error = 1;
    m->debug_state = ERROR;
    return 0;

    can_ok:
    m->init_status |= MOTOR_INIT_STATUS_CAN_SET;
    m->state.error_code &= ~MOTOR_ERROR_HAL_CAN;
    m->state.is_error = 0;
    m->debug_state = MOTOR_INITIALIZED;
    return 1;
}

/* create 2D array of legMotor objects: `legMotor[leg][joint]` */
bool create_motor_objects(LegMotor_TypeDef** m)
{
    
    legMotor = (LegMotor_TypeDef**)malloc(NUM_OF_LEGS * sizeof(LegMotor_TypeDef*));
    for (int i=0; i<NUM_OF_LEGS; i++){
        legMotor[i] = (LegMotor_TypeDef*)malloc(NUM_OF_JOINTS_PER_LEG * sizeof(LegMotor_TypeDef));
    }

    /* initialize states of the motors, otherwise motorstates publisher goes to error state. */
    for(int i=0; i<NUM_OF_LEGS; i++){
        for(int j=0; j<NUM_OF_JOINTS_PER_LEG; j++){
            legMotor[i][j].state.error_code = 0;
            legMotor[i][j].state.is_available = 0;
            legMotor[i][j].state.is_enabled = 0;
            legMotor[i][j].state.is_error = 0;
            legMotor[i][j].state.feedback.can_id = 0;
            legMotor[i][j].state.feedback.position = 0;
            legMotor[i][j].state.feedback.velocity = 0;
            legMotor[i][j].state.feedback.torque = 0;
            legMotor[i][j].state.feedback.vb = 0;
            legMotor[i][j].state.status_msg.data = "";
            legMotor[i][j].state.status_msg.capacity = 200;
            legMotor[i][j].state.status_msg.size = 0;
        }
    }

    motor_objects_created = true;
    return 1;
}

/* To free allocated memory for legMotor objects */
bool destroy_motor_objects()
{
    if(motor_objects_created){
        for(int i=0; i<NUM_OF_LEGS; i++){
            free(legMotor[i]);
        }
        free(legMotor);
        motor_objects_created = false;
        return 1;
    }
    else return 0;
}


/** Initialize legMotor objects by doing following steps.
 * `1`: 
 * if one of motors param or ctrl limit is wrong, service response will be an error
 */
void init_legMotors(CAN_HandleTypeDef* hcan, 
hyperdog_uros_interfaces__srv__InitLegMotors_Request* req, 
hyperdog_uros_interfaces__srv__InitLegMotors_Response* res)
{
    /* create 2D array of legMotor object, [leg][joint] */
    if(!motor_objects_created){create_motor_objects(legMotor);}

    /* FR Leg HIP_ROLL joint motor */
    res->error_code[0] = check_init_motor_valid(&req->data.fr_hip_roll);
    if(res->error_code[0] == 0){
        legMotor[0][0].self = req->data.fr_hip_roll;
        legMotor[0][0].state.is_error = 0;
        legMotor[0][0].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[0][0], hcan)){
            legMotor[0][0].state.error_code &= ~ MOTOR_ERROR_PARAM;
            legMotor[0][0].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        legMotor[0][0].state.is_error = 1;
        legMotor[0][0].state.error_code |= MOTOR_ERROR_PARAM;
        legMotor[0][0].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[0][0].debug_state = MOTOR_NOT_INITIALIZED;
    }
    res->init_status_code[0] = legMotor[0][0].debug_state;

    /* FR Leg HIP_PITCH joint motor */
    res->error_code[1] = check_init_motor_valid(&req->data.fr_hip_pitch);
    if(res->error_code[1] == 0){
        legMotor[0][1].self = req->data.fr_hip_pitch;
        legMotor[0][1].state.is_error = 0;
        legMotor[0][1].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[0][1], hcan)){
            legMotor[0][1].state.error_code &= ~ MOTOR_ERROR_PARAM;
            legMotor[0][1].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        legMotor[0][1].state.is_error = 1;
        legMotor[0][1].state.error_code |= MOTOR_ERROR_PARAM;
        legMotor[0][1].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[0][1].debug_state = MOTOR_NOT_INITIALIZED;
    }
    res->init_status_code[1] = legMotor[0][1].debug_state;

    /* FR Leg KNEE joint motor */
    res->error_code[2] = check_init_motor_valid(&req->data.fr_knee);
    if(res->error_code[2] == 0){
        legMotor[0][2].self = req->data.fr_knee;
        legMotor[0][2].state.is_error = 0;
        legMotor[0][2].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[0][2], hcan)){
            legMotor[0][2].state.error_code &= ~ MOTOR_ERROR_PARAM;
            legMotor[0][2].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        /* update status, states and error */
        legMotor[0][2].state.is_error = 1;
        legMotor[0][2].state.error_code |= MOTOR_ERROR_PARAM;
        legMotor[0][2].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[0][2].debug_state = MOTOR_NOT_INITIALIZED;
    }
    res->init_status_code[2] = legMotor[0][2].debug_state;

    /* FL Leg HIP_ROLL joint motor */
    res->error_code[3] = check_init_motor_valid(&req->data.fl_hip_roll);
    if(res->error_code[3] == 0){
        legMotor[1][0].self = req->data.fl_hip_roll;
        legMotor[1][0].state.is_error = 0;
        legMotor[1][0].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[1][0], hcan)){
            legMotor[1][0].state.error_code &= ~ MOTOR_ERROR_PARAM;
            legMotor[1][0].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        /* update status, states and error */
        legMotor[1][0].state.is_error = 1;
        legMotor[1][0].state.error_code |= MOTOR_ERROR_PARAM;
        legMotor[1][0].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[1][0].debug_state = MOTOR_NOT_INITIALIZED;
    }
    res->init_status_code[3] = legMotor[1][0].debug_state;

    /* FL Leg HIP_PITCH joint motor */
    res->error_code[4] = check_init_motor_valid(&req->data.fl_hip_pitch);
    if(res->error_code[4] == 0){
        legMotor[1][1].self = req->data.fl_hip_pitch;  
        legMotor[1][1].state.is_error = 0;
        legMotor[1][1].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[1][1], hcan)){
            legMotor[1][1].state.error_code &= ~ MOTOR_ERROR_PARAM;
            legMotor[1][1].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        /* update status, states and error */
        legMotor[1][1].state.is_error = 1;
        legMotor[1][1].state.error_code |= MOTOR_ERROR_PARAM;
        legMotor[1][1].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[1][1].debug_state = MOTOR_NOT_INITIALIZED;
    }
    res->init_status_code[4] = legMotor[1][1].debug_state;

    /* FL Leg KNEE joint motor */
    res->error_code[5] = check_init_motor_valid(&req->data.fl_knee);
    if(res->error_code[5] == 0){
        legMotor[1][2].self = req->data.fl_knee;    
        legMotor[1][2].state.is_error = 0;
        legMotor[1][2].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[1][2], hcan)){
            legMotor[1][2].state.error_code &= ~ MOTOR_ERROR_PARAM;
            legMotor[1][2].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        /* update status, states and error */
        legMotor[1][2].state.is_error = 1;
        legMotor[1][2].state.error_code |= MOTOR_ERROR_PARAM;
        legMotor[1][2].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[1][2].debug_state = MOTOR_NOT_INITIALIZED;
    }
    res->init_status_code[5] = legMotor[1][2].debug_state;
    
    /* RR Leg HIP_ROLL joint motor */
    res->error_code[6] = check_init_motor_valid(&req->data.rr_hip_roll);
    if(res->error_code[6] == 0)     {
        legMotor[2][0].self = req->data.rr_hip_roll;
        legMotor[2][0].state.is_error = 0;
        legMotor[2][0].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[2][0], hcan)){
            legMotor[2][0].state.error_code &= ~ MOTOR_ERROR_PARAM;
            legMotor[2][0].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        /* update status, states and error */
        legMotor[2][0].state.is_error = 1;
        legMotor[2][0].state.error_code |= MOTOR_ERROR_PARAM;
        legMotor[2][0].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[2][0].debug_state = MOTOR_NOT_INITIALIZED;
    }
    res->init_status_code[6] = legMotor[2][0].debug_state;

    /* RR Leg HIP_PITCH joint motor */
    res->error_code[7] = check_init_motor_valid(&req->data.rr_hip_pitch);
    if(res->error_code[7] == 0){
        legMotor[2][1].self = req->data.rr_hip_pitch;
        legMotor[2][1].state.is_error = 0;
        legMotor[2][1].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[2][1], hcan)){
            legMotor[2][1].state.error_code &= ~ MOTOR_ERROR_PARAM;
            legMotor[2][1].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        /* update status, states and error */
        legMotor[2][1].state.is_error = 1;
        legMotor[2][1].state.error_code |= MOTOR_ERROR_PARAM;
        legMotor[2][1].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[2][1].debug_state = MOTOR_NOT_INITIALIZED;
    }
    res->init_status_code[7] = legMotor[2][1].debug_state;

    /* RR Leg KNEE joint motor */
    res->error_code[8] = check_init_motor_valid(&req->data.rr_knee);
    if(res->error_code[8] == 0){
        legMotor[2][2].self = req->data.rr_knee;
        legMotor[2][2].state.is_error = 0;
        legMotor[2][2].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[2][2], hcan)){
            legMotor[2][2].state.error_code &= ~ MOTOR_ERROR_PARAM;
            legMotor[2][2].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        /* update status, states and error */
        legMotor[2][2].state.is_error = 1;
        legMotor[2][2].state.error_code |= MOTOR_ERROR_PARAM;
        legMotor[2][2].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[2][2].debug_state = MOTOR_NOT_INITIALIZED;
    }
    res->init_status_code[8] = legMotor[2][2].debug_state;

    /* RL Leg HIP_ROLL joint motor */
    res->error_code[9] = check_init_motor_valid(&req->data.rl_hip_roll);
    if(res->error_code[9] == 0){
        legMotor[3][0].self = req->data.rl_hip_roll;
        legMotor[3][0].state.is_error = 0;
        legMotor[3][0].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[3][0], hcan)){
            legMotor[3][0].state.error_code &= ~ MOTOR_ERROR_PARAM;
            legMotor[3][0].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        /* update status, states and error */
        legMotor[3][0].state.is_error = 1;
        legMotor[3][0].state.error_code |= MOTOR_ERROR_PARAM;
        legMotor[3][0].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[3][0].debug_state = MOTOR_NOT_INITIALIZED;
    }
    res->init_status_code[9] = legMotor[3][0].debug_state;

    /* RL Leg HIP_PITCH joint motor */
    res->error_code[10] = check_init_motor_valid(&req->data.rl_hip_roll);
    if(res->error_code[10] == 0){
        legMotor[3][1].self = req->data.rl_hip_pitch;
        legMotor[3][1].state.is_error = 0;
        legMotor[3][1].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[3][1], hcan)){
            legMotor[3][1].state.error_code &= ~ MOTOR_ERROR_PARAM;
            legMotor[3][1].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        /* update status, states and error */
        legMotor[3][1].state.is_error = 1;
        legMotor[3][1].state.error_code |= MOTOR_ERROR_PARAM;
        legMotor[3][1].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[3][1].debug_state = MOTOR_NOT_INITIALIZED;
    }
    res->init_status_code[10] = legMotor[3][1].debug_state;


    /* RL Leg KNEE joint motor */
    res->error_code[11] = check_init_motor_valid(&req->data.rl_hip_roll);
    if(res->error_code[11] == 0){
        legMotor[3][2].self = req->data.rl_knee;
        legMotor[3][2].state.is_error = 0;
        legMotor[3][2].init_status |= MOTOR_INIT_STATUS_PARAM_SET;
        if(init_motorCAN(&legMotor[3][2], hcan)){
            legMotor[3][2].state.error_code &= ~ MOTOR_ERROR_PARAM;
            legMotor[3][2].debug_state = MOTOR_INITIALIZED;
        }
    }else{
        /* update status, states and error */
        legMotor[3][2].state.is_error = 1;
        legMotor[3][2].state.error_code |= MOTOR_ERROR_PARAM;
        legMotor[3][2].init_status &= ~MOTOR_INIT_STATUS_PARAM_SET;
        legMotor[3][2].debug_state = MOTOR_NOT_INITIALIZED;
    }
    res->init_status_code[11] = legMotor[3][2].debug_state;

}


void _unpack_canRx(LegMotor_TypeDef* m)
{

}

bool motor_sendTx_getRx(LegMotor_TypeDef* m){
    /* Send CanTx message to the motor */
    retry:
    if(HAL_CAN_AddTxMessage(m->hcan, &m->canTx.header, m->canTx.data, &m->canTx.TxMailBox) != HAL_OK)   
        goto can_fail;

    /*  get CAN rx message and filter motor Id  */
    uint8_t rx_data[NUM_OF_CAN_RX_BYTES];
    osDelay(2);
    if(HAL_CAN_GetRxMessage(m->hcan, CAN_RX_FIFO0, &m->canRx->header, rx_data) != HAL_OK){   
        goto motor_offline;
    }

    /* If rx msg was sent by the correct motor, save rx data into canRx.data */
    if(rx_data[0] == m->self.params.can_id){
        memcpy(m->canRx->data, rx_data, NUM_OF_CAN_RX_BYTES);
        /* unpack canRx data into motor feedback {position, velocity, currunt} */
        _unpack_canRx(m);
        /* reset motor _noMotorResp_count */
        m->_noMotorResp_count = 0;
        goto motor_ok; 
    } 

    /* If tx msg was sent and rx msg was received, but rx msg was received from another motor */
    else if (m->hcan->ErrorCode != HAL_ERROR){
        /* count failiers of motor response */
        m->_noMotorResp_count ++;
        /* if motor response was no recived more than MAX_MOTOR_NO_RESPONSE_COUNT, update motoe state and error_code */
        if(m->_noMotorResp_count > MAX_MOTOR_NO_RESPONSE_COUNT)
            goto motor_offline;
        else goto retry;
    }

    motor_ok:
    m->state.is_available = true;
    m->state.error_code &= ~MOTOR_ERROR_OFFLINE;
    m->state.error_code &= ~MOTOR_ERROR_HAL_CAN;
    return 1;

    motor_offline:
    m->state.error_code |= MOTOR_ERROR_OFFLINE; /*!< Set motor offline error */
    m->debug_state = MOTOR_OFFLINE;
    return 0;
    
    can_fail:
    m->state.error_code |= MOTOR_ERROR_HAL_CAN;
    m->debug_state = CAN_ERROR;
    return 0;
}



bool enable_motor(LegMotor_TypeDef* m){
    memcpy(m->canTx.data, motor_enable_cmd, sizeof(motor_enable_cmd));
    if(motor_sendTx_getRx(m)) goto ok;
    else goto fail;

    ok:
    m->state.error_code &= ~MOTOR_ERROR_EN;
    m->debug_state = MOTOR_ENABLED;
    return 1;

    fail:
    m->state.error_code |= MOTOR_ERROR_EN;
    return 0;
}

bool enable_motor_id(uint8_t id){
    for(int i=0; i<NUM_OF_LEGS; i++){
        for(int j=0; j<NUM_OF_JOINTS_PER_LEG; j++){
            if(legMotor[i][j].self.params.can_id == id){
                return enable_motor(&legMotor[i][j]);
            }
        }
    }
}

bool enable_allMotors(){
    if(motor_objects_created){
        for(int i=0; i<NUM_OF_LEGS; i++){
            for(int j=0; j<NUM_OF_JOINTS_PER_LEG; j++){
                enable_motor(&legMotor[i][j]);
                osDelay(2);
            }
        }
        return 1;
    }else{
        return 0;
    }
}



bool disable_motor(LegMotor_TypeDef* m){
    memcpy(m->canTx.data, motor_disable_cmd, sizeof(motor_disable_cmd));
    if(motor_sendTx_getRx(m)){ 
        osDelay(2); 
        goto ok;}
    else{
        goto fail;
    } 

    ok:
    m->state.error_code &= ~MOTOR_ERROR_DIS;
    m->debug_state = MOTOR_DISABLED;
    return 1;
    

    fail:
    m->state.error_code |= MOTOR_ERROR_DIS;
    return 0;
    
}

bool disable_motor_id(uint8_t id){
    for(int i=0; i<NUM_OF_LEGS; i++){
        for(int j=0; j<NUM_OF_JOINTS_PER_LEG; j++){
            if(legMotor[i][j].self.params.can_id == id){
                return disable_motor(&legMotor[i][j]);
            }
        }
    }
}


void disable_allMotors(){
    for(int i=0; i<NUM_OF_LEGS; i++){
        for(int j=0; j<NUM_OF_JOINTS_PER_LEG; j++){
            disable_motor(&legMotor[i][j]);
            osDelay(2);
        }
    }
}

bool setzeros_motor_position(LegMotor_TypeDef* m){
    memcpy(m->canTx.data, motor_setzero_cmd, sizeof(motor_setzero_cmd));
    if(motor_sendTx_getRx(m)) goto ok;
    else goto fail;

    ok:
    m->state.error_code &= ~MOTOR_ERROR_SZ;
    return 1;

    fail:
    m->state.error_code |= MOTOR_ERROR_SZ;
    return 0;
}



void destroy_legMotors(){
    for(int i=0; i<NUM_OF_LEGS; i++){
        free(legMotor[i]);
    }
    free(legMotor);
}