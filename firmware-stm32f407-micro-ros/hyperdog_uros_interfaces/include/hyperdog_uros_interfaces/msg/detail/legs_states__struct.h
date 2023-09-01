// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_interfaces:msg/LegsStates.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_INTERFACES__MSG__DETAIL__LEGS_STATES__STRUCT_H_
#define HYPERDOG_UROS_INTERFACES__MSG__DETAIL__LEGS_STATES__STRUCT_H_

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
#include "hyperdog_uros_interfaces/msg/detail/leg_states__struct.h"

// Struct defined in msg/LegsStates in the package hyperdog_uros_interfaces.
typedef struct hyperdog_uros_interfaces__msg__LegsStates
{
  hyperdog_uros_interfaces__msg__LegStates fr;
  hyperdog_uros_interfaces__msg__LegStates fl;
  hyperdog_uros_interfaces__msg__LegStates rr;
  hyperdog_uros_interfaces__msg__LegStates rl;
} hyperdog_uros_interfaces__msg__LegsStates;

// Struct for a sequence of hyperdog_uros_interfaces__msg__LegsStates.
typedef struct hyperdog_uros_interfaces__msg__LegsStates__Sequence
{
  hyperdog_uros_interfaces__msg__LegsStates * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_interfaces__msg__LegsStates__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_INTERFACES__MSG__DETAIL__LEGS_STATES__STRUCT_H_
