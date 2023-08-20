#ifndef MOTOR_TYPEDEFS_H__
#define MOTOR_TYPEDEFS_H__


#ifdef __cplusplus
extern "C"{
#endif

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "can.h"
#include "motor_defs.h"

/** Motor Status flag TypeDef
 * \param bit_0 motor id set
 * \param bit_1 motor CAN set
 * \param bit_2 motor online 
 * \param bit_3 motor enabled 
 * \param bit_4 motor params set 
 * \param bit_5 motor in range
 * \param bit_6 motor ready
 */
typedef uint8_t  motor_status_t ;
typedef uint16_t  motor_errorcode_t;


// ________________________________________
struct{
    float min;
    float max;
}typedef range_t;


// ==========  Motor Params TypeDef =============
/**
 * Motor params: 
 * \param p.min: Minimum value of motor position 
 * \param p.max: Maximum value of motor position
 * \param v.min: Minimum value motor velocity
 * \param v.max: Maximum value motor velocity 
 * \param kp.min: Minimum value motor Kp
 * \param kp.max: Maximum value motor Kp 
 * \param kd.min: Minimum value motor Kd
 * \param kd.max: Maximum value motor Kd 
 * \param i_ff.min: Minimum value motor feed forward current
 * \param i_ff.max: Maximum value motor feed foward current
 */
struct{
    range_t p_des;
    range_t v_des;
    range_t kp;
    range_t kd;
    range_t i_ff;
}typedef motor_param_t;



// ==========  Motor Control Limits TypeDef ============
/** Motor control limit TypeDef
 * \param position min and max motor control position limits
 * \param velocity min and max motor control velocity limits
 * \param current min and max motor current limits
 */
struct{
    range_t position; // to limit motor position 
    range_t velocity; // to limit motor velocity
    range_t current; // to limit motor intake current. If motor current exceed the limit, disable the motor or do safety control
}typedef motor_ctrl_limits_t;



// ==========  Motor Commands TypeDef ===========
/**
 * Motor commands
 * \param p_des: desired position
 * \param v_des: desired velocity
 * \param kp: stiffnes
 * \param kd: damp
 * \param iff: feed forward current
  */
struct {
    float p_des;
    float v_des;
    float kp;
    float kd;
    float iff;
}typedef motor_cmd_t;


// ========  Motor Current States TypeDef =========
/**
 * Current states of the motor
 * \param position current motor position
 * \param velocity current motor velocity
 * \param current current motor current
 */
struct{
    float position;
    float velocity;
    float current;
}typedef motor_current_states_t;



struct {
    uint8_t                 id; /*!< Identifier of the motor */
    motor_param_t           params; /* motor parameters: max position, max velocity, max kp, max kd, max i_ff */
    motor_ctrl_limits_t     limit; /*!< to limit controlable range of the motor; max position, min position, max velocity, max current */
    motor_cmd_t             cmd; /*!< Command to the motor: p_des, v_des, kp, kd, i_ff */
    motor_current_states_t  states; /*!< Motor feedback of current states: position, velocity, current */
    motor_status_t          status; /*!< Motor status */
    motor_errorcode_t       error_code;
    CAN_HandleTypeDef*      hcan_ptr; /*!< Pointer hcan1*/
    CANRxMessage            canRx; /*Rx CAN message structure */
    CANTxMessage            canTx; /*!< Tx CAN message structure */
    uint8_t                 noResp_counter; /*!< to count number of times motor didn't response to the heartbeat */
}typedef Motor_TypeDef;




#ifdef __cplusplus
}
#endif
#endif // MOTOR_TYPEDEFS_H__