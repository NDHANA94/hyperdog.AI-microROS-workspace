// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_msgs:msg/MotorStates.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_MSGS__MSG__DETAIL__MOTOR_STATES__STRUCT_H_
#define HYPERDOG_UROS_MSGS__MSG__DETAIL__MOTOR_STATES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'motor_name'
// Member 'status_msg'
#include "rosidl_runtime_c/string.h"

// constants for array fields with an upper bound
// motor_name
enum
{
  hyperdog_uros_msgs__msg__MotorStates__motor_name__MAX_SIZE = 10
};

// Struct defined in msg/MotorStates in the package hyperdog_uros_msgs.
typedef struct hyperdog_uros_msgs__msg__MotorStates
{
  rosidl_runtime_c__String__Sequence motor_name;
  uint8_t id;
  bool is_available;
  bool is_enabled;
  bool is_error;
  double cur_position;
  double cur_velocity;
  double torque;
  double vb;
  int16_t error_code;
  rosidl_runtime_c__String status_msg;
} hyperdog_uros_msgs__msg__MotorStates;

// Struct for a sequence of hyperdog_uros_msgs__msg__MotorStates.
typedef struct hyperdog_uros_msgs__msg__MotorStates__Sequence
{
  hyperdog_uros_msgs__msg__MotorStates * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_msgs__msg__MotorStates__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_MSGS__MSG__DETAIL__MOTOR_STATES__STRUCT_H_
