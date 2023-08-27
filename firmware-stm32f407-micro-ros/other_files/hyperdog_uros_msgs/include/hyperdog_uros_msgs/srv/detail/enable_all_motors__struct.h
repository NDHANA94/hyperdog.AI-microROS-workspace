// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_msgs:srv/EnableAllMotors.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_MSGS__SRV__DETAIL__ENABLE_ALL_MOTORS__STRUCT_H_
#define HYPERDOG_UROS_MSGS__SRV__DETAIL__ENABLE_ALL_MOTORS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in srv/EnableAllMotors in the package hyperdog_uros_msgs.
typedef struct hyperdog_uros_msgs__srv__EnableAllMotors_Request
{
  bool enable;
} hyperdog_uros_msgs__srv__EnableAllMotors_Request;

// Struct for a sequence of hyperdog_uros_msgs__srv__EnableAllMotors_Request.
typedef struct hyperdog_uros_msgs__srv__EnableAllMotors_Request__Sequence
{
  hyperdog_uros_msgs__srv__EnableAllMotors_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_msgs__srv__EnableAllMotors_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'error_msg'
#include "rosidl_runtime_c/string.h"

// Struct defined in srv/EnableAllMotors in the package hyperdog_uros_msgs.
typedef struct hyperdog_uros_msgs__srv__EnableAllMotors_Response
{
  bool is_enabled;
  rosidl_runtime_c__String error_msg;
} hyperdog_uros_msgs__srv__EnableAllMotors_Response;

// Struct for a sequence of hyperdog_uros_msgs__srv__EnableAllMotors_Response.
typedef struct hyperdog_uros_msgs__srv__EnableAllMotors_Response__Sequence
{
  hyperdog_uros_msgs__srv__EnableAllMotors_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_msgs__srv__EnableAllMotors_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_MSGS__SRV__DETAIL__ENABLE_ALL_MOTORS__STRUCT_H_