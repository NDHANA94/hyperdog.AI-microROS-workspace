#ifndef MINICHEETAH_MOTOR_H__
#define MINICHEETAH_MOTOR_H__

/** This library consists with necessary functions for controlling 12 minicheetah actuators 
 * using one CAN bus.
 * 
 * (#) How to setup:
 *      (##) 1. Set motor IDs for each 12 motors using MOTOR_setID method.
 *      (##) 2. Set motor parameters of each 12 motors using MOTOR_setParams method.
 *      (##) 3. Configure CAN communication using MOTOR_configCAN
 *      (##) 4. strat watchdog to update status and states of each motors
 * 
 * (#) How to control:
 *      (##)
 *      (##) 
 *      (##)
 *      (##)
 *      (##)
 * 
 * (#) Error Code: 
 *      (##) Error code related with CAN bus is indicated by the LD5
 *          (###) 
 *          (###)
 * 
 *      (##) Error code related with motors is indicated by the LD6
 *          (###) Slow blink indicates the motor index which has an error:
 *                  exmample: 1 slow blink -> 0 motor index (NOT ID)
 *          (###) Flast blink indicates the error:
 *                  (####) 1 fast blink: motor is offline
 *                  (####) 2 fast blinks
 */

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



extern Motor_TypeDef motor[NUM_OF_MOTORS];
extern uint8_t motor_enable_cmd[NUM_OF_CAN_TX_BYETS];
extern uint8_t motor_disable_cmd[NUM_OF_CAN_TX_BYETS];
extern uint8_t motor_setzero_cmd[NUM_OF_CAN_TX_BYETS];
extern uint8_t motor_heartbeat_cmd[NUM_OF_CAN_TX_BYETS];

extern uint16_t motor_error_code;
extern uint8_t motor_status;


void MOTOR_setInit(enum MOTORS m, uint8_t id);
void MOTOR_setParams(enum MOTORS m, float pMax, float vMax, float kpMax, float kdMax, float iffMax);
void MOTOR_setCtrlLimits(enum MOTORS m, float pDesMax, float pDesMin, float vMax, float iMax);
void MOTOR_configCAN(enum MOTORS m, CAN_HandleTypeDef* hcan, uint8_t filterbank);
void MOTOR_enable(enum MOTORS m);
void MOTOR_disable(enum MOTORS m);
void MOTOR_setZero(enum MOTORS m);
void MOTOR_sendHeatbeat(enum MOTORS m);
void MOTOR_startWatchdog();

void _update_motor_states();
void _update_motor_status();
void _pack_cmd(enum MOTORS m);
void _unpack_reply(enum MOTORS m);
void _can_read();
void _can_send();

#ifdef __cplusplus
}
#endif





#endif /* MINICHEETAH_MOTOR_H__ */