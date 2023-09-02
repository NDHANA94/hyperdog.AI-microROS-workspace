#include "rclcpp/rclcpp.hpp"
#include "hyperdog_uros_interfaces/srv/disable_all_motors.hpp"
#include "hyperdog_uros_interfaces/srv/disable_all_motors.h"


#include <string>
#include <iostream>
#include <cstdio>

/* Motor error codes; 11 bits*/
// #define MOTOR_ERROR_PARAM           (0b00000000001U) /*!< `0x002U`   motor parameter error                         */
#define MOTOR_ERROR_HAL_CAN         (0b00000000010U) /*!< `0x004U`   HAL_CAN Error                                 */
#define MOTOR_ERROR_OFFLINE         (0b00000000100U) /*!< `0x008U`   motor is offline / not connected              */
// #define MOTOR_ERROR_OOR             (0b00000001000U) /*!< `0x010U`   Out Of Range error                            */
// #define MOTOR_ERROR_OH              (0b00000010000U) /*!< `0x020U`   Over-Heat error                               */
// #define MOTOR_ERROR_OC              (0b00000100000U) /*!< `0x040U`   Over-Current error                            */
// #define MOTOR_ERROR_EN              (0b00001000000U) /*!< `0x080U`   Failed to enable the motor                    */
#define MOTOR_ERROR_DIS             (0b00010000000U) /*!< `0x100U`   Failed to diable the motor                    */
#define MOTOR_ERROR_NOT_INITIALIZED (0xFFFFU)


using namespace std::chrono_literals;
std::string motor_name_[12] = {"fr_hip_roll ", "fr_hip_pitch", "fr_knee     ", 
                               "fl_hip_roll ", "fl_hip_pitch", "fl_knee     ",
                               "rr_hip_roll ", "rr_hip_pitch", "rr_knee     ",
                               "rl_hip_roll ", "rl_hip_pitch", "rl_knee     "};

std::string error_list[4] = {"Failed to disable the motor (HAL_CAN Error)",
                             "Failed to disable the motor (motor is offline / not connected)",
                             "Failed to disable the motor (Unknown Error)",
                             "Motors are NOT INITIALIZED, please initialize motors first!" };

void print_motorError(int motor, int error){
    if(motor == -1)
        RCLCPP_ERROR(rclcpp::get_logger("DisableAllMotors"), error_list[error]); 
    else if(motor<12 && error<4){
        RCLCPP_ERROR(rclcpp::get_logger("DisableAllMotors"), 
            "[%s] %s", motor_name_[motor].c_str(), error_list[error].c_str());
    }
}



/* ==================================================================================================================
                                    DISABLE ALL MOTOR CLIENT
                                            MAIN
=================================================================================================================== */
int main(int argc, char** argv)
{

    rclcpp::init(argc, argv);

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("disableallmotors_client");
    rclcpp::Client<hyperdog_uros_interfaces::srv::DisableAllMotors>::SharedPtr client = 
        node->create_client<hyperdog_uros_interfaces::srv::DisableAllMotors>("disableAllMotors");

    auto request = std::make_shared<hyperdog_uros_interfaces::srv::DisableAllMotors::Request>();
    
    while (!client->wait_for_service(1s)){
        if(!rclcpp::ok()){
            RCLCPP_ERROR(rclcpp::get_logger("DisableAllMotors"), "Interupted while waiting for the service. Exiting.");
            return 0;
        }
        RCLCPP_INFO(rclcpp::get_logger("DisableAllMotors"), "service not available, waiting again...");
    }

    // hyperdog_uros_interfaces__srv__EnableAllMotors_Response res;
    auto res = client->async_send_request(request);

    // Wait for the result
    if(rclcpp::spin_until_future_complete(node, res) == rclcpp::FutureReturnCode::SUCCESS)
    {
        for(int i=0; i<12; i++){
            uint16_t error_code = res.get()->error_code[i];
            /*  motor is disabled ----------------------------------------------*/
            if((error_code & MOTOR_ERROR_DIS) != MOTOR_ERROR_DIS){
                RCLCPP_INFO(rclcpp::get_logger("DisableAllMotors"), 
                    "[%s] motor is disabled.", motor_name_[i].c_str());
            }
            /* failed  --------------------------------------------------------*/
            else{
                /* motors are not initialized --------------*/
                if((error_code & MOTOR_ERROR_NOT_INITIALIZED) == MOTOR_ERROR_NOT_INITIALIZED){
                    print_motorError(-1, 3);
                    break;
                }
                /* other errors ----------------------------*/
                else{
                    if((error_code & MOTOR_ERROR_HAL_CAN) == MOTOR_ERROR_HAL_CAN)
                        print_motorError(i, 0);
                    if((error_code & MOTOR_ERROR_OFFLINE) == MOTOR_ERROR_OFFLINE)
                        print_motorError(i, 1);
                    // if can ok and motor is online, but not disabled.
                    if(((error_code & 0b00010000110) == MOTOR_ERROR_DIS))
                        print_motorError(i, 2);
                }
            }
        }
    }else{
        RCLCPP_INFO(rclcpp::get_logger("DisableAllMotors"), "Failed to call service enableAllMotors");
    }

    rclcpp::shutdown();
    return 0;
}