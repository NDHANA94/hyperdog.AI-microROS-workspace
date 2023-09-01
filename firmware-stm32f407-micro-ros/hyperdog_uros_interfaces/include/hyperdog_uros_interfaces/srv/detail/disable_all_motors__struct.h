// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_interfaces:srv/DisableAllMotors.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_INTERFACES__SRV__DETAIL__DISABLE_ALL_MOTORS__STRUCT_H_
#define HYPERDOG_UROS_INTERFACES__SRV__DETAIL__DISABLE_ALL_MOTORS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in srv/DisableAllMotors in the package hyperdog_uros_interfaces.
typedef struct hyperdog_uros_interfaces__srv__DisableAllMotors_Request
{
  uint8_t structure_needs_at_least_one_member;
} hyperdog_uros_interfaces__srv__DisableAllMotors_Request;

// Struct for a sequence of hyperdog_uros_interfaces__srv__DisableAllMotors_Request.
typedef struct hyperdog_uros_interfaces__srv__DisableAllMotors_Request__Sequence
{
  hyperdog_uros_interfaces__srv__DisableAllMotors_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_interfaces__srv__DisableAllMotors_Request__Sequence;


// Constants defined in the message

// Struct defined in srv/DisableAllMotors in the package hyperdog_uros_interfaces.
typedef struct hyperdog_uros_interfaces__srv__DisableAllMotors_Response
{
  int16_t error_code[12];
} hyperdog_uros_interfaces__srv__DisableAllMotors_Response;

// Struct for a sequence of hyperdog_uros_interfaces__srv__DisableAllMotors_Response.
typedef struct hyperdog_uros_interfaces__srv__DisableAllMotors_Response__Sequence
{
  hyperdog_uros_interfaces__srv__DisableAllMotors_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_interfaces__srv__DisableAllMotors_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_INTERFACES__SRV__DETAIL__DISABLE_ALL_MOTORS__STRUCT_H_
