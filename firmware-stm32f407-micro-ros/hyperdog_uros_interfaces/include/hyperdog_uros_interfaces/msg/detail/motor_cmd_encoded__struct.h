// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_interfaces:msg/MotorCmdEncoded.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTOR_CMD_ENCODED__STRUCT_H_
#define HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTOR_CMD_ENCODED__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/MotorCmdEncoded in the package hyperdog_uros_interfaces.
typedef struct hyperdog_uros_interfaces__msg__MotorCmdEncoded
{
  uint8_t can_id;
  bool enable;
  bool disable;
  bool set_zero;
  uint8_t cmd[8];
} hyperdog_uros_interfaces__msg__MotorCmdEncoded;

// Struct for a sequence of hyperdog_uros_interfaces__msg__MotorCmdEncoded.
typedef struct hyperdog_uros_interfaces__msg__MotorCmdEncoded__Sequence
{
  hyperdog_uros_interfaces__msg__MotorCmdEncoded * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_interfaces__msg__MotorCmdEncoded__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTOR_CMD_ENCODED__STRUCT_H_
