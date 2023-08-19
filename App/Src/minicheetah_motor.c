#include "minicheetah_motor.h"
#include "error_indicator.h"

Motor_TypeDef motor[NUM_OF_MOTORS];
uint8_t motor_enable_cmd[8] = MOTOR_ENABLE_CMD;
uint8_t motor_disable_cmd[8] = MOTOR_DISABLE_CMD;
uint8_t motor_setzero_cmd[8] = MOTOR_SETZERO_CMD;
uint8_t motor_heartbeat_cmd[8] = MOTOR_HEARTBEAT;

uint16_t motor_error_code = MOTOR_ERROR_INITIAL;
uint8_t motor_status = 0;


void MOTOR_setInit(enum MOTORS m, uint8_t id)
{
    // set init error and init status
    motor[m].status = 0;
    motor[m].error_code = MOTOR_ERROR_INITIAL;
    motor[m].id = id;
    motor[m].status |= MOTOR_STATUS_ID_SET; // set ID_SET bit of the status


    if ((motor[m].status & 0xF) == MOTOR_STATUS_INITIALIZED){    
        motor[m].error_code &= ~MOTOR_ERROR_NOT_INITIALIZED; // reset NOT_INITIALIZED bit of error code
    }
}

void MOTOR_setParams(enum MOTORS m, float pMax, float vMax, float kpMax, float kdMax, float iffMax)
{
    motor[m].params.p_des.min = -pMax;
    motor[m].params.p_des.max = pMax;
    motor[m].params.v_des.min = -vMax;
    motor[m].params.v_des.max = vMax;
    motor[m].params.kp.min    = 0;
    motor[m].params.kp.max    = kpMax;
    motor[m].params.kd.min    = 0;
    motor[m].params.kd.max    = kdMax;
    motor[m].params.i_ff.min  = -iffMax;
    motor[m].params.i_ff.max  = iffMax;
    
    motor[m].status |= MOTOR_STATUS_PARAMS_SET; // set PARAM_SET bit of the motor status.
    motor[m].error_code &= ~ MOTOR_ERROR_PARAM; // reset PARAM_ERROR bit of motor error code.

    if ((motor[m].status & 0xF)== MOTOR_STATUS_INITIALIZED){    
        motor[m].error_code &= ~MOTOR_ERROR_NOT_INITIALIZED; // reset NOT_INITIALIZED bit of error code
    }
}

void MOTOR_setCtrlLimits(enum MOTORS m, float pDesMax, float pDesMin, float vDesMax, float vMax, float iMax)
{
    motor[m].limit.position.max = pDesMax;
    motor[m].limit.position.min = pDesMin;
    motor[m].limit.velocity.max = vDesMax;
    motor[m].limit.velocity.min = -vDesMax;
    motor[m].limit.current.max  = iMax;
    motor[m].limit.current.min  = -iMax;

    motor[m].status |= MOTOR_STATUS_LIMITS_SET; // set CTRL_LIMIT_SET bit of the motor status.

    if ((motor[m].status & 0xF) == MOTOR_STATUS_INITIALIZED){    
        motor[m].error_code &= ~MOTOR_ERROR_NOT_INITIALIZED; // reset NOT_INITIALIZED bit of error code
    }
}

/** Confiure rx/tx messages and rx filter of the motor.
 * *** Make sure to call this function after initialied the motor IDs. ***
 * \param m enum MOTOR
 * \param *hcan CAN interface pointer instance
 * \param filterbank filter bank id to use for rx filter
 *
 */
void MOTOR_configCAN(enum MOTORS m, CAN_HandleTypeDef* hcan, uint8_t filterbank)
{
    // copy hcan pointer to Motor struct
    motor[m].hcan_ptr = hcan;

    // config can rx filter
    motor[m].canRx.filter.FilterBank = filterbank;
    motor[m].canRx.filter.FilterMode = CAN_FILTERMODE_IDMASK;
    motor[m].canRx.filter.FilterScale = CAN_FILTERSCALE_32BIT;
    motor[m].canRx.filter.FilterIdHigh = motor[m].id << 5;
    motor[m].canRx.filter.FilterIdLow  = 0;
    motor[m].canRx.filter.FilterMaskIdHigh = 0xFF;
    motor[m].canRx.filter.FilterMaskIdLow = 0;
    motor[m].canRx.filter.FilterFIFOAssignment = CAN_FilterFIFO0;
    motor[m].canRx.filter.FilterActivation = ENABLE;
    HAL_CAN_ConfigFilter(hcan, &motor[m].canRx.filter);

    // config can tx header
    motor[m].canTx.header.StdId = motor[m].id;
    motor[m].canTx.header.IDE = CAN_ID_STD;
    motor[m].canTx.header.DLC = NUM_OF_CAN_TX_BYETS;
    motor[m].canTx.header.RTR = CAN_RTR_DATA;

    if(motor[m].hcan_ptr->State != HAL_CAN_STATE_ERROR){
        motor[m].status |= MOTOR_STATUS_CAN_SET;
        motor[m].error_code &= ~ MOTOR_ERROR_CAN_CONFIG;
    }
    else{
        motor[m].error_code |= MOTOR_ERROR_CAN_CONFIG;
        motor[m].status &= ~ MOTOR_STATUS_CAN_SET;
    }
    if ((motor[m].status & 0xF) == MOTOR_STATUS_INITIALIZED){    
        motor[m].error_code &= ~MOTOR_ERROR_NOT_INITIALIZED; // reset NOT_INITIALIZED bit of error code
    }
}


void MOTOR_sendHeatbeat(enum MOTORS m)
{
    if((motor[m].status & 0xF) == MOTOR_STATUS_INITIALIZED){
        memcpy(motor[m].canTx.data, motor_heartbeat_cmd, sizeof(motor_heartbeat_cmd));
        if(HAL_CAN_AddTxMessage(motor[m].hcan_ptr, &motor[m].canTx.header, motor[m].canTx.data, &motor[m].canTx.TxMailBox) != HAL_OK)
        {
            blink_error(5, 3, 200, 100);
        }
    }
   
}

void MOTOR_startWatchdog()
{

}

void MOTOR_enable(enum MOTORS m)
{

}

void MOTOR_disable(enum MOTORS m)
{

}

void MOTOR_setZero(enum MOTORS m)
{

}


void _pack_cmd(enum MOTORS m)
{

}
void _unpack_reply(enum MOTORS m)
{

}

void _can_send()
{

}

void _can_read()
{
    
}