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
}


///  @brief Indicate eroor code using LD3:
/// 
void error_indicator()
{
    no_error();
    while(1)
    {
        if(rmw_err_code != RMW_RET_OK){
            HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
            // blink once to indicate error is related to rmw
            blink_error(3, 1, 400, 200);
            // indicate rmw error code:
            switch (rmw_err_code)
            {
            /// Generic error to indicate operation could not complete successfully
            case RMW_RET_ERROR:
                blink_error(3, 1, 200, 200); 
                break;
            /// The operation was halted early because it exceeded its timeout critera
            case RMW_RET_TIMEOUT:
                blink_error(3, 2, 200, 200); 
                break;
            /// The operation or event handling is not supported.
            case RMW_RET_UNSUPPORTED:
                blink_error(3, 3, 200, 200); 
                break;
            /// Failed to allocate memory
            case RMW_RET_BAD_ALLOC:
                blink_error(3, 4, 200, 200); 
                break;
            /// Argument to function was invalid
            case RMW_RET_INVALID_ARGUMENT: 
                blink_error(3, 5, 200, 200);
                break;
            /// Incorrect rmw implementation.
            case RMW_RET_INCORRECT_RMW_IMPLEMENTATION: 
                blink_error(3, 6, 200, 200);
                break;
            // rmw node specific ret codes in 2XX 
            /// Failed to find node name
            // Using same return code than in rcl
            case RMW_RET_NODE_NAME_NON_EXISTENT: 
                blink_error(3, 7, 200, 200);
                break;
            default:
                break;
            }
        }
        else if (rcl_err_code != RCL_RET_OK){
            HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
            // blink twice to indicate the error is related to rcl
            blink_error(3, 2, 400, 200);
        }
        else{
            no_error();
        }

    osDelay(10);

    }
}

