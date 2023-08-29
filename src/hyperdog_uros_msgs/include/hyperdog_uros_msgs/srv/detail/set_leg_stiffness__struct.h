// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_msgs:srv/SetLegStiffness.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_MSGS__SRV__DETAIL__SET_LEG_STIFFNESS__STRUCT_H_
#define HYPERDOG_UROS_MSGS__SRV__DETAIL__SET_LEG_STIFFNESS__STRUCT_H_

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
#include "hyperdog_uros_msgs/msg/detail/vector3__struct.h"

// Struct defined in srv/SetLegStiffness in the package hyperdog_uros_msgs.
typedef struct hyperdog_uros_msgs__srv__SetLegStiffness_Request
{
  uint8_t leg;
  hyperdog_uros_msgs__msg__Vector3 data;
} hyperdog_uros_msgs__srv__SetLegStiffness_Request;

// Struct for a sequence of hyperdog_uros_msgs__srv__SetLegStiffness_Request.
typedef struct hyperdog_uros_msgs__srv__SetLegStiffness_Request__Sequence
{
  hyperdog_uros_msgs__srv__SetLegStiffness_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_msgs__srv__SetLegStiffness_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'error_msg'
#include "rosidl_runtime_c/string.h"

// Struct defined in srv/SetLegStiffness in the package hyperdog_uros_msgs.
typedef struct hyperdog_uros_msgs__srv__SetLegStiffness_Response
{
  bool is_set;
  rosidl_runtime_c__String error_msg;
} hyperdog_uros_msgs__srv__SetLegStiffness_Response;

// Struct for a sequence of hyperdog_uros_msgs__srv__SetLegStiffness_Response.
typedef struct hyperdog_uros_msgs__srv__SetLegStiffness_Response__Sequence
{
  hyperdog_uros_msgs__srv__SetLegStiffness_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_msgs__srv__SetLegStiffness_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_MSGS__SRV__DETAIL__SET_LEG_STIFFNESS__STRUCT_H_
