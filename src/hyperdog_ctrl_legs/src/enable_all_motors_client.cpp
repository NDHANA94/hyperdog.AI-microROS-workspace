#include "rclcpp/rclcpp.hpp"
#include "hyperdog_uros_msgs/srv/enable_all_motors.hpp"


#include <string>
#include <iostream>
#include <cstdio>

using namespace std::chrono_literals;

int main(int argc, char** argv)
{

    rclcpp::init(argc, argv);

    
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("enableallmotors_client");
    rclcpp::Client<hyperdog_uros_msgs::srv::EnableAllMotors>::SharedPtr client = 
        node->create_client<hyperdog_uros_msgs::srv::EnableAllMotors>("enableallmotors");

    auto request = std::make_shared<hyperdog_uros_msgs::srv::EnableAllMotors::Request>();

    request->enable = true;
    
    while (!client->wait_for_service(1s)){
        if(!rclcpp::ok()){
            RCLCPP_ERROR(rclcpp::get_logger("EnableAllMotors_client"), "Interupted while waiting for the service. Exiting.");
            return 0;
        }
        RCLCPP_INFO(rclcpp::get_logger("EnableAllMotors_client"), "service not available, waiting again...");
    }

    auto response = client->async_send_request(request);

    // Wait for the result
    if(rclcpp::spin_until_future_complete(node, response) ==
        rclcpp::FutureReturnCode::SUCCESS)
    {
        if(response.get()->is_enabled){
            RCLCPP_INFO(rclcpp::get_logger("EnableAllMotors_client"), "All motors are enabled");
        }else{
            RCLCPP_ERROR(rclcpp::get_logger("uros_legMotors"), "failed to enable all the motors or few motors");
            // const char* error_msg = response.get()->error_msg.data;
            RCLCPP_ERROR(rclcpp::get_logger("uros_legMotors"), "%s", response.get()->error_msg.data());
        }
    }else{
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Failed to call service enableAllMotors");
    }

    rclcpp::shutdown();
    return 0;
}