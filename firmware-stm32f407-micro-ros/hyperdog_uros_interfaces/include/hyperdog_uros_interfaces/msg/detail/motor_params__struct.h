// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_interfaces:msg/MotorParams.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTOR_PARAMS__STRUCT_H_
#define HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTOR_PARAMS__STRUCT_H_

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
// Member 'kp'
// Member 'kd'
// Member 'i_ff'
#include "hyperdog_uros_interfaces/msg/detail/limit__struct.h"

// Struct defined in msg/MotorParams in the package hyperdog_uros_interfaces.
typedef struct hyperdog_uros_interfaces__msg__MotorParams
{
  uint8_t can_id;
  hyperdog_uros_interfaces__msg__Limit position;
  hyperdog_uros_interfaces__msg__Limit velocity;
  hyperdog_uros_interfaces__msg__Limit kp;
  hyperdog_uros_interfaces__msg__Limit kd;
  hyperdog_uros_interfaces__msg__Limit i_ff;
} hyperdog_uros_interfaces__msg__MotorParams;

// Struct for a sequence of hyperdog_uros_interfaces__msg__MotorParams.
typedef struct hyperdog_uros_interfaces__msg__MotorParams__Sequence
{
  hyperdog_uros_interfaces__msg__MotorParams * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_interfaces__msg__MotorParams__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTOR_PARAMS__STRUCT_H_
