#include "minicheetah_motor.h"
#include "error_indicator.h"
Motor::Motor()
{

}

Motor::Motor(uint8_t id, CAN_HandleTypeDef* hcan, uint8_t rx_filterbank)
{

    set_id(id);
    config_CAN(hcan, rx_filterbank);

}

Motor::~Motor()
{

}

void Motor::set_id(uint8_t motor_id)
{
    this->id = motor_id;
    this->motor_status |= MOTOR_ID_SET;
}

void Motor::config_CAN(CAN_HandleTypeDef* hcan, uint8_t rx_filterbank)
{
    _init_can_rx(rx_filterbank);
    _init_can_tx();

    /// \todo check error befor setting motor status flag
    this->motor_status |= MOTOR_CAN_SET;
}
void Motor::_init_can_rx(uint8_t rx_filterbank)
{
    // rx filter configuration
    this->rx_msg.filter.FilterBank = rx_filterbank;
    this->rx_msg.filter.FilterMode = CAN_FILTERMODE_IDMASK;
    this->rx_msg.filter.FilterScale = CAN_FILTERSCALE_32BIT;
    this->rx_msg.filter.FilterIdHigh = id << 5;
    this->rx_msg.filter.FilterIdLow = 0x0;
    this->rx_msg.filter.FilterMaskIdHigh = 0xFFF;
    this->rx_msg.filter.FilterMaskIdLow = 0;
    this->rx_msg.filter.FilterFIFOAssignment = CAN_FilterFIFO0;
    this->rx_msg.filter.FilterActivation = ENABLE;
    HAL_CAN_ConfigFilter(this->hcan_ptr, &this->rx_msg.filter);
    
}
void Motor::_init_can_tx()
{
    this->tx_msg.header.StdId = this->id;
    this->tx_msg.header.DLC = NUM_OF_TX_BYETS;
    this->tx_msg.header.IDE = CAN_ID_STD;
    this->tx_msg.header.RTR = CAN_RTR_DATA;
}

void Motor::set_motor_params(float p_max, float v_max, float kp_max, float kd_max, float iff_max)
{
    this->params.p_des.max = p_max;
    this->params.p_des.min = -p_max;
    this->params.v_des.max = v_max;
    this->params.v_des.min = -v_max;
    this->params.kp.max = kp_max;
    this->params.kp.min = 0;
    this->params.kd.max = kd_max;
    this->params.kd.min = 0;
    this->params.i_ff.max = iff_max;
    this->params.i_ff.min = -iff_max;

    this->motor_status |= MOTOR_PARAMS_SET;
}

void Motor::set_motor_control_limits(float p_min, float p_max, float v_max, float i_max)
{
    this->ctrl_limit.position.min = p_min;
    this->ctrl_limit.position.max = p_max;
    this->ctrl_limit.velocity.max = v_max;
    this->ctrl_limit.velocity.min = -v_max;
    this->ctrl_limit.current.max = i_max;
    this->ctrl_limit.current.min = -i_max;

    this->motor_status |= MOTOR_CTRL_LIMITS_SET;
}

void Motor::send_heartbeat()
{
    if(this->motor_status & (MOTOR_ID_SET | MOTOR_CAN_SET)){
        memcpy(this->tx_msg.data, heartbeat_cmd_, 8);
        if(HAL_CAN_AddTxMessage(&hcan1, &this->tx_msg.header, this->tx_msg.data, &this->tx_msg.TxMailBox) != HAL_OK)
        {
            blink_error(5, 3, 200, 100);
        }
    }
   
}

void Motor::enable()
{

}

void Motor::disable()
{

}

void Motor::setzero()
{

}


void Motor::pack_cmd()
{

}
void Motor::unpack_reply()
{

}

void Motor::can_send()
{

}

void Motor::can_read()
{
    
}