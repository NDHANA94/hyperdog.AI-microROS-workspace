// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_interfaces:srv/SetLegDamping.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_INTERFACES__SRV__DETAIL__SET_LEG_DAMPING__STRUCT_H_
#define HYPERDOG_UROS_INTERFACES__SRV__DETAIL__SET_LEG_DAMPING__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'data'
#include "hyperdog_uros_interfaces/msg/detail/vector3__struct.h"

// Struct defined in srv/SetLegDamping in the package hyperdog_uros_interfaces.
typedef struct hyperdog_uros_interfaces__srv__SetLegDamping_Request
{
  uint8_t leg;
  hyperdog_uros_interfaces__msg__Vector3 data;
} hyperdog_uros_interfaces__srv__SetLegDamping_Request;

// Struct for a sequence of hyperdog_uros_interfaces__srv__SetLegDamping_Request.
typedef struct hyperdog_uros_interfaces__srv__SetLegDamping_Request__Sequence
{
  hyperdog_uros_interfaces__srv__SetLegDamping_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_interfaces__srv__SetLegDamping_Request__Sequence;


// Constants defined in the message

// Struct defined in srv/SetLegDamping in the package hyperdog_uros_interfaces.
typedef struct hyperdog_uros_interfaces__srv__SetLegDamping_Response
{
  int16_t error_code;
} hyperdog_uros_interfaces__srv__SetLegDamping_Response;

// Struct for a sequence of hyperdog_uros_interfaces__srv__SetLegDamping_Response.
typedef struct hyperdog_uros_interfaces__srv__SetLegDamping_Response__Sequence
{
  hyperdog_uros_interfaces__srv__SetLegDamping_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_interfaces__srv__SetLegDamping_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_INTERFACES__SRV__DETAIL__SET_LEG_DAMPING__STRUCT_H_
