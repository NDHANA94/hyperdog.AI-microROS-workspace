// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_interfaces:msg/Limit.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_INTERFACES__MSG__DETAIL__LIMIT__STRUCT_H_
#define HYPERDOG_UROS_INTERFACES__MSG__DETAIL__LIMIT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Limit in the package hyperdog_uros_interfaces.
typedef struct hyperdog_uros_interfaces__msg__Limit
{
  double min;
  double max;
} hyperdog_uros_interfaces__msg__Limit;

// Struct for a sequence of hyperdog_uros_interfaces__msg__Limit.
typedef struct hyperdog_uros_interfaces__msg__Limit__Sequence
{
  hyperdog_uros_interfaces__msg__Limit * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_interfaces__msg__Limit__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_INTERFACES__MSG__DETAIL__LIMIT__STRUCT_H_
