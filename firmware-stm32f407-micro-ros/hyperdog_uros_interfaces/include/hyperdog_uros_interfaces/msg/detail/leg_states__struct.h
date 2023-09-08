// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_interfaces:msg/LegStates.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_INTERFACES__MSG__DETAIL__LEG_STATES__STRUCT_H_
#define HYPERDOG_UROS_INTERFACES__MSG__DETAIL__LEG_STATES__STRUCT_H_

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
// Member 'applied_force'
// Member 'reaction_force'
// Member 'stiffness_ratio'
// Member 'damping_ratio'
#include "hyperdog_uros_interfaces/msg/detail/vector3__struct.h"

// Struct defined in msg/LegStates in the package hyperdog_uros_interfaces.
typedef struct hyperdog_uros_interfaces__msg__LegStates
{
  bool is_contacted;
  uint8_t error_code;
  hyperdog_uros_interfaces__msg__Vector3 position;
  hyperdog_uros_interfaces__msg__Vector3 velocity;
  hyperdog_uros_interfaces__msg__Vector3 applied_force;
  hyperdog_uros_interfaces__msg__Vector3 reaction_force;
  hyperdog_uros_interfaces__msg__Vector3 stiffness_ratio;
  hyperdog_uros_interfaces__msg__Vector3 damping_ratio;
  float joint_ang[3];
} hyperdog_uros_interfaces__msg__LegStates;

// Struct for a sequence of hyperdog_uros_interfaces__msg__LegStates.
typedef struct hyperdog_uros_interfaces__msg__LegStates__Sequence
{
  hyperdog_uros_interfaces__msg__LegStates * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_interfaces__msg__LegStates__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_INTERFACES__MSG__DETAIL__LEG_STATES__STRUCT_H_
