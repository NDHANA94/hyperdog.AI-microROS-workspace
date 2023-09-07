#include <cstdio>

#include "motor_states_decoder/minicheetah_motor_utils.hpp"
#include "motor_states_decoder/motor_states_decoder_node.hpp"
#include "hyperdog_uros_interfaces/msg/motors_states_encoded.hpp"

#include "print_color.h"

MotorStatesDecoder::MotorStatesDecoder()
: Node ("motor_states_decoder_node")
{
  RCLCPP_INFO(this->get_logger(), "%sStarting motor_states_decoder_node.%s", GREEN, NC);
  std::string topic_name = "motors_states";
  subscription_ = this->create_subscription<hyperdog_uros_interfaces::msg::MotorsStatesEncoded>(
                  topic_name,
                  rclcpp::SensorDataQoS(),
                  std::bind(&MotorStatesDecoder::subscription_callback,
                  this, std::placeholders::_1));

  publisher_ = this->create_publisher<hyperdog_uros_interfaces::msg::MotorsStates>
              ("motors_states_decoded", 10);
}


MotorStatesDecoder::~MotorStatesDecoder(){}

void MotorStatesDecoder::subscription_callback(
  const hyperdog_uros_interfaces::msg::MotorsStatesEncoded::SharedPtr msg)
{
  pub_msg.fr_hip_roll.is_available = msg->fr_hip_roll.is_available;
  pub_msg.fr_hip_roll.is_enabled   = msg->fr_hip_roll.is_enabled;
  pub_msg.fr_hip_roll.error_code   = msg->fr_hip_roll.error_code;
  pub_msg.fr_hip_roll.status_msg   = msg->fr_hip_roll.status_msg;
  pub_msg.fr_hip_roll.feedback  = unpack_motor_feedback(msg->fr_hip_roll.feedback);
  pub_msg.fr_hip_pitch.is_available = msg->fr_hip_pitch.is_available;
  pub_msg.fr_hip_pitch.is_enabled   = msg->fr_hip_pitch.is_enabled;
  pub_msg.fr_hip_pitch.error_code   = msg->fr_hip_pitch.error_code;
  pub_msg.fr_hip_pitch.status_msg   = msg->fr_hip_pitch.status_msg;
  pub_msg.fr_hip_pitch.feedback = unpack_motor_feedback(msg->fr_hip_pitch.feedback);
  pub_msg.fr_knee.is_available = msg->fr_knee.is_available;
  pub_msg.fr_knee.is_enabled   = msg->fr_knee.is_enabled;
  pub_msg.fr_knee.error_code   = msg->fr_knee.error_code;
  pub_msg.fr_knee.status_msg   = msg->fr_knee.status_msg;
  pub_msg.fr_knee.feedback      = unpack_motor_feedback(msg->fr_knee.feedback);

  pub_msg.fl_hip_roll.is_available = msg->fl_hip_roll.is_available;
  pub_msg.fl_hip_roll.is_enabled   = msg->fl_hip_roll.is_enabled;
  pub_msg.fl_hip_roll.error_code   = msg->fl_hip_roll.error_code;
  pub_msg.fl_hip_roll.status_msg   = msg->fl_hip_roll.status_msg;
  pub_msg.fl_hip_roll.feedback  = unpack_motor_feedback(msg->fl_hip_roll.feedback);
  pub_msg.fl_hip_pitch.is_available = msg->fl_hip_pitch.is_available;
  pub_msg.fl_hip_pitch.is_enabled   = msg->fl_hip_pitch.is_enabled;
  pub_msg.fl_hip_pitch.error_code   = msg->fl_hip_pitch.error_code;
  pub_msg.fl_hip_pitch.status_msg   = msg->fl_hip_pitch.status_msg;
  pub_msg.fl_hip_pitch.feedback = unpack_motor_feedback(msg->fl_hip_pitch.feedback);
  pub_msg.fl_knee.is_available = msg->fl_knee.is_available;
  pub_msg.fl_knee.is_enabled   = msg->fl_knee.is_enabled;
  pub_msg.fl_knee.error_code   = msg->fl_knee.error_code;
  pub_msg.fl_knee.status_msg   = msg->fl_knee.status_msg;
  pub_msg.fl_knee.feedback      = unpack_motor_feedback(msg->fl_knee.feedback);

  pub_msg.rr_hip_roll.is_available = msg->rr_hip_roll.is_available;
  pub_msg.rr_hip_roll.is_enabled   = msg->rr_hip_roll.is_enabled;
  pub_msg.rr_hip_roll.error_code   = msg->rr_hip_roll.error_code;
  pub_msg.rr_hip_roll.status_msg   = msg->rr_hip_roll.status_msg;
  pub_msg.rr_hip_roll.feedback  = unpack_motor_feedback(msg->rr_hip_roll.feedback);
  pub_msg.rr_hip_pitch.is_available = msg->rr_hip_pitch.is_available;
  pub_msg.rr_hip_pitch.is_enabled   = msg->rr_hip_pitch.is_enabled;
  pub_msg.rr_hip_pitch.error_code   = msg->rr_hip_pitch.error_code;
  pub_msg.rr_hip_pitch.status_msg   = msg->rr_hip_pitch.status_msg;
  pub_msg.rr_hip_pitch.feedback = unpack_motor_feedback(msg->rr_hip_pitch.feedback);
  pub_msg.rr_knee.is_available = msg->rr_knee.is_available;
  pub_msg.rr_knee.is_enabled   = msg->rr_knee.is_enabled;
  pub_msg.rr_knee.error_code   = msg->rr_knee.error_code;
  pub_msg.rr_knee.status_msg   = msg->rr_knee.status_msg;
  pub_msg.rr_knee.feedback      = unpack_motor_feedback(msg->rr_knee.feedback);

  pub_msg.rl_hip_roll.is_available = msg->rl_hip_roll.is_available;
  pub_msg.rl_hip_roll.is_enabled   = msg->rl_hip_roll.is_enabled;
  pub_msg.rl_hip_roll.error_code   = msg->rl_hip_roll.error_code;
  pub_msg.rl_hip_roll.status_msg   = msg->rl_hip_roll.status_msg;
  pub_msg.rl_hip_roll.feedback  = unpack_motor_feedback(msg->rl_hip_roll.feedback);
  pub_msg.rl_hip_pitch.is_available = msg->rl_hip_pitch.is_available;
  pub_msg.rl_hip_pitch.is_enabled   = msg->rl_hip_pitch.is_enabled;
  pub_msg.rl_hip_pitch.error_code   = msg->rl_hip_pitch.error_code;
  pub_msg.rl_hip_pitch.status_msg   = msg->rl_hip_pitch.status_msg;
  pub_msg.rl_hip_pitch.feedback = unpack_motor_feedback(msg->rl_hip_pitch.feedback);
  pub_msg.rl_knee.is_available = msg->rl_knee.is_available;
  pub_msg.rl_knee.is_enabled   = msg->rl_knee.is_enabled;
  pub_msg.rl_knee.error_code   = msg->rl_knee.error_code;
  pub_msg.rl_knee.status_msg   = msg->rl_knee.status_msg;
  pub_msg.rl_knee.feedback      = unpack_motor_feedback(msg->rl_knee.feedback);

  publisher_->publish(pub_msg);
}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MotorStatesDecoder>());
  rclcpp::shutdown();
  return 0;
}
