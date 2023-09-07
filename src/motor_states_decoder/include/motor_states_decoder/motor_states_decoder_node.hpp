/**
 * @author: Nipun Dhananjaya Weerakkodi (nipun.dhananjaya@gmail.com)
 * @created: 07/09/2023
 * @last_update: ---
 */

#ifndef MOTOR_STATES_DECODER_NODE_H__
#define MOTOR_STATES_DECODER_NODE_H__

#include <cstdio>
// #include <functional>
#include <memory>
#include <string>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "hyperdog_uros_interfaces/msg/motors_states_encoded.hpp"
#include "hyperdog_uros_interfaces/msg/motors_states.hpp"

#include "motor_states_decoder/minicheetah_motor_utils.hpp"

#include "std_msgs/msg/string.hpp"

#define PKG_NAME "motor_states_decoder"

using namespace std::chrono_literals;

auto pub_msg = hyperdog_uros_interfaces::msg::MotorsStates();

#pragma once
class MotorStatesDecoder : public rclcpp::Node
{
private:
    void subscription_callback(const hyperdog_uros_interfaces::msg::MotorsStatesEncoded::SharedPtr msg);
    
    rclcpp::Subscription<hyperdog_uros_interfaces::msg::MotorsStatesEncoded>::SharedPtr subscription_;
    rclcpp::Publisher<hyperdog_uros_interfaces::msg::MotorsStates>::SharedPtr publisher_;

public:
    MotorStatesDecoder();
    ~MotorStatesDecoder();
};



#endif