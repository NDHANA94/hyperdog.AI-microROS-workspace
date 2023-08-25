// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_msgs:msg/MotorCmd.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_MSGS__MSG__DETAIL__MOTOR_CMD__STRUCT_H_
#define HYPERDOG_UROS_MSGS__MSG__DETAIL__MOTOR_CMD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/MotorCmd in the package hyperdog_uros_msgs.
typedef struct hyperdog_uros_msgs__msg__MotorCmd
{
  bool enable;
  double desire_position;
  double desire_velocity;
  double kp;
  double kd;
  double i_ff;
} hyperdog_uros_msgs__msg__MotorCmd;

// Struct for a sequence of hyperdog_uros_msgs__msg__MotorCmd.
typedef struct hyperdog_uros_msgs__msg__MotorCmd__Sequence
{
  hyperdog_uros_msgs__msg__MotorCmd * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_msgs__msg__MotorCmd__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_MSGS__MSG__DETAIL__MOTOR_CMD__STRUCT_H_