#ifndef MINICHEETAH_MOTOR_H__
#define MINICHEETAH_MOTOR_H__


#ifdef __cplusplus
extern "C"{
#endif

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "can.h"
#include "motor_defs.h"
#include "motor_typedefs.h"



class Motor
{
public:
    Motor();
    Motor(uint8_t id, CAN_HandleTypeDef* hcan, uint8_t rx_filterbank);
    ~Motor();

    void set_id(uint8_t motor_id);
    void config_CAN(CAN_HandleTypeDef* hcan, uint8_t rx_filterbank);
    void set_motor_params(float p_max, float v_max, float kp_max, float kd_max, float iff_max);
    void set_motor_control_limits(float p_min, float p_max, float v_max, float i_max);
    void send_heartbeat();

    void enable();
    void disable();
    void setzero(); 



private:
    uint8_t id;
    motor_cmd_t cmd;
    motor_param_t params;
    motor_ctrl_limits_t ctrl_limit;
    motor_current_states_t current_states;

    CANRxMessage rx_msg;
    CANTxMessage tx_msg;
    CAN_HandleTypeDef* hcan_ptr;

    Motor_StatusTypeDef motor_status = 0;
    Motor_ErrorCodeTypeDef error_code = MOTOR_INIT_ERROR;

    uint8_t enable_cmd_[8] = MOTOR_ENABLE_CMD;
    uint8_t disbale_cmd_[8] = MOTOR_DISABLE_CMD;
    uint8_t setzero_cmd_[8] = MOTOR_SETZERO_CMD;
    uint8_t heartbeat_cmd_[8] = MOTOR_HEARTBEAT;


    void _init_can_rx(uint8_t rxMsg_filterbank);
    void _init_can_tx();
    
    void pack_cmd();
    void unpack_reply();

    void can_send();
    void can_read();

    
};

#ifdef __cplusplus
}
#endif





#endif /* MINICHEETAH_MOTOR_H__ */