// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_msgs:msg/LegStates.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_MSGS__MSG__DETAIL__LEG_STATES__STRUCT_H_
#define HYPERDOG_UROS_MSGS__MSG__DETAIL__LEG_STATES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'leg_id'
#include "rosidl_runtime_c/string.h"
// Member 'position'
// Member 'velocity'
// Member 'applied_force'
// Member 'reaction_force'
#include "hyperdog_uros_msgs/msg/detail/vector3__struct.h"

// Struct defined in msg/LegStates in the package hyperdog_uros_msgs.
typedef struct hyperdog_uros_msgs__msg__LegStates
{
  rosidl_runtime_c__String leg_id;
  bool is_contacted;
  hyperdog_uros_msgs__msg__Vector3 position;
  hyperdog_uros_msgs__msg__Vector3 velocity;
  hyperdog_uros_msgs__msg__Vector3 applied_force;
  hyperdog_uros_msgs__msg__Vector3 reaction_force;
  uint8_t error_code;
} hyperdog_uros_msgs__msg__LegStates;

// Struct for a sequence of hyperdog_uros_msgs__msg__LegStates.
typedef struct hyperdog_uros_msgs__msg__LegStates__Sequence
{
  hyperdog_uros_msgs__msg__LegStates * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_msgs__msg__LegStates__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_MSGS__MSG__DETAIL__LEG_STATES__STRUCT_H_
