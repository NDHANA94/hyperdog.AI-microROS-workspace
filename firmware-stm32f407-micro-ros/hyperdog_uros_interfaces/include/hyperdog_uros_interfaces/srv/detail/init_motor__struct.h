// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hyperdog_uros_interfaces:srv/InitMotor.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_INTERFACES__SRV__DETAIL__INIT_MOTOR__STRUCT_H_
#define HYPERDOG_UROS_INTERFACES__SRV__DETAIL__INIT_MOTOR__STRUCT_H_

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
#include "hyperdog_uros_interfaces/msg/detail/init_motor__struct.h"

// Struct defined in srv/InitMotor in the package hyperdog_uros_interfaces.
typedef struct hyperdog_uros_interfaces__srv__InitMotor_Request
{
  hyperdog_uros_interfaces__msg__InitMotor data;
} hyperdog_uros_interfaces__srv__InitMotor_Request;

// Struct for a sequence of hyperdog_uros_interfaces__srv__InitMotor_Request.
typedef struct hyperdog_uros_interfaces__srv__InitMotor_Request__Sequence
{
  hyperdog_uros_interfaces__srv__InitMotor_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_interfaces__srv__InitMotor_Request__Sequence;


// Constants defined in the message

// Struct defined in srv/InitMotor in the package hyperdog_uros_interfaces.
typedef struct hyperdog_uros_interfaces__srv__InitMotor_Response
{
  int16_t error_code[12];
  int8_t init_status_code[12];
} hyperdog_uros_interfaces__srv__InitMotor_Response;

// Struct for a sequence of hyperdog_uros_interfaces__srv__InitMotor_Response.
typedef struct hyperdog_uros_interfaces__srv__InitMotor_Response__Sequence
{
  hyperdog_uros_interfaces__srv__InitMotor_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hyperdog_uros_interfaces__srv__InitMotor_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_INTERFACES__SRV__DETAIL__INIT_MOTOR__STRUCT_H_
