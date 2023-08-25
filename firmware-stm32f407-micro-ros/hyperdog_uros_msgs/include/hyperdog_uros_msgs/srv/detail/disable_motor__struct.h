// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_msgs:srv/DisableMotor.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_MSGS__SRV__DETAIL__DISABLE_MOTOR__STRUCT_H_
#define HYPERDOG_UROS_MSGS__SRV__DETAIL__DISABLE_MOTOR__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'leg'
// Member 'joint'
#include "rosidl_runtime_c/string.h"

// constants for array fields with an upper bound
// leg
enum
{
  hyperdog_uros_msgs__srv__DisableMotor_Request__leg__MAX_SIZE = 2
};
// joint
enum
{
  hyperdog_uros_msgs__srv__DisableMotor_Request__joint__MAX_SIZE = 10
};

// Struct defined in srv/DisableMotor in the package hyperdog_uros_msgs.
typedef struct hyperdog_uros_msgs__srv__DisableMotor_Request
{
  rosidl_runtime_c__String__Sequence leg;
  rosidl_runtime_c__String__Sequence joint;
} hyperdog_uros_msgs__srv__DisableMotor_Request;

// Struct for a sequence of hyperdog_uros_msgs__srv__DisableMotor_Request.
typedef struct hyperdog_uros_msgs__srv__DisableMotor_Request__Sequence
{
  hyperdog_uros_msgs__srv__DisableMotor_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_msgs__srv__DisableMotor_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'error_msg'
// already included above
// #include "rosidl_runtime_c/string.h"

// Struct defined in srv/DisableMotor in the package hyperdog_uros_msgs.
typedef struct hyperdog_uros_msgs__srv__DisableMotor_Response
{
  bool is_disabled;
  rosidl_runtime_c__String error_msg;
} hyperdog_uros_msgs__srv__DisableMotor_Response;

// Struct for a sequence of hyperdog_uros_msgs__srv__DisableMotor_Response.
typedef struct hyperdog_uros_msgs__srv__DisableMotor_Response__Sequence
{
  hyperdog_uros_msgs__srv__DisableMotor_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_msgs__srv__DisableMotor_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_MSGS__SRV__DETAIL__DISABLE_MOTOR__STRUCT_H_
