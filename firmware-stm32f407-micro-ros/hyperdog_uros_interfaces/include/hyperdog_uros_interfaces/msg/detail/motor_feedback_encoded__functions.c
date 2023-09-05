// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hyperdog_uros_interfaces:msg/MotorFeedbackEncoded.idl
// generated code does not contain a copyright notice
#include "hyperdog_uros_interfaces/msg/detail/motor_feedback_encoded__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__init(hyperdog_uros_interfaces__msg__MotorFeedbackEncoded * msg)
{
  if (!msg) {
    return false;
  }
  // data
  return true;
}

void
hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__fini(hyperdog_uros_interfaces__msg__MotorFeedbackEncoded * msg)
{
  if (!msg) {
    return;
  }
  // data
}

bool
hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__are_equal(const hyperdog_uros_interfaces__msg__MotorFeedbackEncoded * lhs, const hyperdog_uros_interfaces__msg__MotorFeedbackEncoded * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // data
  for (size_t i = 0; i < 6; ++i) {
    if (lhs->data[i] != rhs->data[i]) {
      return false;
    }
  }
  return true;
}

bool
hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__copy(
  const hyperdog_uros_interfaces__msg__MotorFeedbackEncoded * input,
  hyperdog_uros_interfaces__msg__MotorFeedbackEncoded * output)
{
  if (!input || !output) {
    return false;
  }
  // data
  for (size_t i = 0; i < 6; ++i) {
    output->data[i] = input->data[i];
  }
  return true;
}

hyperdog_uros_interfaces__msg__MotorFeedbackEncoded *
hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_interfaces__msg__MotorFeedbackEncoded * msg = (hyperdog_uros_interfaces__msg__MotorFeedbackEncoded *)allocator.allocate(sizeof(hyperdog_uros_interfaces__msg__MotorFeedbackEncoded), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hyperdog_uros_interfaces__msg__MotorFeedbackEncoded));
  bool success = hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__destroy(hyperdog_uros_interfaces__msg__MotorFeedbackEncoded * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__Sequence__init(hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_interfaces__msg__MotorFeedbackEncoded * data = NULL;

  if (size) {
    data = (hyperdog_uros_interfaces__msg__MotorFeedbackEncoded *)allocator.zero_allocate(size, sizeof(hyperdog_uros_interfaces__msg__MotorFeedbackEncoded), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__fini(&data[i - 1]);
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
hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__Sequence__fini(hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__Sequence * array)
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
      hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__fini(&array->data[i]);
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

hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__Sequence *
hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__Sequence * array = (hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__Sequence *)allocator.allocate(sizeof(hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__Sequence__destroy(hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__Sequence__are_equal(const hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__Sequence * lhs, const hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__Sequence__copy(
  const hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__Sequence * input,
  hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hyperdog_uros_interfaces__msg__MotorFeedbackEncoded);
    hyperdog_uros_interfaces__msg__MotorFeedbackEncoded * data =
      (hyperdog_uros_interfaces__msg__MotorFeedbackEncoded *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__fini(&data[i]);
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
    if (!hyperdog_uros_interfaces__msg__MotorFeedbackEncoded__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
