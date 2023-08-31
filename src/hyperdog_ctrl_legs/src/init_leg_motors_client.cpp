#include "rclcpp/rclcpp.hpp"
#include "hyperdog_uros_msgs/srv/init_leg_motors.hpp"
#include "initLegMotorsMsg_config.cpp"

#include "example_interfaces/srv/add_two_ints.hpp"

using namespace std::chrono_literals;

int main(int argc, char** argv)
{

    rclcpp::init(argc, argv);

    
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("initlegmotors_client");
    rclcpp::Client<hyperdog_uros_msgs::srv::InitLegMotors>::SharedPtr client = 
        node->create_client<hyperdog_uros_msgs::srv::InitLegMotors>("initlegmotors");

    auto request = std::make_shared<hyperdog_uros_msgs::srv::InitLegMotors::Request>();
    auto req_msg = get_initLegMotors_reqMsg();
    request->data = req_msg;
    
    while (!client->wait_for_service(1s)){
        if(!rclcpp::ok()){
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interupted while waiting for the service. Exiting.");
            return 0;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    auto response = client->async_send_request(request);

    // Wait for the result
    if(rclcpp::spin_until_future_complete(node, response) ==
        rclcpp::FutureReturnCode::SUCCESS)
    {
        if(response.get()->done){
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "All Leg motors are initialized.");
        }else{
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Failed to initialize motors");
        }
    }else{
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Failed to call service initlegmotors");
    }

    rclcpp::shutdown();
    return 0;
}