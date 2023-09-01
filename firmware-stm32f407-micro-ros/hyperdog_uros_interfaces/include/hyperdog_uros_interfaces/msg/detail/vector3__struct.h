// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_interfaces:msg/Vector3.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_INTERFACES__MSG__DETAIL__VECTOR3__STRUCT_H_
#define HYPERDOG_UROS_INTERFACES__MSG__DETAIL__VECTOR3__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Vector3 in the package hyperdog_uros_interfaces.
typedef struct hyperdog_uros_interfaces__msg__Vector3
{
  double x;
  double y;
  double z;
} hyperdog_uros_interfaces__msg__Vector3;

// Struct for a sequence of hyperdog_uros_interfaces__msg__Vector3.
typedef struct hyperdog_uros_interfaces__msg__Vector3__Sequence
{
  hyperdog_uros_interfaces__msg__Vector3 * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_interfaces__msg__Vector3__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_INTERFACES__MSG__DETAIL__VECTOR3__STRUCT_H_
