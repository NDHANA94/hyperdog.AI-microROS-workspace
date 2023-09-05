// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_interfaces:msg/MotorsCmdEncoded.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTORS_CMD_ENCODED__STRUCT_H_
#define HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTORS_CMD_ENCODED__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'fr_hip_roll'
// Member 'fr_hip_pitch'
// Member 'fr_knee'
// Member 'fl_hip_roll'
// Member 'fl_hip_pitch'
// Member 'fl_knee'
// Member 'rr_hip_roll'
// Member 'rr_hip_pitch'
// Member 'rr_knee'
// Member 'rl_hip_roll'
// Member 'rl_hip_pitch'
// Member 'rl_knee'
#include "hyperdog_uros_interfaces/msg/detail/motor_cmd_encoded__struct.h"

// Struct defined in msg/MotorsCmdEncoded in the package hyperdog_uros_interfaces.
typedef struct hyperdog_uros_interfaces__msg__MotorsCmdEncoded
{
  hyperdog_uros_interfaces__msg__MotorCmdEncoded fr_hip_roll;
  hyperdog_uros_interfaces__msg__MotorCmdEncoded fr_hip_pitch;
  hyperdog_uros_interfaces__msg__MotorCmdEncoded fr_knee;
  hyperdog_uros_interfaces__msg__MotorCmdEncoded fl_hip_roll;
  hyperdog_uros_interfaces__msg__MotorCmdEncoded fl_hip_pitch;
  hyperdog_uros_interfaces__msg__MotorCmdEncoded fl_knee;
  hyperdog_uros_interfaces__msg__MotorCmdEncoded rr_hip_roll;
  hyperdog_uros_interfaces__msg__MotorCmdEncoded rr_hip_pitch;
  hyperdog_uros_interfaces__msg__MotorCmdEncoded rr_knee;
  hyperdog_uros_interfaces__msg__MotorCmdEncoded rl_hip_roll;
  hyperdog_uros_interfaces__msg__MotorCmdEncoded rl_hip_pitch;
  hyperdog_uros_interfaces__msg__MotorCmdEncoded rl_knee;
} hyperdog_uros_interfaces__msg__MotorsCmdEncoded;

// Struct for a sequence of hyperdog_uros_interfaces__msg__MotorsCmdEncoded.
typedef struct hyperdog_uros_interfaces__msg__MotorsCmdEncoded__Sequence
{
  hyperdog_uros_interfaces__msg__MotorsCmdEncoded * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_interfaces__msg__MotorsCmdEncoded__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTORS_CMD_ENCODED__STRUCT_H_
