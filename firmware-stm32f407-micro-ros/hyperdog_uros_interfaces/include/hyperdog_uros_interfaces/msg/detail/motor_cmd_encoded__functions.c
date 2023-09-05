// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hyperdog_uros_interfaces:msg/MotorCmdEncoded.idl
// generated code does not contain a copyright notice
#include "hyperdog_uros_interfaces/msg/detail/motor_cmd_encoded__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
hyperdog_uros_interfaces__msg__MotorCmdEncoded__init(hyperdog_uros_interfaces__msg__MotorCmdEncoded * msg)
{
  if (!msg) {
    return false;
  }
  // can_id
  // enable
  // disable
  // set_zero
  // cmd
  return true;
}

void
hyperdog_uros_interfaces__msg__MotorCmdEncoded__fini(hyperdog_uros_interfaces__msg__MotorCmdEncoded * msg)
{
  if (!msg) {
    return;
  }
  // can_id
  // enable
  // disable
  // set_zero
  // cmd
}

bool
hyperdog_uros_interfaces__msg__MotorCmdEncoded__are_equal(const hyperdog_uros_interfaces__msg__MotorCmdEncoded * lhs, const hyperdog_uros_interfaces__msg__MotorCmdEncoded * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // can_id
  if (lhs->can_id != rhs->can_id) {
    return false;
  }
  // enable
  if (lhs->enable != rhs->enable) {
    return false;
  }
  // disable
  if (lhs->disable != rhs->disable) {
    return false;
  }
  // set_zero
  if (lhs->set_zero != rhs->set_zero) {
    return false;
  }
  // cmd
  for (size_t i = 0; i < 8; ++i) {
    if (lhs->cmd[i] != rhs->cmd[i]) {
      return false;
    }
  }
  return true;
}

bool
hyperdog_uros_interfaces__msg__MotorCmdEncoded__copy(
  const hyperdog_uros_interfaces__msg__MotorCmdEncoded * input,
  hyperdog_uros_interfaces__msg__MotorCmdEncoded * output)
{
  if (!input || !output) {
    return false;
  }
  // can_id
  output->can_id = input->can_id;
  // enable
  output->enable = input->enable;
  // disable
  output->disable = input->disable;
  // set_zero
  output->set_zero = input->set_zero;
  // cmd
  for (size_t i = 0; i < 8; ++i) {
    output->cmd[i] = input->cmd[i];
  }
  return true;
}

hyperdog_uros_interfaces__msg__MotorCmdEncoded *
hyperdog_uros_interfaces__msg__MotorCmdEncoded__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_interfaces__msg__MotorCmdEncoded * msg = (hyperdog_uros_interfaces__msg__MotorCmdEncoded *)allocator.allocate(sizeof(hyperdog_uros_interfaces__msg__MotorCmdEncoded), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hyperdog_uros_interfaces__msg__MotorCmdEncoded));
  bool success = hyperdog_uros_interfaces__msg__MotorCmdEncoded__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hyperdog_uros_interfaces__msg__MotorCmdEncoded__destroy(hyperdog_uros_interfaces__msg__MotorCmdEncoded * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hyperdog_uros_interfaces__msg__MotorCmdEncoded__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hyperdog_uros_interfaces__msg__MotorCmdEncoded__Sequence__init(hyperdog_uros_interfaces__msg__MotorCmdEncoded__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_interfaces__msg__MotorCmdEncoded * data = NULL;

  if (size) {
    data = (hyperdog_uros_interfaces__msg__MotorCmdEncoded *)allocator.zero_allocate(size, sizeof(hyperdog_uros_interfaces__msg__MotorCmdEncoded), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hyperdog_uros_interfaces__msg__MotorCmdEncoded__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hyperdog_uros_interfaces__msg__MotorCmdEncoded__fini(&data[i - 1]);
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
hyperdog_uros_interfaces__msg__MotorCmdEncoded__Sequence__fini(hyperdog_uros_interfaces__msg__MotorCmdEncoded__Sequence * array)
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
      hyperdog_uros_interfaces__msg__MotorCmdEncoded__fini(&array->data[i]);
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

hyperdog_uros_interfaces__msg__MotorCmdEncoded__Sequence *
hyperdog_uros_interfaces__msg__MotorCmdEncoded__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_interfaces__msg__MotorCmdEncoded__Sequence * array = (hyperdog_uros_interfaces__msg__MotorCmdEncoded__Sequence *)allocator.allocate(sizeof(hyperdog_uros_interfaces__msg__MotorCmdEncoded__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hyperdog_uros_interfaces__msg__MotorCmdEncoded__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hyperdog_uros_interfaces__msg__MotorCmdEncoded__Sequence__destroy(hyperdog_uros_interfaces__msg__MotorCmdEncoded__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hyperdog_uros_interfaces__msg__MotorCmdEncoded__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hyperdog_uros_interfaces__msg__MotorCmdEncoded__Sequence__are_equal(const hyperdog_uros_interfaces__msg__MotorCmdEncoded__Sequence * lhs, const hyperdog_uros_interfaces__msg__MotorCmdEncoded__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hyperdog_uros_interfaces__msg__MotorCmdEncoded__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hyperdog_uros_interfaces__msg__MotorCmdEncoded__Sequence__copy(
  const hyperdog_uros_interfaces__msg__MotorCmdEncoded__Sequence * input,
  hyperdog_uros_interfaces__msg__MotorCmdEncoded__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hyperdog_uros_interfaces__msg__MotorCmdEncoded);
    hyperdog_uros_interfaces__msg__MotorCmdEncoded * data =
      (hyperdog_uros_interfaces__msg__MotorCmdEncoded *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hyperdog_uros_interfaces__msg__MotorCmdEncoded__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          hyperdog_uros_interfaces__msg__MotorCmdEncoded__fini(&data[i]);
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
    if (!hyperdog_uros_interfaces__msg__MotorCmdEncoded__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
