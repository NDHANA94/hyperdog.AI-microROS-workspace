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

#include "error_indicator.h"
#include "uros_tasks.h"
#include "minicheetah_motor.h"
#include "can.h"

rmw_ret_t rmw_err_code;
rcl_ret_t rcl_err_code;

void blink_error(int LD, int times, int on_period, int off_period){
    HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LD4_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
    switch (LD)
    {
    case 3:
        HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
        for (int i = 0; i<times; i++){
            HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
            osDelay(on_period);
            HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
            osDelay(off_period);
        }
        osDelay(1000);
        break;
    case 4:
        HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
        for (int i = 0; i<times; i++){
            HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
            osDelay(on_period);
            HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
            osDelay(off_period);
        }
        osDelay(1000);
        break;
    case 5:
        HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
        for (int i = 0; i<times; i++){
            HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
            osDelay(on_period);
            HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
            osDelay(off_period);
        }
        osDelay(1000);
        break;
    case 6:
        HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
        for (int i = 0; i<times; i++){
            HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_SET);
            osDelay(on_period);
            HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
            osDelay(off_period);
        }
        osDelay(1000);
        break;
    
    default:
        break;
    }
}

void no_error(){
    HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
    osDelay(100);
    HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
    osDelay(100);
    HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
    osDelay(100);
    HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
    osDelay(100);
    HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_SET);
    osDelay(100);
    HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
    osDelay(100);
    HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
    osDelay(100);
    HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
    osDelay(100);
}


///  @brief Indicate eroor code using LD3:
/// 
void error_indicator()
{
    while(1)
    {
        /* UROS Errors -> LD3 Orange*/
        if(uros.state != UROS_RUNNING){
            HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
            osDelay(500);
            /*  Failed to create RMW transport                          */
            if((uros.error_code & UROS_ERROR_RMW_TRANSPORT) == UROS_ERROR_RMW_TRANSPORT) 
                blink_error(3, 1, 200, 200);
            /*  Failed to allocate memory for FreeRTOS                  */
            else if((uros.error_code & UROS_ERROR_FREERTOS_ALLOC) == UROS_ERROR_FREERTOS_ALLOC) 
                blink_error(3, 2, 200, 200);
            /*  Failed to connect with the Agent or create rcl support  */
            else if((uros.error_code & UROS_ERROR_RCL_SUPPORT_INIT) == UROS_ERROR_RCL_SUPPORT_INIT) 
                blink_error(3, 3, 200, 200);
            /*  Failed to initialize the node                           */
            else if((uros.error_code & UROS_ERROR_RCL_NODE_INIT) == UROS_ERROR_RCL_NODE_INIT) 
                blink_error(3, 4, 200, 200);
            /*  Failed to initialize the motor feedback publisher       */
            else if((uros.error_code & UROS_ERROR_RCL_MOTOR_FB_PUB_INIT) == UROS_ERROR_RCL_MOTOR_FB_PUB_INIT) 
                blink_error(3, 5, 200, 200);
            /*  Failed to publish motor feedback                        */
            else if((uros.error_code & UROS_ERROR_RCL_MOTOR_FB_PUB) == UROS_ERROR_RCL_MOTOR_FB_PUB) 
                blink_error(3, 6, 200, 200);
        }
        else{
            HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
            osDelay(100);
            HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
            osDelay(100);
        }

        /* If uros is running check CAN */
        /* CAN Errors -> LD5 Red*/
        if (hcan1.State == HAL_CAN_STATE_ERROR){
            HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
            osDelay(500);
            /*!< Protocol Error Warning                               */
            if((hcan1.ErrorCode & HAL_CAN_ERROR_EWG) == HAL_CAN_ERROR_EWG)
                blink_error(5, 1, 200, 200);
            /*!< Error Passive                                        */
            else if((hcan1.ErrorCode & HAL_CAN_ERROR_EPV) == HAL_CAN_ERROR_EPV)
                blink_error(5, 2, 200, 200);
            /*!< Parameter error ; can be ocuured due to lost of can bus connection or no msg received*/
            else if((hcan1.ErrorCode & HAL_CAN_ERROR_PARAM) == HAL_CAN_ERROR_PARAM)
                blink_error(5, 3, 200, 200);
            /*!< Bus-off error                                        */
            else if((hcan1.ErrorCode & HAL_CAN_ERROR_BOF) == HAL_CAN_ERROR_BOF)
                blink_error(5, 4, 200, 200);
            /*!< Stuff error                                          */
            else if((hcan1.ErrorCode & HAL_CAN_ERROR_STF) == HAL_CAN_ERROR_STF)
                blink_error(5, 5, 200, 200);
            /*!< Form error                                           */
            else if((hcan1.ErrorCode & HAL_CAN_ERROR_FOR) == HAL_CAN_ERROR_FOR)
                blink_error(5, 6, 200, 200);
            /*!< Acknowledgment error                                 */
            else if((hcan1.ErrorCode & HAL_CAN_ERROR_ACK) == HAL_CAN_ERROR_ACK)
                blink_error(5, 7, 200, 200);
            /*!< Bit recessive error                                  */
            else if((hcan1.ErrorCode & HAL_CAN_ERROR_BR) == HAL_CAN_ERROR_BR)
                blink_error(5, 8, 200, 200);
            /*!< Bit dominant error                                   */
            else if((hcan1.ErrorCode & HAL_CAN_ERROR_BD) == HAL_CAN_ERROR_BD)
                blink_error(5, 9, 200, 200);
            /*!< CRC error                                            */
            else if((hcan1.ErrorCode & HAL_CAN_ERROR_CRC) == HAL_CAN_ERROR_CRC)
                blink_error(5, 10, 200, 200);
            /*!< Rx FIFO0 overrun error                               */
            else if((hcan1.ErrorCode & HAL_CAN_ERROR_RX_FOV0) == HAL_CAN_ERROR_RX_FOV0)
                blink_error(5, 11, 200, 200);
            /*!< Rx FIFO1 overrun error                               */
            else if((hcan1.ErrorCode & HAL_CAN_ERROR_RX_FOV1) == HAL_CAN_ERROR_RX_FOV1)
                blink_error(5, 12, 200, 200);
            /*!< TxMailbox 0 transmit failure due to arbitration lost */
            else if((hcan1.ErrorCode & HAL_CAN_ERROR_TX_ALST0) == HAL_CAN_ERROR_TX_ALST0)
                blink_error(5, 13, 200, 200);
            /*!< TxMailbox 0 transmit failure due to transmit error    */
            else if((hcan1.ErrorCode & HAL_CAN_ERROR_TX_TERR0) == HAL_CAN_ERROR_TX_TERR0)
                blink_error(5, 14, 200, 200);
            /*!< TxMailbox 1 transmit failure due to arbitration lost */
            else if((hcan1.ErrorCode & HAL_CAN_ERROR_TX_ALST1) == HAL_CAN_ERROR_TX_ALST1)
                blink_error(5, 15, 200, 200);
            /*!< TxMailbox 1 transmit failure due to transmit error    */
            else if((hcan1.ErrorCode & HAL_CAN_ERROR_TX_TERR1) == HAL_CAN_ERROR_TX_TERR1)
                blink_error(5, 16, 200, 200);
            /*!< TxMailbox 2 transmit failure due to arbitration lost */
            else if((hcan1.ErrorCode & HAL_CAN_ERROR_TX_ALST2) == HAL_CAN_ERROR_TX_ALST2)
                blink_error(5, 17, 200, 200);
            /*!< TxMailbox 2 transmit failure due to transmit error    */
            else if((hcan1.ErrorCode & HAL_CAN_ERROR_TX_TERR2) == HAL_CAN_ERROR_TX_TERR2)
                blink_error(5, 18, 200, 200);
            /*!< Timeout error                                        */
            else if((hcan1.ErrorCode & HAL_CAN_ERROR_TIMEOUT) == HAL_CAN_ERROR_TIMEOUT)
                blink_error(5, 19, 200, 200);
            /*!< Peripheral not initialized                           */
            else if((hcan1.ErrorCode & HAL_CAN_ERROR_NOT_INITIALIZED) == HAL_CAN_ERROR_NOT_INITIALIZED)
                blink_error(5, 20, 200, 200);
            /*!< Peripheral not ready                                 */
            else if((hcan1.ErrorCode & HAL_CAN_ERROR_NOT_READY) == HAL_CAN_ERROR_NOT_READY)
                blink_error(5, 21, 200, 200);
            /*!< Peripheral not started                               */
            else if((hcan1.ErrorCode & HAL_CAN_ERROR_NOT_STARTED) == HAL_CAN_ERROR_NOT_STARTED)
                blink_error(5, 22, 200, 200);
        }
        else{
            HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
            osDelay(100);
            HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
            osDelay(100);
        }

        /* If uros and CAN are OK, check motors */
        /* Motors Error - LD6 Blue*/
        /* Long blinks indicate the motor index (NOT ID). Short blinks indicate the error */
        bool is_motor_err = false;
        if (hcan1.State != HAL_CAN_STATE_ERROR)
        {
            for(int m = 0; m < NUM_OF_MOTORS; m++)
            {   
                // if motor is initialized and has an error
                if((motor[m].init_state & MOTOR_INIT_ID) == MOTOR_INIT_ID && motor[m].state == MOTOR_ERROR) 
                {
                    is_motor_err = true;
                    HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
                    HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
                    HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
                    HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
                    osDelay(500);

                    blink_error(6, m+1, 800, 200); /* long blinks */

                    /*!< `0x001U`   motor is not initialized                      */
                    if((motor[m].error_code & MOTOR_ERROR_NOT_INITIALIZED) == MOTOR_ERROR_NOT_INITIALIZED)
                        blink_error(6, 1, 200, 200); /* 1 short blink */
                    /*!< `0x002U`   motor parameter error                         */
                    else if((motor[m].error_code & MOTOR_ERROR_PARAM) == MOTOR_ERROR_PARAM)
                        blink_error(6, 2, 200, 200); /* 2 short blinks */
                    /*!< `0x004U`   HAL_CAN Error                                 */
                    else if((motor[m].error_code & MOTOR_ERROR_HAL_CAN) == MOTOR_ERROR_HAL_CAN)
                        blink_error(6, 3, 200, 200); /* 3 short blinks */
                    /*!< `0x008U`   motor is offline / not connected              */
                    else if((motor[m].error_code & MOTOR_ERROR_OFFLINE) == MOTOR_ERROR_OFFLINE)
                        blink_error(6, 4, 200, 200); /* 4 short blinks */
                    /*!< `0x010U`   Out Of Range error                            */
                    else if((motor[m].error_code & MOTOR_ERROR_OOR) == MOTOR_ERROR_OOR)
                        blink_error(6, 5, 200, 200); /* 5 short blinks */
                    /*!< `0x020U`   Over-Heat error                               */
                    else if((motor[m].error_code & MOTOR_ERROR_OH) == MOTOR_ERROR_OH)
                        blink_error(6, 6, 200, 200); /* 6 short blinks */
                    /*!< `0x040U`   Over-Current error                            */
                    else if((motor[m].error_code & MOTOR_ERROR_OC) == MOTOR_ERROR_OC)
                        blink_error(6, 7, 200, 200); /* 7 short blinks */
                    /*!< `0x080U`   Failed to enable the motor                    */
                    else if((motor[m].error_code & MOTOR_ERROR_EN) == MOTOR_ERROR_EN)
                        blink_error(6, 8, 200, 200); /* 8 short blinks */
                    /*!< `0x100U`   Failed to diable the motor                    */
                    else if((motor[m].error_code & MOTOR_ERROR_DIS) == MOTOR_ERROR_DIS)
                        blink_error(6, 9, 200, 200); /* 9 short blinks */
                    /*!< `0x200U`   Failed to set motor zero position             */
                    else if((motor[m].error_code & MOTOR_ERROR_SZ) == MOTOR_ERROR_SZ)
                        blink_error(6, 10, 200, 200); /* 10 short blinks */
                    /*!< `0x400U`   Motor is not ready to be operated             */
                    else if((motor[m].error_code & MOTOR_ERROR_NOT_READY) == MOTOR_ERROR_NOT_READY)
                        blink_error(6, 11, 200, 200); /* 11 short blinks */
                }
                /* If no Errors,  */
            }
            if(!is_motor_err){
                HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
                osDelay(100);
                HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_SET);
                osDelay(100);
            }
        }

        HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
        osDelay(100);
        HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
        osDelay(100);

    }
}

