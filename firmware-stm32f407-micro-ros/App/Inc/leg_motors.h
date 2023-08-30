#ifndef _LEG_MOTORS_H_
#define _LEG_MOTORS_H

#ifdef __cplusplus
extern "C"{
#endif

#include "can.h"

#include "hyperdog_uros_msgs/msg/init_motor.h"
#include "hyperdog_uros_msgs/msg/init_leg_motors.h"
#include "hyperdog_uros_msgs/msg/motor_states.h"
#include "hyperdog_uros_msgs/srv/init_leg_motors.h"
#include "hyperdog_uros_msgs/msg/motor_cmd.h"


#define MAX_MOTOR_CURRENT                7 // A


#define CAN_H                           hcan1
#define CAN_CMD_FREQUENCY               100 // Hz
#define CAN_HEARTBEAT_FREQUENCY         1 // Hz
#define NUM_OF_CAN_TX_BYETS             8
#define NUM_OF_CAN_RX_BYTES             6 // 7
#define MAX_MOTOR_NO_RESPONSE_COUNT     5 /*!< after this number of times motor doesn't response repeatedly, motor status will be updated as MOTOR_OFFLINE  */

#define NUM_OF_LEGS                     4
#define NUM_OF_JOINTS_PER_LEG           3

/* Motor error codes; 11 bits*/
#define MOTOR_ERROR_NONE            (0b00000000000U) /*!< `0x000U`   No error                                      */
#define MOTOR_ERROR_NOT_INITIALIZED (0b00000000001U) /*!< `0x001U`   motor is not initialized                      */
#define MOTOR_ERROR_PARAM           (0b00000000010U) /*!< `0x002U`   motor parameter error                         */
#define MOTOR_ERROR_HAL_CAN         (0b00000000100U) /*!< `0x004U`   HAL_CAN Error                                 */
#define MOTOR_ERROR_OFFLINE         (0b00000001000U) /*!< `0x008U`   motor is offline / not connected              */
#define MOTOR_ERROR_OOR             (0b00000010000U) /*!< `0x010U`   Out Of Range error                            */
#define MOTOR_ERROR_OH              (0b00000100000U) /*!< `0x020U`   Over-Heat error                               */
#define MOTOR_ERROR_OC              (0b00001000000U) /*!< `0x040U`   Over-Current error                            */
#define MOTOR_ERROR_EN              (0b00010000000U) /*!< `0x080U`   Failed to enable the motor                    */
#define MOTOR_ERROR_DIS             (0b00100000000U) /*!< `0x100U`   Failed to diable the motor                    */
#define MOTOR_ERROR_SZ              (0b01000000000U) /*!< `0x200U`   Failed to set motor zero position             */
#define MOTOR_ERROR_NOT_READY       (0b10000000000U) /*!< `0x400U`   Motor is not ready to be operated             */
#define MOTOR_ERROR_INITIAL         (0b00000000111U) /*!< `0x007U`   initial state of the error code               */

/* motor initialization steps status; 2-bits */
#define MOTOR_INIT_STATUS_NOT_INITIALIZED  (0b00U)   /* `0x000U` */   
#define MOTOR_INIT_STATUS_PARAM_SET        (0b01U)   /* `0x001U` */
#define MOTOR_INIT_STATUS_CAN_SET          (0b10U)   /* `0x002U` */
#define MOTOR_INIT_STATUS_INITIALIZED      (0b11U)   /* `0x003U` */  

/* special  motor commands */
#define MOTOR_ENABLE_CMD         {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC}
#define MOTOR_DISABLE_CMD        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD}
#define MOTOR_SETZERO_CMD        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE}
#define MOTOR_HEARTBEAT          {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}


/* enum for motor state
@param MOTOR_READY
@param MOTOR_INITIALIZING
@param
@param */
enum MOTOR_State{
    MOTOR_NOT_INITIALIZED,
    MOTOR_INITIALIZED,
    MOTOR_DISABLED, 
    MOTOR_ENABLED,
    MOTOR_ERROR          
};


/* Typedef for Motor CAN TX message
@param data[7] 
@param header 
@param TxMailBox */
typedef struct{
    /* 
    7:`[pdes HIGH 8]` 6:`[pdes LOW 8]` 5:`[vdes High 8]` 4:`[vdes LOW 4 | kp HIGH 4]` 
    3:`[kp LOW 8]` 2:`[kd HIGH 8]` 1:`[kd LOW 4 | iff HIGH 4]` 0:`[iff LOW 8]`*/
    uint8_t data[8];
    CAN_TxHeaderTypeDef header;
    uint32_t TxMailBox;
}CANTxMessage_TypeDef;


/* Typedef for Motor CAN RX messages
@param data[8]
@param header 
@param TxMailBox */
typedef struct{
    /* 
    6:`[ID]` 5:`[position HIGH 8]` 4:`[position LOW 8]` 3:`[velocity HIGH 8]` 
    2:`[velocity LOW 4 | torque HIGH 4]` 1:`[torque LOW 8]` 0:`[vb]` */
    uint8_t data[NUM_OF_CAN_RX_BYTES];
    CAN_RxHeaderTypeDef header;
    CAN_FilterTypeDef filter;
}CANRxMessage_TypeDef;


struct{
    /*
    @param id  CAN ID of the motor
    @param leg  Leg index (FR=0, FL=1, RR=2, RL=3)
    @param joint Joint index (HIP_ROLL=0, HIP_PITCH=1, KNEE=2)
    @param params Parameters of the motor (position.min, position.max, velocity.min, velocity.max, kp.min, kp.max, kd.min, kd.max, iff.min, iff.max)
    @param ctrl_limits To set limits for joint position, joint velocity and motor current */
    hyperdog_uros_msgs__msg__InitMotor      self;   
    /*
    @param is_available 
    @param is_enabled
    @param is_error
    @param error_code
    @param status_msg
    @param feedback id, position, velocity, torque and vb of th motor */
    hyperdog_uros_msgs__msg__MotorStates    state; 
    /* 
    @param p_des desire position
    @param v_des desire velocity
    @param kp stiffness
    @param kd damping
    @param i_ff feed forward current */
    hyperdog_uros_msgs__msg__MotorCmd       cmd;
    /* 
    Pointer to the  `CAN HandleTypeDef`*/
    CAN_HandleTypeDef*                      hcan; 
    /* 
    @param data[8]
    @param header 
    @param TxMailBox */
    CANRxMessage_TypeDef                    canRx;
    /* 
    @param data[7] 
    @param header 
    @param TxMailBox */
    CANTxMessage_TypeDef                    canTx;
    uint8_t                                 init_status;
    enum MOTOR_State                        debug_state;
}typedef LegMotor_TypeDef;

extern LegMotor_TypeDef** legMotor;

void init_legMotors(CAN_HandleTypeDef* hcan, 
                    hyperdog_uros_msgs__srv__InitLegMotors_Request* req, 
                    hyperdog_uros_msgs__srv__InitLegMotors_Response* res);



#ifdef __cplusplus
}
#endif
#endif

