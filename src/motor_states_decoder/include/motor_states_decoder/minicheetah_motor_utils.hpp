#ifndef MINICHEETAH_MOTOR_UTILS_H__
#define MINICHEETAH_MOTOR_UTILS_H__

#include <stdio.h>
#include "hyperdog_uros_interfaces/msg/motor_feedback.hpp"
#include "hyperdog_uros_interfaces/msg/motor_feedback_encoded.hpp"

float _fminf(float x, float y);
float _fmaxf(float x, float y);
int _float2uint(float x, float x_min, float x_max, int bits);
float _uint2float(int x_int, float x_min, float x_max, int bits);
hyperdog_uros_interfaces::msg::MotorFeedback
unpack_motor_feedback(hyperdog_uros_interfaces::msg::MotorFeedbackEncoded fb_enc);

#endif