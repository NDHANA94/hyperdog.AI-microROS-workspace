// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hyperdog_uros_msgs:msg/MotorParams.idl
// generated code does not contain a copyright notice
#include "hyperdog_uros_msgs/msg/detail/motor_params__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `position`
// Member `velocity`
// Member `kp`
// Member `kd`
// Member `i_ff`
#include "hyperdog_uros_msgs/msg/detail/limit__functions.h"

bool
hyperdog_uros_msgs__msg__MotorParams__init(hyperdog_uros_msgs__msg__MotorParams * msg)
{
  if (!msg) {
    return false;
  }
  // can_id
  // position
  if (!hyperdog_uros_msgs__msg__Limit__init(&msg->position)) {
    hyperdog_uros_msgs__msg__MotorParams__fini(msg);
    return false;
  }
  // velocity
  if (!hyperdog_uros_msgs__msg__Limit__init(&msg->velocity)) {
    hyperdog_uros_msgs__msg__MotorParams__fini(msg);
    return false;
  }
  // kp
  if (!hyperdog_uros_msgs__msg__Limit__init(&msg->kp)) {
    hyperdog_uros_msgs__msg__MotorParams__fini(msg);
    return false;
  }
  // kd
  if (!hyperdog_uros_msgs__msg__Limit__init(&msg->kd)) {
    hyperdog_uros_msgs__msg__MotorParams__fini(msg);
    return false;
  }
  // i_ff
  if (!hyperdog_uros_msgs__msg__Limit__init(&msg->i_ff)) {
    hyperdog_uros_msgs__msg__MotorParams__fini(msg);
    return false;
  }
  return true;
}

void
hyperdog_uros_msgs__msg__MotorParams__fini(hyperdog_uros_msgs__msg__MotorParams * msg)
{
  if (!msg) {
    return;
  }
  // can_id
  // position
  hyperdog_uros_msgs__msg__Limit__fini(&msg->position);
  // velocity
  hyperdog_uros_msgs__msg__Limit__fini(&msg->velocity);
  // kp
  hyperdog_uros_msgs__msg__Limit__fini(&msg->kp);
  // kd
  hyperdog_uros_msgs__msg__Limit__fini(&msg->kd);
  // i_ff
  hyperdog_uros_msgs__msg__Limit__fini(&msg->i_ff);
}

bool
hyperdog_uros_msgs__msg__MotorParams__are_equal(const hyperdog_uros_msgs__msg__MotorParams * lhs, const hyperdog_uros_msgs__msg__MotorParams * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // can_id
  if (lhs->can_id != rhs->can_id) {
    return false;
  }
  // position
  if (!hyperdog_uros_msgs__msg__Limit__are_equal(
      &(lhs->position), &(rhs->position)))
  {
    return false;
  }
  // velocity
  if (!hyperdog_uros_msgs__msg__Limit__are_equal(
      &(lhs->velocity), &(rhs->velocity)))
  {
    return false;
  }
  // kp
  if (!hyperdog_uros_msgs__msg__Limit__are_equal(
      &(lhs->kp), &(rhs->kp)))
  {
    return false;
  }
  // kd
  if (!hyperdog_uros_msgs__msg__Limit__are_equal(
      &(lhs->kd), &(rhs->kd)))
  {
    return false;
  }
  // i_ff
  if (!hyperdog_uros_msgs__msg__Limit__are_equal(
      &(lhs->i_ff), &(rhs->i_ff)))
  {
    return false;
  }
  return true;
}

bool
hyperdog_uros_msgs__msg__MotorParams__copy(
  const hyperdog_uros_msgs__msg__MotorParams * input,
  hyperdog_uros_msgs__msg__MotorParams * output)
{
  if (!input || !output) {
    return false;
  }
  // can_id
  output->can_id = input->can_id;
  // position
  if (!hyperdog_uros_msgs__msg__Limit__copy(
      &(input->position), &(output->position)))
  {
    return false;
  }
  // velocity
  if (!hyperdog_uros_msgs__msg__Limit__copy(
      &(input->velocity), &(output->velocity)))
  {
    return false;
  }
  // kp
  if (!hyperdog_uros_msgs__msg__Limit__copy(
      &(input->kp), &(output->kp)))
  {
    return false;
  }
  // kd
  if (!hyperdog_uros_msgs__msg__Limit__copy(
      &(input->kd), &(output->kd)))
  {
    return false;
  }
  // i_ff
  if (!hyperdog_uros_msgs__msg__Limit__copy(
      &(input->i_ff), &(output->i_ff)))
  {
    return false;
  }
  return true;
}

hyperdog_uros_msgs__msg__MotorParams *
hyperdog_uros_msgs__msg__MotorParams__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_msgs__msg__MotorParams * msg = (hyperdog_uros_msgs__msg__MotorParams *)allocator.allocate(sizeof(hyperdog_uros_msgs__msg__MotorParams), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hyperdog_uros_msgs__msg__MotorParams));
  bool success = hyperdog_uros_msgs__msg__MotorParams__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hyperdog_uros_msgs__msg__MotorParams__destroy(hyperdog_uros_msgs__msg__MotorParams * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hyperdog_uros_msgs__msg__MotorParams__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hyperdog_uros_msgs__msg__MotorParams__Sequence__init(hyperdog_uros_msgs__msg__MotorParams__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_msgs__msg__MotorParams * data = NULL;

  if (size) {
    data = (hyperdog_uros_msgs__msg__MotorParams *)allocator.zero_allocate(size, sizeof(hyperdog_uros_msgs__msg__MotorParams), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hyperdog_uros_msgs__msg__MotorParams__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hyperdog_uros_msgs__msg__MotorParams__fini(&data[i - 1]);
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
hyperdog_uros_msgs__msg__MotorParams__Sequence__fini(hyperdog_uros_msgs__msg__MotorParams__Sequence * array)
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
      hyperdog_uros_msgs__msg__MotorParams__fini(&array->data[i]);
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

hyperdog_uros_msgs__msg__MotorParams__Sequence *
hyperdog_uros_msgs__msg__MotorParams__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_msgs__msg__MotorParams__Sequence * array = (hyperdog_uros_msgs__msg__MotorParams__Sequence *)allocator.allocate(sizeof(hyperdog_uros_msgs__msg__MotorParams__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hyperdog_uros_msgs__msg__MotorParams__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hyperdog_uros_msgs__msg__MotorParams__Sequence__destroy(hyperdog_uros_msgs__msg__MotorParams__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hyperdog_uros_msgs__msg__MotorParams__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hyperdog_uros_msgs__msg__MotorParams__Sequence__are_equal(const hyperdog_uros_msgs__msg__MotorParams__Sequence * lhs, const hyperdog_uros_msgs__msg__MotorParams__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hyperdog_uros_msgs__msg__MotorParams__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hyperdog_uros_msgs__msg__MotorParams__Sequence__copy(
  const hyperdog_uros_msgs__msg__MotorParams__Sequence * input,
  hyperdog_uros_msgs__msg__MotorParams__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hyperdog_uros_msgs__msg__MotorParams);
    hyperdog_uros_msgs__msg__MotorParams * data =
      (hyperdog_uros_msgs__msg__MotorParams *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hyperdog_uros_msgs__msg__MotorParams__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          hyperdog_uros_msgs__msg__MotorParams__fini(&data[i]);
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
    if (!hyperdog_uros_msgs__msg__MotorParams__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
