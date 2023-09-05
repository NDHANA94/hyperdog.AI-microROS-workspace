// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hyperdog_uros_interfaces:msg/MotorStatesEncoded.idl
// generated code does not contain a copyright notice
#include "hyperdog_uros_interfaces/msg/detail/motor_states_encoded__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `status_msg`
#include "rosidl_runtime_c/string_functions.h"
// Member `feedback`
#include "hyperdog_uros_interfaces/msg/detail/motor_feedback_encoded__functions.h"

bool
hyperdog_uros_interfaces__msg__MotorStatesEncoded__init(hyperdog_uros_interfaces__msg__MotorStatesEncoded * msg)
{
  if (!msg) {
    return false;
  }
  // is_available
  // is_enabled
  // is_error
  // error_code
  // status_msg
  if (!rosidl_runtime_c__String__init(&msg->status_msg)) {
    hyperdog_uros_interfaces__msg__MotorStatesEncoded__fini(msg);
    return false;
  }
  // feedback
  if (!hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__init(&msg->feedback)) {
    hyperdog_uros_interfaces__msg__MotorStatesEncoded__fini(msg);
    return false;
  }
  return true;
}

void
hyperdog_uros_interfaces__msg__MotorStatesEncoded__fini(hyperdog_uros_interfaces__msg__MotorStatesEncoded * msg)
{
  if (!msg) {
    return;
  }
  // is_available
  // is_enabled
  // is_error
  // error_code
  // status_msg
  rosidl_runtime_c__String__fini(&msg->status_msg);
  // feedback
  hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__fini(&msg->feedback);
}

bool
hyperdog_uros_interfaces__msg__MotorStatesEncoded__are_equal(const hyperdog_uros_interfaces__msg__MotorStatesEncoded * lhs, const hyperdog_uros_interfaces__msg__MotorStatesEncoded * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // is_available
  if (lhs->is_available != rhs->is_available) {
    return false;
  }
  // is_enabled
  if (lhs->is_enabled != rhs->is_enabled) {
    return false;
  }
  // is_error
  if (lhs->is_error != rhs->is_error) {
    return false;
  }
  // error_code
  if (lhs->error_code != rhs->error_code) {
    return false;
  }
  // status_msg
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->status_msg), &(rhs->status_msg)))
  {
    return false;
  }
  // feedback
  if (!hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__are_equal(
      &(lhs->feedback), &(rhs->feedback)))
  {
    return false;
  }
  return true;
}

bool
hyperdog_uros_interfaces__msg__MotorStatesEncoded__copy(
  const hyperdog_uros_interfaces__msg__MotorStatesEncoded * input,
  hyperdog_uros_interfaces__msg__MotorStatesEncoded * output)
{
  if (!input || !output) {
    return false;
  }
  // is_available
  output->is_available = input->is_available;
  // is_enabled
  output->is_enabled = input->is_enabled;
  // is_error
  output->is_error = input->is_error;
  // error_code
  output->error_code = input->error_code;
  // status_msg
  if (!rosidl_runtime_c__String__copy(
      &(input->status_msg), &(output->status_msg)))
  {
    return false;
  }
  // feedback
  if (!hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__copy(
      &(input->feedback), &(output->feedback)))
  {
    return false;
  }
  return true;
}

hyperdog_uros_interfaces__msg__MotorStatesEncoded *
hyperdog_uros_interfaces__msg__MotorStatesEncoded__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_interfaces__msg__MotorStatesEncoded * msg = (hyperdog_uros_interfaces__msg__MotorStatesEncoded *)allocator.allocate(sizeof(hyperdog_uros_interfaces__msg__MotorStatesEncoded), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hyperdog_uros_interfaces__msg__MotorStatesEncoded));
  bool success = hyperdog_uros_interfaces__msg__MotorStatesEncoded__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hyperdog_uros_interfaces__msg__MotorStatesEncoded__destroy(hyperdog_uros_interfaces__msg__MotorStatesEncoded * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hyperdog_uros_interfaces__msg__MotorStatesEncoded__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hyperdog_uros_interfaces__msg__MotorStatesEncoded__Sequence__init(hyperdog_uros_interfaces__msg__MotorStatesEncoded__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_interfaces__msg__MotorStatesEncoded * data = NULL;

  if (size) {
    data = (hyperdog_uros_interfaces__msg__MotorStatesEncoded *)allocator.zero_allocate(size, sizeof(hyperdog_uros_interfaces__msg__MotorStatesEncoded), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hyperdog_uros_interfaces__msg__MotorStatesEncoded__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hyperdog_uros_interfaces__msg__MotorStatesEncoded__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
hyperdog_uros_interfaces__msg__MotorStatesEncoded__Sequence__fini(hyperdog_uros_interfaces__msg__MotorStatesEncoded__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      hyperdog_uros_interfaces__msg__MotorStatesEncoded__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

hyperdog_uros_interfaces__msg__MotorStatesEncoded__Sequence *
hyperdog_uros_interfaces__msg__MotorStatesEncoded__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_interfaces__msg__MotorStatesEncoded__Sequence * array = (hyperdog_uros_interfaces__msg__MotorStatesEncoded__Sequence *)allocator.allocate(sizeof(hyperdog_uros_interfaces__msg__MotorStatesEncoded__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hyperdog_uros_interfaces__msg__MotorStatesEncoded__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hyperdog_uros_interfaces__msg__MotorStatesEncoded__Sequence__destroy(hyperdog_uros_interfaces__msg__MotorStatesEncoded__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hyperdog_uros_interfaces__msg__MotorStatesEncoded__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hyperdog_uros_interfaces__msg__MotorStatesEncoded__Sequence__are_equal(const hyperdog_uros_interfaces__msg__MotorStatesEncoded__Sequence * lhs, const hyperdog_uros_interfaces__msg__MotorStatesEncoded__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hyperdog_uros_interfaces__msg__MotorStatesEncoded__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hyperdog_uros_interfaces__msg__MotorStatesEncoded__Sequence__copy(
  const hyperdog_uros_interfaces__msg__MotorStatesEncoded__Sequence * input,
  hyperdog_uros_interfaces__msg__MotorStatesEncoded__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hyperdog_uros_interfaces__msg__MotorStatesEncoded);
    hyperdog_uros_interfaces__msg__MotorStatesEncoded * data =
      (hyperdog_uros_interfaces__msg__MotorStatesEncoded *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hyperdog_uros_interfaces__msg__MotorStatesEncoded__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          hyperdog_uros_interfaces__msg__MotorStatesEncoded__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!hyperdog_uros_interfaces__msg__MotorStatesEncoded__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
