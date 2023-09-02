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
#include "hyperdog_uros_interfaces/srv/set_zero_position.hpp"

#include <string>
#include <iostream>
#include <cstring>

using namespace std::chrono_literals;

#define MOTOR_ERROR_HAL_CAN         (0b00000000010U) /*!< `0x004U`   HAL_CAN Error                                 */
#define MOTOR_ERROR_OFFLINE         (0b00000000100U) /*!< `0x008U`   motor is offline / not connected              */
// #define MOTOR_ERROR_OOR             (0b00000001000U) /*!< `0x010U`   Out Of Range error                            */
// #define MOTOR_ERROR_OH              (0b00000010000U) /*!< `0x020U`   Over-Heat error                               */
// #define MOTOR_ERROR_OC              (0b00000100000U) /*!< `0x040U`   Over-Current error                            */
#define MOTOR_ERROR_NOT_INITIALIZED (0xFFFFU)


std::string motor_name_[12] = {"fr_hip_roll", "fr_hip_pitch", "fr_knee", 
                               "fl_hip_roll", "fl_hip_pitch", "fl_knee",
                               "rr_hip_roll", "rr_hip_pitch", "rr_knee",
                               "rl_hip_roll", "rl_hip_pitch", "rl_knee"};

std::string error_list[3] = {"HAL_CAN Error !",
                             "motor is offline / not connected !",
                            //  "Motor position is out of range !",
                            //  "Motor is over heated !",
                            //  "Motor has over-current error !",
                             "Motor is NOT INITIALIZED, please initialize motors before setting zero position!" };

void print_motorError(int motor, int error){
    if(motor == -1)
        RCLCPP_ERROR(rclcpp::get_logger("SetMotorZeroPosition"), error_list[error]); 
    else if(motor<12 && error<3){
        RCLCPP_ERROR(rclcpp::get_logger("SetMotorZeroPosition"), 
            "[%s] %s", motor_name_[motor].c_str(), error_list[error].c_str());
    }
}

void print_help(){
    std::string help = "\n\
============================ HELP ==================================\n\
| Usage: ros2 run hyperdog_ctrl_leg setMotorZeroPosition <argument> |\n\
| <argument> should be one of following joint motor index ids:      |\n\
|    fr_hip_roll                                                    |\n\
|    fr_hip_pitch                                                   |\n\
|    fr_hip_yaw                                                     |\n\
|    fl_hip_roll                                                    |\n\
|    fl_hip_pitch                                                   |\n\
|    fl_hip_yaw                                                     |\n\
|    rr_hip_roll                                                    |\n\
|    rr_hip_pitch                                                   |\n\
|    rr_hip_yaw                                                     |\n\
|    rl_hip_roll                                                    |\n\
|    rl_hip_pitch                                                   |\n\
|    rl_hip_yaw                                                     |\n\
====================================================================";

RCLCPP_INFO(rclcpp::get_logger("setMotorZeroPosition client"), "%s", help.c_str());
}


bool run_client(int motor){
    rclcpp::init(0, nullptr);

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("setMotorZeroPosition_client");
    rclcpp::Client<hyperdog_uros_interfaces::srv::SetZeroPosition>::SharedPtr client = 
        node->create_client<hyperdog_uros_interfaces::srv::SetZeroPosition>("setMotorZeroPosition");

    auto req = std::make_shared<hyperdog_uros_interfaces::srv::SetZeroPosition::Request>();
    switch (motor)
        {
        case 0: req->leg = 0; req->joint = 0;break;
        case 1: req->leg = 0; req->joint = 1;break;
        case 2: req->leg = 0; req->joint = 2;break;
        case 3: req->leg = 1; req->joint = 0;break;
        case 4: req->leg = 1; req->joint = 1;break;
        case 5: req->leg = 1; req->joint = 2;break;
        case 6: req->leg = 2; req->joint = 0;break;
        case 7: req->leg = 2; req->joint = 1;break;
        case 8: req->leg = 2; req->joint = 2;break;
        case 9: req->leg = 3; req->joint = 0;break;
        case 10:req->leg = 3; req->joint = 1;break;
        case 11:req->leg = 3; req->joint = 2;break;       
        default: break;
    }

    while (!client->wait_for_service(1s)){
        if(!rclcpp::ok()){
            RCLCPP_ERROR(rclcpp::get_logger("SetMotorZeroPosition"), "Interupted while waiting for the service. Exiting.");
            return 0;
        }
        RCLCPP_INFO(rclcpp::get_logger("SetMotorZeroPosition"), "service not available, waiting again...");
    }

    auto res = client->async_send_request(req);

    // Wait for the result
    if(rclcpp::spin_until_future_complete(node, res) == rclcpp::FutureReturnCode::SUCCESS)
    {
        uint16_t error_code = res.get()->error_code;
        if( (( error_code & MOTOR_ERROR_HAL_CAN) != MOTOR_ERROR_HAL_CAN)
            && (( error_code & MOTOR_ERROR_OFFLINE) != MOTOR_ERROR_OFFLINE) ){
            RCLCPP_INFO(rclcpp::get_logger("SetMotorZeroPosition"), 
                "[%s] Current motor position is set as zero position.", motor_name_[motor].c_str());
        }
        else{
            if((error_code & MOTOR_ERROR_NOT_INITIALIZED) == MOTOR_ERROR_NOT_INITIALIZED)
                    print_motorError(-1, 2);
            else{
                if((error_code & MOTOR_ERROR_HAL_CAN) == MOTOR_ERROR_HAL_CAN)
                    print_motorError(motor, 0);
                if((error_code & MOTOR_ERROR_OFFLINE) == MOTOR_ERROR_OFFLINE)
                    print_motorError(motor, 1);
            }
        }
    }else{
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Failed to call service enableAllMotors");
        rclcpp::shutdown();
        return 0;
    }
    rclcpp::shutdown();
    return 1;
}


/* ======================================================================================================
                                 SET MOTOR ZERO POSITION CLIENT
                                            MAIN
======================================================================================================= */
int main(int argc, char* argv[])
{
    // if number of arguments is not one:
    if(argc != 2) {
        print_help();
        return -1;
    }
    // check the argument is valid or not
    else{
        bool valid = false;
        int m = 0;
        for (int m=0; m<12; m++){
            if(argv[1] == motor_name_[m]){
                valid = true;
                break;
            }
        }
        // if the argument is valid
        if(valid){
            run_client(m);
            return 0;
        } 
    }

    RCLCPP_ERROR(rclcpp::get_logger("SetMotorZeroPosition"), "%s argument is not valid", argv[1]);
    print_help();
    return -1;
}