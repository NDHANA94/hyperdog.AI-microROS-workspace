// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_interfaces:msg/MotorCmd.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTOR_CMD__STRUCT_H_
#define HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTOR_CMD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/MotorCmd in the package hyperdog_uros_interfaces.
typedef struct hyperdog_uros_interfaces__msg__MotorCmd
{
  uint8_t leg;
  uint8_t joint;
  bool enable;
  bool disable;
  bool set_zero;
  float desire_position;
  float desire_velocity;
  float kp;
  float kd;
  float i_ff;
} hyperdog_uros_interfaces__msg__MotorCmd;

// Struct for a sequence of hyperdog_uros_interfaces__msg__MotorCmd.
typedef struct hyperdog_uros_interfaces__msg__MotorCmd__Sequence
{
  hyperdog_uros_interfaces__msg__MotorCmd * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_interfaces__msg__MotorCmd__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTOR_CMD__STRUCT_H_
