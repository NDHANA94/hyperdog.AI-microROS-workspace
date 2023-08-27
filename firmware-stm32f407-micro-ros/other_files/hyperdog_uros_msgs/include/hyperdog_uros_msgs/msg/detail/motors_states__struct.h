// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_msgs:msg/MotorsStates.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_MSGS__MSG__DETAIL__MOTORS_STATES__STRUCT_H_
#define HYPERDOG_UROS_MSGS__MSG__DETAIL__MOTORS_STATES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'fr_hip_roll'
// Member 'fr_hip_pitch'
// Member 'fr_knee'
// Member 'fl_hip_roll'
// Member 'fl_hip_pitch'
// Member 'fl_knee'
// Member 'rr_hip_roll'
// Member 'rr_hip_pitch'
// Member 'rr_knee'
// Member 'rl_hip_roll'
// Member 'rl_hip_pitch'
// Member 'rl_knee'
#include "hyperdog_uros_msgs/msg/detail/motor_states__struct.h"

// Struct defined in msg/MotorsStates in the package hyperdog_uros_msgs.
typedef struct hyperdog_uros_msgs__msg__MotorsStates
{
  hyperdog_uros_msgs__msg__MotorStates fr_hip_roll;
  hyperdog_uros_msgs__msg__MotorStates fr_hip_pitch;
  hyperdog_uros_msgs__msg__MotorStates fr_knee;
  hyperdog_uros_msgs__msg__MotorStates fl_hip_roll;
  hyperdog_uros_msgs__msg__MotorStates fl_hip_pitch;
  hyperdog_uros_msgs__msg__MotorStates fl_knee;
  hyperdog_uros_msgs__msg__MotorStates rr_hip_roll;
  hyperdog_uros_msgs__msg__MotorStates rr_hip_pitch;
  hyperdog_uros_msgs__msg__MotorStates rr_knee;
  hyperdog_uros_msgs__msg__MotorStates rl_hip_roll;
  hyperdog_uros_msgs__msg__MotorStates rl_hip_pitch;
  hyperdog_uros_msgs__msg__MotorStates rl_knee;
} hyperdog_uros_msgs__msg__MotorsStates;

// Struct for a sequence of hyperdog_uros_msgs__msg__MotorsStates.
typedef struct hyperdog_uros_msgs__msg__MotorsStates__Sequence
{
  hyperdog_uros_msgs__msg__MotorsStates * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_msgs__msg__MotorsStates__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_MSGS__MSG__DETAIL__MOTORS_STATES__STRUCT_H_
