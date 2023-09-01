// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_interfaces:msg/MotorCtrlLimits.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTOR_CTRL_LIMITS__STRUCT_H_
#define HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTOR_CTRL_LIMITS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'position'
// Member 'velocity'
// Member 'current'
#include "hyperdog_uros_interfaces/msg/detail/limit__struct.h"

// Struct defined in msg/MotorCtrlLimits in the package hyperdog_uros_interfaces.
typedef struct hyperdog_uros_interfaces__msg__MotorCtrlLimits
{
  hyperdog_uros_interfaces__msg__Limit position;
  hyperdog_uros_interfaces__msg__Limit velocity;
  hyperdog_uros_interfaces__msg__Limit current;
} hyperdog_uros_interfaces__msg__MotorCtrlLimits;

// Struct for a sequence of hyperdog_uros_interfaces__msg__MotorCtrlLimits.
typedef struct hyperdog_uros_interfaces__msg__MotorCtrlLimits__Sequence
{
  hyperdog_uros_interfaces__msg__MotorCtrlLimits * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_interfaces__msg__MotorCtrlLimits__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTOR_CTRL_LIMITS__STRUCT_H_
