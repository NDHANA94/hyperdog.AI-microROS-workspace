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


int main(int argc, char** argv)
{

    rclcpp::init(argc, argv);

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("initlegmotors_client");
    rclcpp::Client<hyperdog_uros_interfaces::srv::InitLegMotors>::SharedPtr client = 
        node->create_client<hyperdog_uros_interfaces::srv::InitLegMotors>("initlegmotors");

    auto request = std::make_shared<hyperdog_uros_interfaces::srv::InitLegMotors::Request>();
    auto req_msg = get_initLegMotors_reqMsg();
    request->data = req_msg;
    
    while (!client->wait_for_service(1s)){
        if(!rclcpp::ok()){
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interupted while waiting for the service. Exiting.");
            return 0;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    // hyperdog_uros_interfaces__srv__InitLegMotors_Response res;
    auto res = client->async_send_request(request);

    // Wait for the result and print in logger
    if(rclcpp::spin_until_future_complete(node, res) == rclcpp::FutureReturnCode::SUCCESS)
    {
        for (int i=0; i<12; i++){
            if(res.get()->error_code[i]==0){
                RCLCPP_INFO(rclcpp::get_logger(motor_name_[i]), "Motor is sucessfully initialized.");
            }else{
                RCLCPP_ERROR(rclcpp::get_logger(motor_name_[i]), "Failed to initialize motor.");
                if((res.get()->error_code[i] & MOTOR_PARAM_ERROR_CAN_ID) == MOTOR_PARAM_ERROR_CAN_ID)
                    RCLCPP_ERROR(rclcpp::get_logger(motor_name_[i]), error_list[0]);
                if((res.get()->error_code[i] & MOTOR_PARAM_ERROR_P) == MOTOR_PARAM_ERROR_P)
                    RCLCPP_ERROR(rclcpp::get_logger(motor_name_[i]), error_list[1]);
                if((res.get()->error_code[i] & MOTOR_PARAM_ERROR_V) == MOTOR_PARAM_ERROR_V)
                    RCLCPP_ERROR(rclcpp::get_logger(motor_name_[i]), error_list[2]);
                if((res.get()->error_code[i] & MOTOR_PARAM_ERROR_KP) == MOTOR_PARAM_ERROR_KP)
                    RCLCPP_ERROR(rclcpp::get_logger(motor_name_[i]), error_list[3]);
                if((res.get()->error_code[i] & MOTOR_PARAM_ERROR_KD) == MOTOR_PARAM_ERROR_KD)
                    RCLCPP_ERROR(rclcpp::get_logger(motor_name_[i]), error_list[4]);
                if((res.get()->error_code[i] & MOTOR_PARAM_ERROR_IFF) == MOTOR_PARAM_ERROR_IFF)
                    RCLCPP_ERROR(rclcpp::get_logger(motor_name_[i]), error_list[5]);
                if((res.get()->error_code[i] & MOTOR_PARAM_ERROR_CTRL_P) == MOTOR_PARAM_ERROR_CTRL_P)
                    RCLCPP_ERROR(rclcpp::get_logger(motor_name_[i]), error_list[6]);
                if((res.get()->error_code[i] & MOTOR_PARAM_ERROR_CTRL_V) == MOTOR_PARAM_ERROR_CTRL_V)
                    RCLCPP_ERROR(rclcpp::get_logger(motor_name_[i]), error_list[7]);
                if((res.get()->error_code[i] & MOTOR_PARAM_ERROR_CTRL_I) == MOTOR_PARAM_ERROR_CTRL_I)
                    RCLCPP_ERROR(rclcpp::get_logger(motor_name_[i]), error_list[8]);
            }
        }
    }else{
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Failed to call service initlegmotors");
    }

    rclcpp::shutdown();
    return 0;
}