// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hyperdog_uros_interfaces:msg/Limit.idl
// generated code does not contain a copyright notice
#include "hyperdog_uros_interfaces/msg/detail/limit__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
hyperdog_uros_interfaces__msg__Limit__init(hyperdog_uros_interfaces__msg__Limit * msg)
{
  if (!msg) {
    return false;
  }
  // min
  // max
  return true;
}

void
hyperdog_uros_interfaces__msg__Limit__fini(hyperdog_uros_interfaces__msg__Limit * msg)
{
  if (!msg) {
    return;
  }
  // min
  // max
}

bool
hyperdog_uros_interfaces__msg__Limit__are_equal(const hyperdog_uros_interfaces__msg__Limit * lhs, const hyperdog_uros_interfaces__msg__Limit * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // min
  if (lhs->min != rhs->min) {
    return false;
  }
  // max
  if (lhs->max != rhs->max) {
    return false;
  }
  return true;
}

bool
hyperdog_uros_interfaces__msg__Limit__copy(
  const hyperdog_uros_interfaces__msg__Limit * input,
  hyperdog_uros_interfaces__msg__Limit * output)
{
  if (!input || !output) {
    return false;
  }
  // min
  output->min = input->min;
  // max
  output->max = input->max;
  return true;
}

hyperdog_uros_interfaces__msg__Limit *
hyperdog_uros_interfaces__msg__Limit__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_interfaces__msg__Limit * msg = (hyperdog_uros_interfaces__msg__Limit *)allocator.allocate(sizeof(hyperdog_uros_interfaces__msg__Limit), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hyperdog_uros_interfaces__msg__Limit));
  bool success = hyperdog_uros_interfaces__msg__Limit__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hyperdog_uros_interfaces__msg__Limit__destroy(hyperdog_uros_interfaces__msg__Limit * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hyperdog_uros_interfaces__msg__Limit__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hyperdog_uros_interfaces__msg__Limit__Sequence__init(hyperdog_uros_interfaces__msg__Limit__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_interfaces__msg__Limit * data = NULL;

  if (size) {
    data = (hyperdog_uros_interfaces__msg__Limit *)allocator.zero_allocate(size, sizeof(hyperdog_uros_interfaces__msg__Limit), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hyperdog_uros_interfaces__msg__Limit__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hyperdog_uros_interfaces__msg__Limit__fini(&data[i - 1]);
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
hyperdog_uros_interfaces__msg__Limit__Sequence__fini(hyperdog_uros_interfaces__msg__Limit__Sequence * array)
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
      hyperdog_uros_interfaces__msg__Limit__fini(&array->data[i]);
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

hyperdog_uros_interfaces__msg__Limit__Sequence *
hyperdog_uros_interfaces__msg__Limit__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_interfaces__msg__Limit__Sequence * array = (hyperdog_uros_interfaces__msg__Limit__Sequence *)allocator.allocate(sizeof(hyperdog_uros_interfaces__msg__Limit__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hyperdog_uros_interfaces__msg__Limit__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hyperdog_uros_interfaces__msg__Limit__Sequence__destroy(hyperdog_uros_interfaces__msg__Limit__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hyperdog_uros_interfaces__msg__Limit__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hyperdog_uros_interfaces__msg__Limit__Sequence__are_equal(const hyperdog_uros_interfaces__msg__Limit__Sequence * lhs, const hyperdog_uros_interfaces__msg__Limit__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hyperdog_uros_interfaces__msg__Limit__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hyperdog_uros_interfaces__msg__Limit__Sequence__copy(
  const hyperdog_uros_interfaces__msg__Limit__Sequence * input,
  hyperdog_uros_interfaces__msg__Limit__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hyperdog_uros_interfaces__msg__Limit);
    hyperdog_uros_interfaces__msg__Limit * data =
      (hyperdog_uros_interfaces__msg__Limit *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hyperdog_uros_interfaces__msg__Limit__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          hyperdog_uros_interfaces__msg__Limit__fini(&data[i]);
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
    if (!hyperdog_uros_interfaces__msg__Limit__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
