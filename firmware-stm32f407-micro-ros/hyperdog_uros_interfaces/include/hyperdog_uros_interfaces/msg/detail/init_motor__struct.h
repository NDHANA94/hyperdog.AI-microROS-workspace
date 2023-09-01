// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_interfaces:msg/InitMotor.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_INTERFACES__MSG__DETAIL__INIT_MOTOR__STRUCT_H_
#define HYPERDOG_UROS_INTERFACES__MSG__DETAIL__INIT_MOTOR__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'params'
#include "hyperdog_uros_interfaces/msg/detail/motor_params__struct.h"
// Member 'ctrl_limits'
#include "hyperdog_uros_interfaces/msg/detail/motor_ctrl_limits__struct.h"

// Struct defined in msg/InitMotor in the package hyperdog_uros_interfaces.
typedef struct hyperdog_uros_interfaces__msg__InitMotor
{
  hyperdog_uros_interfaces__msg__MotorParams params;
  hyperdog_uros_interfaces__msg__MotorCtrlLimits ctrl_limits;
} hyperdog_uros_interfaces__msg__InitMotor;

// Struct for a sequence of hyperdog_uros_interfaces__msg__InitMotor.
typedef struct hyperdog_uros_interfaces__msg__InitMotor__Sequence
{
  hyperdog_uros_interfaces__msg__InitMotor * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_interfaces__msg__InitMotor__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_INTERFACES__MSG__DETAIL__INIT_MOTOR__STRUCT_H_
