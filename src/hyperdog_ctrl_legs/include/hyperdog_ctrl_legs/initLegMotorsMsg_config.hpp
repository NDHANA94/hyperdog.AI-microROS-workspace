#ifndef INIT_LEG_MOTORS_MSG_CONFIG_H__
#define INIT_LEG_MOTORS_MSG_CONFIG_H__


#include "hyperdog_uros_interfaces/msg/init_leg_motors.hpp"
#include "rclcpp/rclcpp.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>
using namespace std::chrono_literals;

#define NUM_OF_MOTORS           12
#define MAX_MOTOR_CURRENT       7.0



hyperdog_uros_interfaces::msg::InitLegMotors get_initLegMotors_reqMsg();

#endif