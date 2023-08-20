
#ifndef MOTOR_DEFS_H__
#define MOTOR_DEFS_H__


#ifdef __cplusplus
extern "C"{
#endif


#define NUM_OF_MOTORS           12

#define MOTOR_ID_FR_HIP         1
#define MOTOR_ID_FR_THIGH       2
#define MOTOR_ID_FR_CALF        3
#define MOTOR_ID_FL_HIP         4
#define MOTOR_ID_FL_THIGH       5
#define MOTOR_ID_FL_CALF        6
#define MOTOR_ID_BR_HIP         7
#define MOTOR_ID_BR_THIGH       8
#define MOTOR_ID_BR_CALF        9
#define MOTOR_ID_BL_HIP         10
#define MOTOR_ID_BL_THIGH       11
#define MOTOR_ID_BL_CALF        12

#define CAN_H                   hcan1
#define CAN_CMD_FREQUENCY         100 // Hz
#define CAN_HEARTBEAT_FREQUENCY     1 // Hz
#define NUM_OF_CAN_TX_BYETS         8
#define NUM_OF_CAN_RX_BYTES         7
#define MAX_MOTOR_NO_RESPONSE_COUNT     5 /*!< after this number of times motor doesn't response repeatedly, motor status will be updated as MOTOR_OFFLINE  */


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


/* motor initialization steps; 4-bits */
#define MOTOR_INIT_NOT              (0b0000U)   /* `0x000U` */   
#define MOTOR_INIT_ID               (0b0001U)   /* `0x001U` */
#define MOTOR_INIT_PARAM            (0b0010U)   /* `0x002U` */
#define MOTOR_INIT_LIMITS           (0b0100U)   /* `0x004U` */
#define MOTOR_INIT_CAN              (0b1000U)   /* `0x008U` */
#define MOTOR_INIT_ALL              (0b1111U)   /* `0x015U` */


/* special  motor commands */
#define MOTOR_ENABLE_CMD         {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC}
#define MOTOR_DISABLE_CMD        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD}
#define MOTOR_SETZERO_CMD        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE}
#define MOTOR_HEARTBEAT          {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}


enum MOTORS{
    FR_HIP,
    FR_THIGH,
    FR_CALF,
    FL_HIP,
    FL_THIGH,
    BR_HIP,
    BR_THIGH,
    BR_CALF,
    BL_HIP,
    BL_THIGH,
    BL_CALF
};


enum MOTOR_State{
    MOTOR_READY            = 0b00,
    MOTOR_INITIALIZING  = 0b01,
    MOTOR_ENABLED       = 0b10,
    MOTOR_ERROR         = 0b11
};





#ifdef __cplusplus
}
#endif
#endif





// #define MOTOR_STATUS_ID_SET            0b00000001 /*!< motor id is set                               */
// #define MOTOR_STATUS_PARAMS_SET        0b00000010 /*!< motor parameters are set                      */
// #define MOTOR_STATUS_LIMITS_SET        0b00000100 /*!< motor control limits are set                  */
// #define MOTOR_STATUS_CAN_SET           0b00001000 /*!< motor CAN is configured                       */
// #define MOTOR_STATUS_ONLINE            0b00010000 /*!< motor is online                               */
// #define MOTOR_STATUS_ENABLED           0b00100000 /*!< motor is enabled                              */
// #define MOTOR_STATUS_IN_RANGE          0b01000000 /*!< motor position is in limited range            */
// #define MOTOR_STATUS_ERROR             0b10000000 /*!< motor has an error */
// #define MOTOR_STATUS_INITIALIZED       0b00001111 /*!< motor id, params and CAN are initialized      */
// #define MOTOR_STATUS_READY             0b01111111 /*!< motor is ready to be operated                 */