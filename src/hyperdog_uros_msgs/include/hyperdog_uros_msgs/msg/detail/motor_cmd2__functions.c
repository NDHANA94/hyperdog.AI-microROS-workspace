// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hyperdog_uros_msgs:msg/MotorCmd2.idl
// generated code does not contain a copyright notice
#include "hyperdog_uros_msgs/msg/detail/motor_cmd2__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
hyperdog_uros_msgs__msg__MotorCmd2__init(hyperdog_uros_msgs__msg__MotorCmd2 * msg)
{
  if (!msg) {
    return false;
  }
  // can_id
  // enable
  // disable
  // set_zero
  // desire_position
  // desire_velocity
  // kp
  // kd
  // i_ff
  return true;
}

void
hyperdog_uros_msgs__msg__MotorCmd2__fini(hyperdog_uros_msgs__msg__MotorCmd2 * msg)
{
  if (!msg) {
    return;
  }
  // can_id
  // enable
  // disable
  // set_zero
  // desire_position
  // desire_velocity
  // kp
  // kd
  // i_ff
}

bool
hyperdog_uros_msgs__msg__MotorCmd2__are_equal(const hyperdog_uros_msgs__msg__MotorCmd2 * lhs, const hyperdog_uros_msgs__msg__MotorCmd2 * rhs)
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
  // desire_position
  if (lhs->desire_position != rhs->desire_position) {
    return false;
  }
  // desire_velocity
  if (lhs->desire_velocity != rhs->desire_velocity) {
    return false;
  }
  // kp
  if (lhs->kp != rhs->kp) {
    return false;
  }
  // kd
  if (lhs->kd != rhs->kd) {
    return false;
  }
  // i_ff
  if (lhs->i_ff != rhs->i_ff) {
    return false;
  }
  return true;
}

bool
hyperdog_uros_msgs__msg__MotorCmd2__copy(
  const hyperdog_uros_msgs__msg__MotorCmd2 * input,
  hyperdog_uros_msgs__msg__MotorCmd2 * output)
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
  // desire_position
  output->desire_position = input->desire_position;
  // desire_velocity
  output->desire_velocity = input->desire_velocity;
  // kp
  output->kp = input->kp;
  // kd
  output->kd = input->kd;
  // i_ff
  output->i_ff = input->i_ff;
  return true;
}

hyperdog_uros_msgs__msg__MotorCmd2 *
hyperdog_uros_msgs__msg__MotorCmd2__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_msgs__msg__MotorCmd2 * msg = (hyperdog_uros_msgs__msg__MotorCmd2 *)allocator.allocate(sizeof(hyperdog_uros_msgs__msg__MotorCmd2), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hyperdog_uros_msgs__msg__MotorCmd2));
  bool success = hyperdog_uros_msgs__msg__MotorCmd2__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hyperdog_uros_msgs__msg__MotorCmd2__destroy(hyperdog_uros_msgs__msg__MotorCmd2 * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hyperdog_uros_msgs__msg__MotorCmd2__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hyperdog_uros_msgs__msg__MotorCmd2__Sequence__init(hyperdog_uros_msgs__msg__MotorCmd2__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_msgs__msg__MotorCmd2 * data = NULL;

  if (size) {
    data = (hyperdog_uros_msgs__msg__MotorCmd2 *)allocator.zero_allocate(size, sizeof(hyperdog_uros_msgs__msg__MotorCmd2), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hyperdog_uros_msgs__msg__MotorCmd2__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hyperdog_uros_msgs__msg__MotorCmd2__fini(&data[i - 1]);
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
hyperdog_uros_msgs__msg__MotorCmd2__Sequence__fini(hyperdog_uros_msgs__msg__MotorCmd2__Sequence * array)
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
      hyperdog_uros_msgs__msg__MotorCmd2__fini(&array->data[i]);
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

hyperdog_uros_msgs__msg__MotorCmd2__Sequence *
hyperdog_uros_msgs__msg__MotorCmd2__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_msgs__msg__MotorCmd2__Sequence * array = (hyperdog_uros_msgs__msg__MotorCmd2__Sequence *)allocator.allocate(sizeof(hyperdog_uros_msgs__msg__MotorCmd2__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hyperdog_uros_msgs__msg__MotorCmd2__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hyperdog_uros_msgs__msg__MotorCmd2__Sequence__destroy(hyperdog_uros_msgs__msg__MotorCmd2__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hyperdog_uros_msgs__msg__MotorCmd2__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hyperdog_uros_msgs__msg__MotorCmd2__Sequence__are_equal(const hyperdog_uros_msgs__msg__MotorCmd2__Sequence * lhs, const hyperdog_uros_msgs__msg__MotorCmd2__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hyperdog_uros_msgs__msg__MotorCmd2__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hyperdog_uros_msgs__msg__MotorCmd2__Sequence__copy(
  const hyperdog_uros_msgs__msg__MotorCmd2__Sequence * input,
  hyperdog_uros_msgs__msg__MotorCmd2__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hyperdog_uros_msgs__msg__MotorCmd2);
    hyperdog_uros_msgs__msg__MotorCmd2 * data =
      (hyperdog_uros_msgs__msg__MotorCmd2 *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hyperdog_uros_msgs__msg__MotorCmd2__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          hyperdog_uros_msgs__msg__MotorCmd2__fini(&data[i]);
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
    if (!hyperdog_uros_msgs__msg__MotorCmd2__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
