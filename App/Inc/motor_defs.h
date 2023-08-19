
#ifndef MOTOR_DEFS_H__
#define MOTOR_DEFS_H__


#ifdef __cplusplus
extern "C"{
#endif

#ifdef __cplusplus
}
#endif


#define NUM_OF_MOTORS          12
#define CAN_H                  hcan1
#define NUM_OF_TX_BYETS         8
#define NUM_OF_RX_BYTES         7

/* Motor error codes */
#define MOTOR_OK                0
#define MOTOR_CAN_FAILED        1
#define MOTOR_NOT_AVAILABLE     2
#define MOTOR_OUT_OF_RANGE      3
#define MOTOR_OVER_HEATED       4
#define MOTOR_OVER_CURRENT      5
#define MOTOR_INIT_ERROR        -1
 

// motor status
#define MOTOR_ID_SET            0b00000001
#define MOTOR_CAN_SET           0b00000010
#define MOTOR_ONLINE            0b00000100
#define MOTOR_ENABLED           0b00001000
#define MOTOR_PARAMS_SET        0b00010000
#define MOTOR_CTRL_LIMITS_SET   0b00100000
#define MOTOR_IN_RANGE          0b01000000
#define MOTOR_READY             0b01111111


// special  motor commands
#define MOTOR_ENABLE_CMD         {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC}
#define MOTOR_DISABLE_CMD        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD}
#define MOTOR_SETZERO_CMD        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE}
#define MOTOR_HEARTBEAT          {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}



#endif