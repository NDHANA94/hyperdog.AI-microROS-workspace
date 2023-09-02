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
#include "hyperdog_uros_interfaces/srv/init_leg_motors.hpp"
#include "hyperdog_uros_interfaces/srv/init_leg_motors.h"
#include "initLegMotorsMsg_config.cpp"

#include <string>
#include <iostream>
#include <cstdio>

#define MOTOR_PARAM_ERROR_CAN_ID    (0b000000001U)
#define MOTOR_PARAM_ERROR_P         (0b000000010U)
#define MOTOR_PARAM_ERROR_V         (0b000000100U)
#define MOTOR_PARAM_ERROR_KP        (0b000001000U)
#define MOTOR_PARAM_ERROR_KD        (0b000010000U)
#define MOTOR_PARAM_ERROR_IFF       (0b000100000U)
#define MOTOR_PARAM_ERROR_CTRL_P    (0b001000000U)
#define MOTOR_PARAM_ERROR_CTRL_V    (0b010000000U)
#define MOTOR_PARAM_ERROR_CTRL_I    (0b100000000U)

using namespace std::chrono_literals;

std::string motor_name_[12] = {"fr_hip_roll ", "fr_hip_pitch", "fr_knee     ", 
                               "fl_hip_roll ", "fl_hip_pitch", "fl_knee     ",
                               "rr_hip_roll ", "rr_hip_pitch", "rr_knee     ",
                               "rl_hip_roll ", "rl_hip_pitch", "rl_knee     "};

std::string error_list[9] = {"can id must be in range of 1~225",
                             "Motor position parameters are not valid",
                             "Motor velocity parameters are not valid",
                             "Motor kp parameters are not valid",
                             "Motor kd parameters are not valid",
                             "Motor i_ff parameters are not valid",
                             "position ctrl limits should be within the motor position params",
                             "velocity ctrl limits should be within the motor velocity params",
                             "current ctrl limits should be within the motor max current param (7A)"};
void print_motorError(int motor, int error){
    if(motor == -1)
        RCLCPP_ERROR(rclcpp::get_logger("InitLegMotors"), error_list[error]); 

    else if(motor<12 && error < 9){
        RCLCPP_ERROR(rclcpp::get_logger("InitLegMotors"), 
            "[%s] %s", motor_name_[motor].c_str(), error_list[error].c_str());
    }
}

/* =========================================================================================================
                                    INIT LEG MOTORS CLIENT
                                            MAIN
========================================================================================================== */

int main(int argc, char** argv)
{

    rclcpp::init(argc, argv);

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("initlegmotors_client");
    rclcpp::Client<hyperdog_uros_interfaces::srv::InitLegMotors>::SharedPtr client = 
        node->create_client<hyperdog_uros_interfaces::srv::InitLegMotors>("initLegMotors");

    auto request = std::make_shared<hyperdog_uros_interfaces::srv::InitLegMotors::Request>();
    auto req_msg = get_initLegMotors_reqMsg();
    request->data = req_msg;
    
    while (!client->wait_for_service(1s)){
        if(!rclcpp::ok()){
            RCLCPP_ERROR(rclcpp::get_logger("InitLegMotors"), 
                "Interupted while waiting for the service. Exiting.");
            return 0;
        }
        RCLCPP_INFO(rclcpp::get_logger("InitLegMotors"), "service not available, waiting again...");
    }

    // hyperdog_uros_interfaces__srv__InitLegMotors_Response res;
    auto res = client->async_send_request(request);

    // Wait for the result and print in logger
    if(rclcpp::spin_until_future_complete(node, res) == rclcpp::FutureReturnCode::SUCCESS)
    {
        for (int i=0; i<12; i++){
            uint16_t error_code = res.get()->error_code[i];
            if(error_code==0){
                RCLCPP_INFO(rclcpp::get_logger(motor_name_[i]), "Motor is sucessfully initialized.");
            }else{
                RCLCPP_ERROR(rclcpp::get_logger(motor_name_[i]), "Failed to initialize motor.");
                if((error_code & MOTOR_PARAM_ERROR_CAN_ID) == MOTOR_PARAM_ERROR_CAN_ID)
                    print_motorError(i, 0);
                if((error_code & MOTOR_PARAM_ERROR_P) == MOTOR_PARAM_ERROR_P)
                    print_motorError(i, 1);
                if((error_code & MOTOR_PARAM_ERROR_V) == MOTOR_PARAM_ERROR_V)
                    print_motorError(i, 2);
                if((error_code & MOTOR_PARAM_ERROR_KP) == MOTOR_PARAM_ERROR_KP)
                    print_motorError(i, 3);
                if((error_code & MOTOR_PARAM_ERROR_KD) == MOTOR_PARAM_ERROR_KD)
                    print_motorError(i, 4);
                if((error_code & MOTOR_PARAM_ERROR_IFF) == MOTOR_PARAM_ERROR_IFF)
                    print_motorError(i, 5);
                if((error_code & MOTOR_PARAM_ERROR_CTRL_P) == MOTOR_PARAM_ERROR_CTRL_P)
                    print_motorError(i, 6);
                if((error_code & MOTOR_PARAM_ERROR_CTRL_V) == MOTOR_PARAM_ERROR_CTRL_V)
                    print_motorError(i, 7);
                if((error_code & MOTOR_PARAM_ERROR_CTRL_I) == MOTOR_PARAM_ERROR_CTRL_I)
                    print_motorError(i, 8);
            }
        }
    }else{
        RCLCPP_INFO(rclcpp::get_logger("InitLegMotors"), "Failed to call service initlegmotors");
    }

    rclcpp::shutdown();
    return 0;
}