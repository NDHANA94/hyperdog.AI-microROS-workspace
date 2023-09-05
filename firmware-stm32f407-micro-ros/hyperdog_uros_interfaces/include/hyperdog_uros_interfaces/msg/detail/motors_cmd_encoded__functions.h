// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from hyperdog_uros_interfaces:msg/MotorsCmdEncoded.idl
// generated code does not contain a copyright notice

#ifndef HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTORS_CMD_ENCODED__FUNCTIONS_H_
#define HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTORS_CMD_ENCODED__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "hyperdog_uros_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "hyperdog_uros_interfaces/msg/detail/motors_cmd_encoded__struct.h"

/// Initialize msg/MotorsCmdEncoded message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * hyperdog_uros_interfaces__msg__MotorsCmdEncoded
 * )) before or use
 * hyperdog_uros_interfaces__msg__MotorsCmdEncoded__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_hyperdog_uros_interfaces
bool
hyperdog_uros_interfaces__msg__MotorsCmdEncoded__init(hyperdog_uros_interfaces__msg__MotorsCmdEncoded * msg);

/// Finalize msg/MotorsCmdEncoded message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hyperdog_uros_interfaces
void
hyperdog_uros_interfaces__msg__MotorsCmdEncoded__fini(hyperdog_uros_interfaces__msg__MotorsCmdEncoded * msg);

/// Create msg/MotorsCmdEncoded message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * hyperdog_uros_interfaces__msg__MotorsCmdEncoded__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_hyperdog_uros_interfaces
hyperdog_uros_interfaces__msg__MotorsCmdEncoded *
hyperdog_uros_interfaces__msg__MotorsCmdEncoded__create();

/// Destroy msg/MotorsCmdEncoded message.
/**
 * It calls
 * hyperdog_uros_interfaces__msg__MotorsCmdEncoded__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hyperdog_uros_interfaces
void
hyperdog_uros_interfaces__msg__MotorsCmdEncoded__destroy(hyperdog_uros_interfaces__msg__MotorsCmdEncoded * msg);

/// Check for msg/MotorsCmdEncoded message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_hyperdog_uros_interfaces
bool
hyperdog_uros_interfaces__msg__MotorsCmdEncoded__are_equal(const hyperdog_uros_interfaces__msg__MotorsCmdEncoded * lhs, const hyperdog_uros_interfaces__msg__MotorsCmdEncoded * rhs);

/// Copy a msg/MotorsCmdEncoded message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_hyperdog_uros_interfaces
bool
hyperdog_uros_interfaces__msg__MotorsCmdEncoded__copy(
  const hyperdog_uros_interfaces__msg__MotorsCmdEncoded * input,
  hyperdog_uros_interfaces__msg__MotorsCmdEncoded * output);

/// Initialize array of msg/MotorsCmdEncoded messages.
/**
 * It allocates the memory for the number of elements and calls
 * hyperdog_uros_interfaces__msg__MotorsCmdEncoded__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_hyperdog_uros_interfaces
bool
hyperdog_uros_interfaces__msg__MotorsCmdEncoded__Sequence__init(hyperdog_uros_interfaces__msg__MotorsCmdEncoded__Sequence * array, size_t size);

/// Finalize array of msg/MotorsCmdEncoded messages.
/**
 * It calls
 * hyperdog_uros_interfaces__msg__MotorsCmdEncoded__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hyperdog_uros_interfaces
void
hyperdog_uros_interfaces__msg__MotorsCmdEncoded__Sequence__fini(hyperdog_uros_interfaces__msg__MotorsCmdEncoded__Sequence * array);

/// Create array of msg/MotorsCmdEncoded messages.
/**
 * It allocates the memory for the array and calls
 * hyperdog_uros_interfaces__msg__MotorsCmdEncoded__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_hyperdog_uros_interfaces
hyperdog_uros_interfaces__msg__MotorsCmdEncoded__Sequence *
hyperdog_uros_interfaces__msg__MotorsCmdEncoded__Sequence__create(size_t size);

/// Destroy array of msg/MotorsCmdEncoded messages.
/**
 * It calls
 * hyperdog_uros_interfaces__msg__MotorsCmdEncoded__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hyperdog_uros_interfaces
void
hyperdog_uros_interfaces__msg__MotorsCmdEncoded__Sequence__destroy(hyperdog_uros_interfaces__msg__MotorsCmdEncoded__Sequence * array);

/// Check for msg/MotorsCmdEncoded message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_hyperdog_uros_interfaces
bool
hyperdog_uros_interfaces__msg__MotorsCmdEncoded__Sequence__are_equal(const hyperdog_uros_interfaces__msg__MotorsCmdEncoded__Sequence * lhs, const hyperdog_uros_interfaces__msg__MotorsCmdEncoded__Sequence * rhs);

/// Copy an array of msg/MotorsCmdEncoded messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_hyperdog_uros_interfaces
bool
hyperdog_uros_interfaces__msg__MotorsCmdEncoded__Sequence__copy(
  const hyperdog_uros_interfaces__msg__MotorsCmdEncoded__Sequence * input,
  hyperdog_uros_interfaces__msg__MotorsCmdEncoded__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // HYPERDOG_UROS_INTERFACES__MSG__DETAIL__MOTORS_CMD_ENCODED__FUNCTIONS_H_
