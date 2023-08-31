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

#include "minicheetah_motor.h"
#include "error_indicator.h"

Motor_TypeDef motor[NUM_OF_MOTORS];
uint8_t motor_enable_cmd[8] = MOTOR_ENABLE_CMD;
uint8_t motor_disable_cmd[8] = MOTOR_DISABLE_CMD;
uint8_t motor_setzero_cmd[8] = MOTOR_SETZERO_CMD;
uint8_t motor_heartbeat_cmd[8] = MOTOR_HEARTBEAT;

uint16_t motor_error_code = MOTOR_ERROR_INITIAL;
uint8_t motor_state = 0;

/**
 * @brief To initialize a motor Id.
 * @brief To be fully initialized the motor, MOTOR_setParams, MOTOR_setCtrlLimits and MOTOR_configCAN methods must be called after this method.
 * @param m motor instance 
 * @param id CAN StdId of the motor
 */
void MOTOR_initId(enum MOTORS m, uint8_t id)
{
    // set init_state, state and error_code to thier initial state
    motor[m].state = MOTOR_INITIALIZING;
    motor[m].init_state = MOTOR_INIT_STATUS_NOT;
    motor[m].error_code = MOTOR_ERROR_INITIAL;

    /* Set Id */
    motor[m].id = id;

    /* update motor init_state */
    motor[m].init_state |= MOTOR_INIT_STATUS_ID; // set ID_SET bit of the init state
}


/**
 * @brief To set motor parameters of the motor
 * @param m motor instance
 * @param pMax maximum position of the motor
 * @param vMax Maximum velocity of the motor
 * @param kpMax maximum Kp value of the motor
 * @param kdMax maximum Kd value of the motor
 * @param iffMax maximum feed forwad current of the motor
 */
void MOTOR_initParams(enum MOTORS m, float pMax, float vMax, float kpMax, float kdMax, float iffMax, float vbMax)
{
    motor[m].params.p.min = -pMax;
    motor[m].params.p.max = pMax;
    motor[m].params.v.min = -vMax;
    motor[m].params.v.max = vMax;
    motor[m].params.kp.min    = 0;
    motor[m].params.kp.max    = kpMax;
    motor[m].params.kd.min    = 0;
    motor[m].params.kd.max    = kdMax;
    motor[m].params.i_ff.min  = -iffMax;
    motor[m].params.i_ff.max  = iffMax;
    motor[m].params.vb.min    = 0;
    motor[m].params.vb.max    = vbMax;
    
    /* update init_state and error_code */
    motor[m].init_state |= MOTOR_INIT_STATUS_PARAM; // set PARAM_SET bit of the motor init_state.
    motor[m].error_code &= ~ MOTOR_ERROR_PARAM; // reset PARAM_ERROR bit of motor error_code.

    /* If motor is fully initialized update error_code and motor state */
    if (motor[m].init_state == MOTOR_INIT_STATUS_OK)
    {   
        motor[m].error_code &= ~MOTOR_ERROR_NOT_INITIALIZED; // reset NOT_INITIALIZED bit of error_code
        motor[m].state = MOTOR_READY;
    }
}


/** 
 * @brief To set limit for the contral parameters and motor current
 * @param m Motor instance
 * @param pDesMax Higher limit for motor position
 * @param pDesMin Lower limit for motor position
 * @param vMax    Higher limit for motor velocity
 * @param iMax    Highr limit for motor intake current
 */
void MOTOR_initCtrlLimits(enum MOTORS m, float pDesMax, float pDesMin, float vMax, float iMax)
{
    motor[m].limit.position.max = pDesMax;
    motor[m].limit.position.min = pDesMin;
    motor[m].limit.velocity.max = vMax;
    motor[m].limit.velocity.min = -vMax;
    motor[m].limit.current.max  = iMax;
    motor[m].limit.current.min  = -iMax;

    /* update motor init_state */
    motor[m].init_state |= MOTOR_INIT_STATUS_LIMITS; // set CTRL_LIMIT_SET bit of the motor init_state.

    /* If motor is fully initialized update error_code */
    if (motor[m].init_state == MOTOR_INIT_STATUS_OK)
    { 
        motor[m].error_code &= ~MOTOR_ERROR_NOT_INITIALIZED; // reset NOT_INITIALIZED bit of error_code
        motor[m].state = MOTOR_READY;
    }
}


/** Confiure rx/tx messages and rx filter of the motor.
 * Make sure to call this function after initialied the motor IDs. *
 * \param m enum MOTOR
 * \param *hcan CAN interface pointer instance
 * \param filterbank filter bank id to use for rx filter
 *
 */
void MOTOR_initCANConfig(enum MOTORS m, CAN_HandleTypeDef* hcan, uint8_t filterbank)
{
    /* copy hcan pointer to motor instance */
    motor[m].hcan_ptr = hcan;

    /* config can rx filter */
    motor[m].canRx.filter.FilterMode = CAN_FILTERMODE_IDMASK;
    motor[m].canRx.filter.FilterScale = CAN_FILTERSCALE_32BIT;
    motor[m].canRx.filter.FilterIdHigh = 0 << 5; // motors sends can frame with Id number 0, 1st byte of data frame is the motor Id
    motor[m].canRx.filter.FilterIdLow  = 0x0;
    motor[m].canRx.filter.FilterMaskIdHigh = 0xFFF;
    motor[m].canRx.filter.FilterMaskIdLow = 0;
    motor[m].canRx.filter.FilterFIFOAssignment = CAN_FilterFIFO0;
    motor[m].canRx.filter.FilterActivation = ENABLE;
    // motor[m].canRx.filter.FilterBank = filterbank;
    HAL_CAN_ConfigFilter(hcan, &motor[m].canRx.filter);

    /* config can tx header */
    motor[m].canTx.header.StdId = motor[m].id;
    motor[m].canTx.header.IDE = CAN_ID_STD;
    motor[m].canTx.header.DLC = NUM_OF_CAN_TX_BYETS;
    motor[m].canTx.header.RTR = CAN_RTR_DATA;

    /* If there is a CAN state error, update motor init_state, state and error_code */
    if(motor[m].hcan_ptr->ErrorCode == HAL_ERROR)
    {
        motor[m].init_state &= ~MOTOR_INIT_STATUS_CAN;
        motor[m].error_code |= MOTOR_ERROR_HAL_CAN;
        motor[m].state = ERROR;
    }

    else
    {
        /* update motor init_state and error_code */
        motor[m].init_state |= MOTOR_INIT_STATUS_CAN;
        motor[m].error_code &= ~MOTOR_ERROR_HAL_CAN; /* reset motor CAN_COFIG error in the error_code */
    }

    /* If motor is fully initialized update motor state and error_code */
    if (motor[m].init_state == MOTOR_INIT_STATUS_OK)
    { 
        motor[m].error_code &= ~MOTOR_ERROR_NOT_INITIALIZED; // reset NOT_INITIALIZED bit of error_code
        motor[m].state = MOTOR_READY;
    }
       
}


/** 
 * \brief To send a heartbeat to a motor and to update motor_state and error_code.
 * Heartbeat will be sent although motor state is in ERROR. 
 * 
 * \param m enum name of the motor 
 * 
 */
void MOTOR_sendHeatbeat(enum MOTORS m)
{
    /* Copy heatbeat comd to can_tx mesage */
    memcpy(motor[m].canTx.data, motor_heartbeat_cmd, sizeof(motor_heartbeat_cmd));

    /* send the heartbeat */
    MOTOR_sendTxGetRx(m);

    /* update the motor feedback */
    _unpack_canRx(m);
    

    /* update error_code, if motor is onine */
    if(!_is_motor_error(m, MOTOR_ERROR_OFFLINE))
    {
        /* @todo : Check for other errors (OOR, OH, OC) and update error_code */

        motor[m].error_code &= ~ MOTOR_ERROR_NOT_READY;     /*!< Reset motor is not ready error */
        motor[m].error_code &= ~ MOTOR_ERROR_OOR;           /* Reset motor out of range error */
        motor[m].error_code &= ~ MOTOR_ERROR_OH;            /* Reset motor over-heated error */
        motor[m].error_code &= ~ MOTOR_ERROR_OC;            /* Reset motor over-current error */
    }
}


/**
 * @brief This method is used to send the command to the motor and get the response from the motor.
 * If HAL_CAN sent the Tx command and we loss the response from the motor, this method will count 
 * how many time we missed the response. once the missed response times more than defined 
 * MAX_MOTOR_NO_RESPONSE_COUNT, motor state is set to ERROR and error_code's MOTOR_OFFLINE bit will be set.
 * If HAL_CAN will be failed to send or get message, motor state will be set to ERROR and error_code's
 * MOTOR_ERROR_HAL_CAN bit will be set.
 * 
 * \param m enum name of the motor 
 */
void MOTOR_sendTxGetRx(enum MOTORS m)
{
    /* Send CanTx message to the motor */
    if(HAL_CAN_AddTxMessage(motor[m].hcan_ptr, &motor[m].canTx.header, motor[m].canTx.data, &motor[m].canTx.TxMailBox) == HAL_OK)
    {
        /*  get CAN rx message and filter motor Id  */
        uint8_t rx_data[NUM_OF_CAN_RX_BYTES];
        if(HAL_CAN_GetRxMessage(motor[m].hcan_ptr, CAN_RX_FIFO0, &motor[m].canRx.header, rx_data) == HAL_OK && rx_data[0] == motor[0].id)
        {
            /* If rx msg was sent by the right motor, save rx data into canRx.data */
            memcpy(motor[m].canRx.data, rx_data, NUM_OF_CAN_RX_BYTES);

            /* unpack canRx data into motor feedback {position, velocity, currunt} */
            _unpack_canRx(m);

            /* reset motor noResp_counter */
            motor[m].noResp_counter = 0;

            /* update motor error_code */
            motor[m].error_code &= ~MOTOR_ERROR_OFFLINE; /*!< Reset motor offline error */
            motor[m].error_code &= ~MOTOR_ERROR_HAL_CAN; /*!< Reset motor HAL_CAN error */

            /* update motor state */
            if(motor[m].state != MOTOR_ENABLED && !_is_motor_error(m, MOTOR_ERROR_NOT_INITIALIZED))
            {
                motor[m].state = MOTOR_READY; /*!< Reset motor error state */
            }
        }

         /* If tx msg was sent and rx msg was received, but rx msg was sent by another motor */
        else if (motor[m].hcan_ptr->ErrorCode != HAL_ERROR)
        {
             /* count failiers of motor response */
            motor[m].noResp_counter ++;

            /* if motor response was no recived more than MAX_MOTOR_NO_RESPONSE_COUNT, update motoe state and error_code */
            if(motor[m].noResp_counter > MAX_MOTOR_NO_RESPONSE_COUNT)
            {
                motor[m].error_code |= MOTOR_ERROR_OFFLINE; /*!< Set motor offline error */
                motor[m].state = MOTOR_ERROR;
            }
        }
    }

    /* If Send or Get msg was failed */
    else
    {
        /* update motor error_code */
        motor[m].error_code |= MOTOR_ERROR_HAL_CAN; /*!< set HAL_CAN error */

        /* update motor state */
        motor[m].state = MOTOR_ERROR; 
    }
}



/**
 *  @brief To send enable motor command and update motor state.
 * Enable command can be sent only if there is no internal motor errors such as;
 * over-current, over-heat. 
 * @param m enum name of the motor 
 * 
 */
void MOTOR_enable(enum MOTORS m)
{
    /* If motor is not over-heated or not over-current */
    if(!_is_motor_error(m, 0b00001100000U))
    {
        /* set canTx data to enable command */
        memcpy(motor[m].canTx.data, motor_enable_cmd, sizeof(motor_enable_cmd));

        /* Send the cmd and get the response */
        MOTOR_sendTxGetRx(m);

        /* if response received from the motor m, update state and error_code */
        if(motor[m].noResp_counter == 0){
            motor[m].error_code &= ~MOTOR_ERROR_EN; /*!< reset */
            motor[m].state = MOTOR_ENABLED;
        }

        /* else, update error_code and state */
        else{
            motor[m].error_code |= MOTOR_ERROR_EN; /*!< set `enbale error` bit of the error code*/
            motor[m].state = MOTOR_ERROR;
        }

    }
    
}


/**
 * To send motor disable command
 * @param m enum name of the motor 
 */
void MOTOR_disable(enum MOTORS m)
{
    
    /* set canTx data to enable command */
    memcpy(motor[m].canTx.data, motor_disable_cmd, sizeof(motor_disable_cmd));

    /* Send the cmd and get the response */
    MOTOR_sendTxGetRx(m);

    /* if response received from the motor m, update state  and error_code */
    if(motor[m].noResp_counter == 0){
        motor[m].error_code &= ~MOTOR_ERROR_DIS;
        motor[m].state = MOTOR_READY;
    }

    /* else, update error_code and state */
    else{
        motor[m].error_code |= MOTOR_ERROR_DIS;
        motor[m].state = MOTOR_ERROR;
    }

}

/**
 * To send motor set_zero command.
 * This command can be used for setting the motor current position as its zero position.
 * @param m enum name of the motor 
 * 
 * @todo : when it's possible to set motor position zero ?
 * @todo : make a condition to send this cmd, only when motor can set the zero position
 */
void MOTOR_setZero(enum MOTORS m)
{
    /* set canTx data to enable command */
    memcpy(motor[m].canTx.data, motor_setzero_cmd, sizeof(motor_setzero_cmd));

    /* Send the cmd and get the response */
    MOTOR_sendTxGetRx(m);

    /*  update error_code */
    if(motor[m].noResp_counter != 0)
    {
        motor[m].error_code |= MOTOR_ERROR_SZ;
    }
}



void MOTOR_startWatchdog()
{
    
}

/**
 * Pack motor commands from `motor[x].cmd` into `motor[x].canTx` message 
 * 
*/
void _pack_cmd(enum MOTORS m)
{
    /*  
    * 
    * CAN Command Packet Structure 
    * 16 bit position command, between -4*pi and 4*pi
    * 12 bit velocity command, between -30 and + 30 rad/s
    * 12 bit kp, between 0 and 500 N-m/rad
    * 12 bit kd, between 0 and 100 N-m*s/rad
    * 12 bit feed forward torque, between -18 and 18 N-m
    * CAN Packet is 8 8-bit words
    * Formatted as follows.  For each quantity, bit 0 is LSB
    * 0: [position[15-8]]
    * 1: [position[7-0]]
    * 2: [velocity[11-4]]
    * 3: [velocity[3-0] , kp[11-8]]
    * 4: [kp[7-0]]
    * 5: [kd[11-4]]
    * 6: [kd[3-0], torque[11-8]]
    * 7: [torque[7-0]] 
    */

    /* Limit data to be within bounds */
    float p_des = fminf(fmaxf(motor[m].params.p.min, motor[m].cmd.p_des), motor[m].params.p.max);
    float v_des = fminf(fmaxf(motor[m].params.v.min, motor[m].cmd.v_des), motor[m].params.v.max);
    float kp    = fminf(fmaxf(motor[m].params.kp.min,    motor[m].cmd.kp   ), motor[m].params.kp.max   );
    float kd    = fminf(fmaxf(motor[m].params.kd.min,    motor[m].cmd.kd   ), motor[m].params.kd.max   );
    float iff   = fminf(fmaxf(motor[m].params.i_ff.min,  motor[m].cmd.iff  ), motor[m].params.i_ff.max );

    /* Convert floats to unsigned ints */
    int p_int   = float2uint(p_des, motor[m].params.p.min, motor[m].params.p.max, 16);
    int v_int   = float2uint(v_des, motor[m].params.v.min, motor[m].params.v.max, 12);
    int kp_int  = float2uint(kp,    motor[m].params.kp.min,    motor[m].params.kp.max   , 12);
    int kd_int  = float2uint(kd,    motor[m].params.kd.min,    motor[m].params.kd.max   , 12);
    int iff_int = float2uint(iff,   motor[m].params.i_ff.min,  motor[m].params.i_ff.max , 12);

    motor[m].canTx.data[0] = p_int >> 8;
    motor[m].canTx.data[1] = p_int & 0xFF;
    motor[m].canTx.data[2] = v_int >> 4;
    motor[m].canTx.data[3] = ((v_int&0xF)<<4) | (kp_int>>8);
    motor[m].canTx.data[4] = kp_int&0xFF;
    motor[m].canTx.data[5] = kd_int>>4;
    motor[m].canTx.data[6] = ((kd_int&0xF)<<4) | (iff_int>>8);
    motor[m].canTx.data[7] = iff_int&0xFF;
}


/**
 * unpack `motor[x].canRx` data to `motor[x].feedback` 
 * \param m enum name of the motor
*/
void _unpack_canRx(enum MOTORS m)
{
    /** 
     * CAN Reply Packet Structure
     * \protocol  :
	 * 16 bit position, between -4*pi and 4*pi
	 * 12 bit velocity, between -30 and + 30 rad/s
	 * 12 bit current, between -40 and 40;
	 * CAN Packet is 5 8-bit words
	 * Formatted as follows.  For each quantity, bit 0 is LSB
     * 0: [id]
	 * 1: [position[15-8]]
	 * 2: [position[7-0]]
	 * 3: [velocity[11-4]]
	 * 4: [velocity[3-0] , current[11-8]]
	 * 5: [current[7-0]]
     */

    /* unpack uints from motor[x].canRx.data */
    int p_int  = (motor[m].canRx.data[1] << 8) | motor[m].canRx.data[2];
    int v_int  = (motor[m].canRx.data[3] << 4) | motor[m].canRx.data[4]>>4;
    int i_int  = ((motor[m].canRx.data[4]&0xF)<<8) | motor[m].canRx.data[5];

    /* convert uints to float  and set them in `motor[x].feedback.X` */
    motor[m].feedback.position = uint2float(p_int, motor[m].params.p.min, motor[m].params.p.max, 16);
    motor[m].feedback.velocity = uint2float(v_int, motor[m].params.v.min, motor[m].params.v.max, 12);
    motor[m].feedback.current  = uint2float(i_int, motor[m].params.i_ff.min,  motor[m].params.i_ff.max,  12);
    if (NUM_OF_CAN_RX_BYTES == 7){
        motor[m].feedback.vb = uint2float(motor[m].canRx.data[6], motor[m].params.vb.min,  motor[m].params.vb.max,  8);
    }

}



/**
 * @brief To check if a given `error_code` is set.
 * \param m enum name of the motor 
 * @param error_word which error bit(s) to be checked
 * @retval bool:  1 if set, 0 else
 */
bool _is_motor_error(enum MOTORS m, uint8_t error_word)
{
    bool is_error_set = (motor[m].error_code & error_word) == error_word;
    return is_error_set;
}


float fminf(float x, float y){
    return (((x) < (y)) ? (x) : (y));
}

float fmaxf(float x, float y){
    return (((x) > (y)) ? (x) : (y));
}

int float2uint(float x, float x_min, float x_max, int bits)
{
    float span = x_max - x_min;
    float offset = x_min;
    return (int) ((x - offset) * ((float)((1<<bits)-1))/span);
}

float uint2float(int x_int, float x_min, float x_max, int bits)
{
    float span = x_max = x_min;
    float offset = x_min;
    return ((float)x_int)*span/((float)((1<<bits)-1)) + offset;
}