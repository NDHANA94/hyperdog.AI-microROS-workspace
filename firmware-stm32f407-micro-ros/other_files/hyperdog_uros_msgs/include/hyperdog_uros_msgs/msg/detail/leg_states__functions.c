// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hyperdog_uros_msgs:msg/LegStates.idl
// generated code does not contain a copyright notice
#include "hyperdog_uros_msgs/msg/detail/leg_states__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `leg_id`
#include "rosidl_runtime_c/string_functions.h"
// Member `position`
// Member `velocity`
// Member `applied_force`
// Member `reaction_force`
#include "hyperdog_uros_msgs/msg/detail/vector3__functions.h"

bool
hyperdog_uros_msgs__msg__LegStates__init(hyperdog_uros_msgs__msg__LegStates * msg)
{
  if (!msg) {
    return false;
  }
  // leg_id
  if (!rosidl_runtime_c__String__init(&msg->leg_id)) {
    hyperdog_uros_msgs__msg__LegStates__fini(msg);
    return false;
  }
  // is_contacted
  // position
  if (!hyperdog_uros_msgs__msg__Vector3__init(&msg->position)) {
    hyperdog_uros_msgs__msg__LegStates__fini(msg);
    return false;
  }
  // velocity
  if (!hyperdog_uros_msgs__msg__Vector3__init(&msg->velocity)) {
    hyperdog_uros_msgs__msg__LegStates__fini(msg);
    return false;
  }
  // applied_force
  if (!hyperdog_uros_msgs__msg__Vector3__init(&msg->applied_force)) {
    hyperdog_uros_msgs__msg__LegStates__fini(msg);
    return false;
  }
  // reaction_force
  if (!hyperdog_uros_msgs__msg__Vector3__init(&msg->reaction_force)) {
    hyperdog_uros_msgs__msg__LegStates__fini(msg);
    return false;
  }
  // error_code
  return true;
}

void
hyperdog_uros_msgs__msg__LegStates__fini(hyperdog_uros_msgs__msg__LegStates * msg)
{
  if (!msg) {
    return;
  }
  // leg_id
  rosidl_runtime_c__String__fini(&msg->leg_id);
  // is_contacted
  // position
  hyperdog_uros_msgs__msg__Vector3__fini(&msg->position);
  // velocity
  hyperdog_uros_msgs__msg__Vector3__fini(&msg->velocity);
  // applied_force
  hyperdog_uros_msgs__msg__Vector3__fini(&msg->applied_force);
  // reaction_force
  hyperdog_uros_msgs__msg__Vector3__fini(&msg->reaction_force);
  // error_code
}

bool
hyperdog_uros_msgs__msg__LegStates__are_equal(const hyperdog_uros_msgs__msg__LegStates * lhs, const hyperdog_uros_msgs__msg__LegStates * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // leg_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->leg_id), &(rhs->leg_id)))
  {
    return false;
  }
  // is_contacted
  if (lhs->is_contacted != rhs->is_contacted) {
    return false;
  }
  // position
  if (!hyperdog_uros_msgs__msg__Vector3__are_equal(
      &(lhs->position), &(rhs->position)))
  {
    return false;
  }
  // velocity
  if (!hyperdog_uros_msgs__msg__Vector3__are_equal(
      &(lhs->velocity), &(rhs->velocity)))
  {
    return false;
  }
  // applied_force
  if (!hyperdog_uros_msgs__msg__Vector3__are_equal(
      &(lhs->applied_force), &(rhs->applied_force)))
  {
    return false;
  }
  // reaction_force
  if (!hyperdog_uros_msgs__msg__Vector3__are_equal(
      &(lhs->reaction_force), &(rhs->reaction_force)))
  {
    return false;
  }
  // error_code
  if (lhs->error_code != rhs->error_code) {
    return false;
  }
  return true;
}

bool
hyperdog_uros_msgs__msg__LegStates__copy(
  const hyperdog_uros_msgs__msg__LegStates * input,
  hyperdog_uros_msgs__msg__LegStates * output)
{
  if (!input || !output) {
    return false;
  }
  // leg_id
  if (!rosidl_runtime_c__String__copy(
      &(input->leg_id), &(output->leg_id)))
  {
    return false;
  }
  // is_contacted
  output->is_contacted = input->is_contacted;
  // position
  if (!hyperdog_uros_msgs__msg__Vector3__copy(
      &(input->position), &(output->position)))
  {
    return false;
  }
  // velocity
  if (!hyperdog_uros_msgs__msg__Vector3__copy(
      &(input->velocity), &(output->velocity)))
  {
    return false;
  }
  // applied_force
  if (!hyperdog_uros_msgs__msg__Vector3__copy(
      &(input->applied_force), &(output->applied_force)))
  {
    return false;
  }
  // reaction_force
  if (!hyperdog_uros_msgs__msg__Vector3__copy(
      &(input->reaction_force), &(output->reaction_force)))
  {
    return false;
  }
  // error_code
  output->error_code = input->error_code;
  return true;
}

hyperdog_uros_msgs__msg__LegStates *
hyperdog_uros_msgs__msg__LegStates__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_msgs__msg__LegStates * msg = (hyperdog_uros_msgs__msg__LegStates *)allocator.allocate(sizeof(hyperdog_uros_msgs__msg__LegStates), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hyperdog_uros_msgs__msg__LegStates));
  bool success = hyperdog_uros_msgs__msg__LegStates__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hyperdog_uros_msgs__msg__LegStates__destroy(hyperdog_uros_msgs__msg__LegStates * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hyperdog_uros_msgs__msg__LegStates__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hyperdog_uros_msgs__msg__LegStates__Sequence__init(hyperdog_uros_msgs__msg__LegStates__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_msgs__msg__LegStates * data = NULL;

  if (size) {
    data = (hyperdog_uros_msgs__msg__LegStates *)allocator.zero_allocate(size, sizeof(hyperdog_uros_msgs__msg__LegStates), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hyperdog_uros_msgs__msg__LegStates__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hyperdog_uros_msgs__msg__LegStates__fini(&data[i - 1]);
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
hyperdog_uros_msgs__msg__LegStates__Sequence__fini(hyperdog_uros_msgs__msg__LegStates__Sequence * array)
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
      hyperdog_uros_msgs__msg__LegStates__fini(&array->data[i]);
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

hyperdog_uros_msgs__msg__LegStates__Sequence *
hyperdog_uros_msgs__msg__LegStates__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_msgs__msg__LegStates__Sequence * array = (hyperdog_uros_msgs__msg__LegStates__Sequence *)allocator.allocate(sizeof(hyperdog_uros_msgs__msg__LegStates__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hyperdog_uros_msgs__msg__LegStates__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hyperdog_uros_msgs__msg__LegStates__Sequence__destroy(hyperdog_uros_msgs__msg__LegStates__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hyperdog_uros_msgs__msg__LegStates__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hyperdog_uros_msgs__msg__LegStates__Sequence__are_equal(const hyperdog_uros_msgs__msg__LegStates__Sequence * lhs, const hyperdog_uros_msgs__msg__LegStates__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hyperdog_uros_msgs__msg__LegStates__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hyperdog_uros_msgs__msg__LegStates__Sequence__copy(
  const hyperdog_uros_msgs__msg__LegStates__Sequence * input,
  hyperdog_uros_msgs__msg__LegStates__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hyperdog_uros_msgs__msg__LegStates);
    hyperdog_uros_msgs__msg__LegStates * data =
      (hyperdog_uros_msgs__msg__LegStates *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hyperdog_uros_msgs__msg__LegStates__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          hyperdog_uros_msgs__msg__LegStates__fini(&data[i]);
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
    if (!hyperdog_uros_msgs__msg__LegStates__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}