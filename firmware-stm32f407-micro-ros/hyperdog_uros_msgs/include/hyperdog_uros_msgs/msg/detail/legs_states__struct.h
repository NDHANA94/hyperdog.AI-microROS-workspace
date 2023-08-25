// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_msgs:msg/LegsStates.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_MSGS__MSG__DETAIL__LEGS_STATES__STRUCT_H_
#define HYPERDOG_UROS_MSGS__MSG__DETAIL__LEGS_STATES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'fr_leg'
// Member 'fl_leg'
// Member 'rr_leg'
// Member 'rl_leg'
#include "hyperdog_uros_msgs/msg/detail/leg_states__struct.h"

// Struct defined in msg/LegsStates in the package hyperdog_uros_msgs.
typedef struct hyperdog_uros_msgs__msg__LegsStates
{
  hyperdog_uros_msgs__msg__LegStates fr_leg;
  hyperdog_uros_msgs__msg__LegStates fl_leg;
  hyperdog_uros_msgs__msg__LegStates rr_leg;
  hyperdog_uros_msgs__msg__LegStates rl_leg;
} hyperdog_uros_msgs__msg__LegsStates;

// Struct for a sequence of hyperdog_uros_msgs__msg__LegsStates.
typedef struct hyperdog_uros_msgs__msg__LegsStates__Sequence
{
  hyperdog_uros_msgs__msg__LegsStates * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_msgs__msg__LegsStates__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_MSGS__MSG__DETAIL__LEGS_STATES__STRUCT_H_
