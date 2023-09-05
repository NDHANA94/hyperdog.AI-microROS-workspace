// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_interfaces:msg/MotorStatesEncoded.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTOR_STATES_ENCODED__STRUCT_H_
#define HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTOR_STATES_ENCODED__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'status_msg'
#include "rosidl_runtime_c/string.h"
// Member 'feedback'
#include "hyperdog_uros_interfaces/msg/detail/motor_feedback_encoded__struct.h"

// Struct defined in msg/MotorStatesEncoded in the package hyperdog_uros_interfaces.
typedef struct hyperdog_uros_interfaces__msg__MotorStatesEncoded
{
  bool is_available;
  bool is_enabled;
  bool is_error;
  int16_t error_code;
  rosidl_runtime_c__String status_msg;
  hyperdog_uros_interfaces__msg__MotorFeedbackEncoded feedback;
} hyperdog_uros_interfaces__msg__MotorStatesEncoded;

// Struct for a sequence of hyperdog_uros_interfaces__msg__MotorStatesEncoded.
typedef struct hyperdog_uros_interfaces__msg__MotorStatesEncoded__Sequence
{
  hyperdog_uros_interfaces__msg__MotorStatesEncoded * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_interfaces__msg__MotorStatesEncoded__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTOR_STATES_ENCODED__STRUCT_H_
