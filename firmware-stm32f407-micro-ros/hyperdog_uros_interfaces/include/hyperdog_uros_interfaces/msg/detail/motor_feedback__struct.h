// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_interfaces:msg/MotorFeedback.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTOR_FEEDBACK__STRUCT_H_
#define HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTOR_FEEDBACK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/MotorFeedback in the package hyperdog_uros_interfaces.
typedef struct hyperdog_uros_interfaces__msg__MotorFeedback
{
  uint8_t can_id;
  float position;
  float velocity;
  float torque;
  float vb;
} hyperdog_uros_interfaces__msg__MotorFeedback;

// Struct for a sequence of hyperdog_uros_interfaces__msg__MotorFeedback.
typedef struct hyperdog_uros_interfaces__msg__MotorFeedback__Sequence
{
  hyperdog_uros_interfaces__msg__MotorFeedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_interfaces__msg__MotorFeedback__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTOR_FEEDBACK__STRUCT_H_
