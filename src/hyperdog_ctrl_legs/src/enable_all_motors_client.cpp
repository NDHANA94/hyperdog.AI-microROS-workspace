/**
 * Author: Nipun Dhananjaya Weerakkodi  (nipun.dhananjaya@gmail.com)
 * Last update: 02.09.2023
 * 
===========================================================================================
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

#include "rclcpp/rclcpp.hpp"
#include "hyperdog_uros_interfaces/srv/enable_all_motors.hpp"
#include "hyperdog_uros_interfaces/srv/enable_all_motors.h"


#include <string>
#include <iostream>
#include <cstdio>

/* Motor error codes; 11 bits*/
#define MOTOR_ERROR_PARAM           (0b00000000001U) /*!< `0x002U`   motor parameter error                         */
#define MOTOR_ERROR_HAL_CAN         (0b00000000010U) /*!< `0x004U`   HAL_CAN Error                                 */
#define MOTOR_ERROR_OFFLINE         (0b00000000100U) /*!< `0x008U`   motor is offline / not connected              */
#define MOTOR_ERROR_OOR             (0b00000001000U) /*!< `0x010U`   Out Of Range error                            */
#define MOTOR_ERROR_OH              (0b00000010000U) /*!< `0x020U`   Over-Heat error                               */
#define MOTOR_ERROR_OC              (0b00000100000U) /*!< `0x040U`   Over-Current error                            */
#define MOTOR_ERROR_EN              (0b00001000000U) /*!< `0x080U`   Failed to enable the motor                    */
#define MOTOR_ERROR_NOT_INITIALIZED (0xFFFFU)

using namespace std::chrono_literals;
std::string motor_name_[12] = {"fr_hip_roll ", "fr_hip_pitch", "fr_knee     ", 
                               "fl_hip_roll ", "fl_hip_pitch", "fl_knee     ",
                               "rr_hip_roll ", "rr_hip_pitch", "rr_knee     ",
                               "rl_hip_roll ", "rl_hip_pitch", "rl_knee     "};

std::string error_list[8] = {"Failed to enable the motor (motor parameter error!)",
                             "Failed to enable the motor (HAL_CAN Error!)",
                             "Failed to enable the motor (motor is offline / not connected!)",
                             "Failed to enable the motor (Motor position is out of range!)",
                             "Failed to enable the motor (Motor is over heated!)",
                             "Failed to enable the motor (Motor has over-current error!)",
                             "Failed to enable the motor (Unknown Error!)",
                             "Motor is NOT INITIALIZED, please initialize motors before enabling!" };

void print_motorError(int motor, int error){
    if(motor == -1)
        RCLCPP_ERROR(rclcpp::get_logger("EnableAllMotors"), error_list[error]); 

    else if(motor<12 && error < 8){
        RCLCPP_ERROR(rclcpp::get_logger("EnableAllMotors"), 
            "[%s] %s", motor_name_[motor].c_str(), error_list[error].c_str());
    }
}



/* ======================================================================================================
                                    ENABLE ALL MOTOR CLIENT
                                            MAIN
======================================================================================================= */
int main(int argc, char** argv)
{

    rclcpp::init(argc, argv);

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("enableallmotors_client");
    rclcpp::Client<hyperdog_uros_interfaces::srv::EnableAllMotors>::SharedPtr client = 
        node->create_client<hyperdog_uros_interfaces::srv::EnableAllMotors>("enableAllMotors");

    auto request = std::make_shared<hyperdog_uros_interfaces::srv::EnableAllMotors::Request>();
    
    while (!client->wait_for_service(1s)){
        if(!rclcpp::ok()){
            RCLCPP_ERROR(rclcpp::get_logger("EnableAllMotors"), "Interupted while waiting for the service. Exiting.");
            return 0;
        }
        RCLCPP_INFO(rclcpp::get_logger("EnableAllMotors"), "service not available, waiting again...");
    }

    // hyperdog_uros_interfaces__srv__EnableAllMotors_Response res;
    auto res = client->async_send_request(request);

    // Wait for the result
    if(rclcpp::spin_until_future_complete(node, res) == rclcpp::FutureReturnCode::SUCCESS)
    {
        for(int i=0; i<12; i++){
            uint16_t error_code = res.get()->error_code[i];
            /* motor is enabled -----------------------------------------------------------------*/
            if((error_code & MOTOR_ERROR_EN) != MOTOR_ERROR_EN){
                RCLCPP_INFO(rclcpp::get_logger("EnableAllMotors"), 
                    "[%s] motor is enabled.", motor_name_[i].c_str());
            }
            /* failed ---------------------------------------------------------------------------*/
            else{
                /* motors are not initialized ----------------------------*/
                if((error_code & MOTOR_ERROR_NOT_INITIALIZED) == MOTOR_ERROR_NOT_INITIALIZED){
                    print_motorError(-1, 7);
                    break;
                }
                /* other errors ------------------------------------------*/
                else{
                    if((error_code & MOTOR_ERROR_PARAM) == MOTOR_ERROR_PARAM)
                        print_motorError(i, 0);
                    if((error_code & MOTOR_ERROR_HAL_CAN) == MOTOR_ERROR_HAL_CAN)
                        print_motorError(i, 1);
                    if((error_code & MOTOR_ERROR_OFFLINE) == MOTOR_ERROR_OFFLINE)
                        print_motorError(i, 2);
                    if((error_code & MOTOR_ERROR_OOR) == MOTOR_ERROR_OOR)
                        print_motorError(i, 3);
                    if((error_code & MOTOR_ERROR_OH) == MOTOR_ERROR_OH)
                        print_motorError(i, 4);
                    if((error_code & MOTOR_ERROR_OC) == MOTOR_ERROR_OC)
                        print_motorError(i, 5); 
                    // if everything is ok, but not enabled:
                    if((error_code & 0b1111111) == MOTOR_ERROR_EN)
                        print_motorError(i, 6);
                }
            }
        }
    }else{
        RCLCPP_INFO(rclcpp::get_logger("EnableAllMotors"), "Failed to call service enableAllMotors");
    }
    // RCLCPP_INFO(rclcpp::get_logger("EnableAllMotors"), "%i", res.get()->error_code[0]);
    rclcpp::shutdown();
    return 0;
}