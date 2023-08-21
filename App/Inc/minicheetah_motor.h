

/* 
==========================================================================================
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
==========================================================================================

 * This library consists with necessary functions for controlling 12 minicheetah actuators 
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



extern Motor_TypeDef motor[NUM_OF_MOTORS];
extern uint8_t motor_enable_cmd[NUM_OF_CAN_TX_BYETS];
extern uint8_t motor_disable_cmd[NUM_OF_CAN_TX_BYETS];
extern uint8_t motor_setzero_cmd[NUM_OF_CAN_TX_BYETS];
extern uint8_t motor_heartbeat_cmd[NUM_OF_CAN_TX_BYETS];

extern uint16_t motor_error_code;
extern uint8_t motor_status;


void MOTOR_initId(enum MOTORS m, uint8_t id);
void MOTOR_initParams(enum MOTORS m, float pMax, float vMax, float kpMax, float kdMax, float iffMax, float vbMax);
void MOTOR_initCtrlLimits(enum MOTORS m, float pDesMax, float pDesMin, float vMax, float iMax);
void MOTOR_initCANConfig(enum MOTORS m, CAN_HandleTypeDef* hcan, uint8_t filterbank);
void MOTOR_enable(enum MOTORS m);
void MOTOR_disable(enum MOTORS m);
void MOTOR_setZero(enum MOTORS m);
void MOTOR_sendTxGetRx(enum MOTORS m);
void MOTOR_sendHeatbeat(enum MOTORS m);
void MOTOR_startWatchdog(); // @todo


void _pack_cmd(enum MOTORS m); // @todo
void _unpack_canRx(enum MOTORS m); // @todo

bool _is_motor_error(enum MOTORS m, uint8_t error_word);

float fminf(float x, float y);
float fmaxf(float x, float y);
int float2uint(float x, float x_min, float x_max, int bits);
float uint2float(int x_int, float x_min, float x_max, int bits);

#ifdef __cplusplus
}
#endif

#endif /* MINICHEETAH_MOTOR_H__ */