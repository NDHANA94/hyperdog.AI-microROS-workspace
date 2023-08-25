// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_msgs:srv/SetMotorsControlLimits.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_MSGS__SRV__DETAIL__SET_MOTORS_CONTROL_LIMITS__STRUCT_H_
#define HYPERDOG_UROS_MSGS__SRV__DETAIL__SET_MOTORS_CONTROL_LIMITS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'fr_hip_pitch'
// Member 'fr_hip_roll'
// Member 'fr_knee'
// Member 'fl_hip_pitch'
// Member 'fl_hip_roll'
// Member 'fl_knee'
// Member 'rr_hip_pitch'
// Member 'rr_hip_roll'
// Member 'rr_knee'
// Member 'rl_hip_pitch'
// Member 'rl_hip_roll'
// Member 'rl_knee'
#include "hyperdog_uros_msgs/msg/detail/motor_ctrl_limits__struct.h"

// Struct defined in srv/SetMotorsControlLimits in the package hyperdog_uros_msgs.
typedef struct hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request
{
  hyperdog_uros_msgs__msg__MotorCtrlLimits fr_hip_pitch;
  hyperdog_uros_msgs__msg__MotorCtrlLimits fr_hip_roll;
  hyperdog_uros_msgs__msg__MotorCtrlLimits fr_knee;
  hyperdog_uros_msgs__msg__MotorCtrlLimits fl_hip_pitch;
  hyperdog_uros_msgs__msg__MotorCtrlLimits fl_hip_roll;
  hyperdog_uros_msgs__msg__MotorCtrlLimits fl_knee;
  hyperdog_uros_msgs__msg__MotorCtrlLimits rr_hip_pitch;
  hyperdog_uros_msgs__msg__MotorCtrlLimits rr_hip_roll;
  hyperdog_uros_msgs__msg__MotorCtrlLimits rr_knee;
  hyperdog_uros_msgs__msg__MotorCtrlLimits rl_hip_pitch;
  hyperdog_uros_msgs__msg__MotorCtrlLimits rl_hip_roll;
  hyperdog_uros_msgs__msg__MotorCtrlLimits rl_knee;
} hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request;

// Struct for a sequence of hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request.
typedef struct hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__Sequence
{
  hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'error_msg'
#include "rosidl_runtime_c/string.h"

// Struct defined in srv/SetMotorsControlLimits in the package hyperdog_uros_msgs.
typedef struct hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response
{
  bool is_set;
  rosidl_runtime_c__String error_msg;
} hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response;

// Struct for a sequence of hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response.
typedef struct hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__Sequence
{
  hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_MSGS__SRV__DETAIL__SET_MOTORS_CONTROL_LIMITS__STRUCT_H_
