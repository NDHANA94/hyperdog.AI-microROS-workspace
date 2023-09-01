// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_interfaces:msg/LegsCmd.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_INTERFACES__MSG__DETAIL__LEGS_CMD__STRUCT_H_
#define HYPERDOG_UROS_INTERFACES__MSG__DETAIL__LEGS_CMD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'fr'
// Member 'fl'
// Member 'rr'
// Member 'rl'
#include "hyperdog_uros_interfaces/msg/detail/leg_cmd__struct.h"

// Struct defined in msg/LegsCmd in the package hyperdog_uros_interfaces.
typedef struct hyperdog_uros_interfaces__msg__LegsCmd
{
  hyperdog_uros_interfaces__msg__LegCmd fr;
  hyperdog_uros_interfaces__msg__LegCmd fl;
  hyperdog_uros_interfaces__msg__LegCmd rr;
  hyperdog_uros_interfaces__msg__LegCmd rl;
} hyperdog_uros_interfaces__msg__LegsCmd;

// Struct for a sequence of hyperdog_uros_interfaces__msg__LegsCmd.
typedef struct hyperdog_uros_interfaces__msg__LegsCmd__Sequence
{
  hyperdog_uros_interfaces__msg__LegsCmd * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_interfaces__msg__LegsCmd__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_INTERFACES__MSG__DETAIL__LEGS_CMD__STRUCT_H_
