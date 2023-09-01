// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hyperdog_uros_interfaces:msg/InitLegMotors.idl
// generated code does not contain a copyright notice
#include "hyperdog_uros_interfaces/msg/detail/init_leg_motors__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `fr_hip_roll`
// Member `fr_hip_pitch`
// Member `fr_knee`
// Member `fl_hip_roll`
// Member `fl_hip_pitch`
// Member `fl_knee`
// Member `rr_hip_roll`
// Member `rr_hip_pitch`
// Member `rr_knee`
// Member `rl_hip_roll`
// Member `rl_hip_pitch`
// Member `rl_knee`
#include "hyperdog_uros_interfaces/msg/detail/init_motor__functions.h"

bool
hyperdog_uros_interfaces__msg__InitLegMotors__init(hyperdog_uros_interfaces__msg__InitLegMotors * msg)
{
  if (!msg) {
    return false;
  }
  // fr_hip_roll
  if (!hyperdog_uros_interfaces__msg__InitMotor__init(&msg->fr_hip_roll)) {
    hyperdog_uros_interfaces__msg__InitLegMotors__fini(msg);
    return false;
  }
  // fr_hip_pitch
  if (!hyperdog_uros_interfaces__msg__InitMotor__init(&msg->fr_hip_pitch)) {
    hyperdog_uros_interfaces__msg__InitLegMotors__fini(msg);
    return false;
  }
  // fr_knee
  if (!hyperdog_uros_interfaces__msg__InitMotor__init(&msg->fr_knee)) {
    hyperdog_uros_interfaces__msg__InitLegMotors__fini(msg);
    return false;
  }
  // fl_hip_roll
  if (!hyperdog_uros_interfaces__msg__InitMotor__init(&msg->fl_hip_roll)) {
    hyperdog_uros_interfaces__msg__InitLegMotors__fini(msg);
    return false;
  }
  // fl_hip_pitch
  if (!hyperdog_uros_interfaces__msg__InitMotor__init(&msg->fl_hip_pitch)) {
    hyperdog_uros_interfaces__msg__InitLegMotors__fini(msg);
    return false;
  }
  // fl_knee
  if (!hyperdog_uros_interfaces__msg__InitMotor__init(&msg->fl_knee)) {
    hyperdog_uros_interfaces__msg__InitLegMotors__fini(msg);
    return false;
  }
  // rr_hip_roll
  if (!hyperdog_uros_interfaces__msg__InitMotor__init(&msg->rr_hip_roll)) {
    hyperdog_uros_interfaces__msg__InitLegMotors__fini(msg);
    return false;
  }
  // rr_hip_pitch
  if (!hyperdog_uros_interfaces__msg__InitMotor__init(&msg->rr_hip_pitch)) {
    hyperdog_uros_interfaces__msg__InitLegMotors__fini(msg);
    return false;
  }
  // rr_knee
  if (!hyperdog_uros_interfaces__msg__InitMotor__init(&msg->rr_knee)) {
    hyperdog_uros_interfaces__msg__InitLegMotors__fini(msg);
    return false;
  }
  // rl_hip_roll
  if (!hyperdog_uros_interfaces__msg__InitMotor__init(&msg->rl_hip_roll)) {
    hyperdog_uros_interfaces__msg__InitLegMotors__fini(msg);
    return false;
  }
  // rl_hip_pitch
  if (!hyperdog_uros_interfaces__msg__InitMotor__init(&msg->rl_hip_pitch)) {
    hyperdog_uros_interfaces__msg__InitLegMotors__fini(msg);
    return false;
  }
  // rl_knee
  if (!hyperdog_uros_interfaces__msg__InitMotor__init(&msg->rl_knee)) {
    hyperdog_uros_interfaces__msg__InitLegMotors__fini(msg);
    return false;
  }
  return true;
}

void
hyperdog_uros_interfaces__msg__InitLegMotors__fini(hyperdog_uros_interfaces__msg__InitLegMotors * msg)
{
  if (!msg) {
    return;
  }
  // fr_hip_roll
  hyperdog_uros_interfaces__msg__InitMotor__fini(&msg->fr_hip_roll);
  // fr_hip_pitch
  hyperdog_uros_interfaces__msg__InitMotor__fini(&msg->fr_hip_pitch);
  // fr_knee
  hyperdog_uros_interfaces__msg__InitMotor__fini(&msg->fr_knee);
  // fl_hip_roll
  hyperdog_uros_interfaces__msg__InitMotor__fini(&msg->fl_hip_roll);
  // fl_hip_pitch
  hyperdog_uros_interfaces__msg__InitMotor__fini(&msg->fl_hip_pitch);
  // fl_knee
  hyperdog_uros_interfaces__msg__InitMotor__fini(&msg->fl_knee);
  // rr_hip_roll
  hyperdog_uros_interfaces__msg__InitMotor__fini(&msg->rr_hip_roll);
  // rr_hip_pitch
  hyperdog_uros_interfaces__msg__InitMotor__fini(&msg->rr_hip_pitch);
  // rr_knee
  hyperdog_uros_interfaces__msg__InitMotor__fini(&msg->rr_knee);
  // rl_hip_roll
  hyperdog_uros_interfaces__msg__InitMotor__fini(&msg->rl_hip_roll);
  // rl_hip_pitch
  hyperdog_uros_interfaces__msg__InitMotor__fini(&msg->rl_hip_pitch);
  // rl_knee
  hyperdog_uros_interfaces__msg__InitMotor__fini(&msg->rl_knee);
}

bool
hyperdog_uros_interfaces__msg__InitLegMotors__are_equal(const hyperdog_uros_interfaces__msg__InitLegMotors * lhs, const hyperdog_uros_interfaces__msg__InitLegMotors * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // fr_hip_roll
  if (!hyperdog_uros_interfaces__msg__InitMotor__are_equal(
      &(lhs->fr_hip_roll), &(rhs->fr_hip_roll)))
  {
    return false;
  }
  // fr_hip_pitch
  if (!hyperdog_uros_interfaces__msg__InitMotor__are_equal(
      &(lhs->fr_hip_pitch), &(rhs->fr_hip_pitch)))
  {
    return false;
  }
  // fr_knee
  if (!hyperdog_uros_interfaces__msg__InitMotor__are_equal(
      &(lhs->fr_knee), &(rhs->fr_knee)))
  {
    return false;
  }
  // fl_hip_roll
  if (!hyperdog_uros_interfaces__msg__InitMotor__are_equal(
      &(lhs->fl_hip_roll), &(rhs->fl_hip_roll)))
  {
    return false;
  }
  // fl_hip_pitch
  if (!hyperdog_uros_interfaces__msg__InitMotor__are_equal(
      &(lhs->fl_hip_pitch), &(rhs->fl_hip_pitch)))
  {
    return false;
  }
  // fl_knee
  if (!hyperdog_uros_interfaces__msg__InitMotor__are_equal(
      &(lhs->fl_knee), &(rhs->fl_knee)))
  {
    return false;
  }
  // rr_hip_roll
  if (!hyperdog_uros_interfaces__msg__InitMotor__are_equal(
      &(lhs->rr_hip_roll), &(rhs->rr_hip_roll)))
  {
    return false;
  }
  // rr_hip_pitch
  if (!hyperdog_uros_interfaces__msg__InitMotor__are_equal(
      &(lhs->rr_hip_pitch), &(rhs->rr_hip_pitch)))
  {
    return false;
  }
  // rr_knee
  if (!hyperdog_uros_interfaces__msg__InitMotor__are_equal(
      &(lhs->rr_knee), &(rhs->rr_knee)))
  {
    return false;
  }
  // rl_hip_roll
  if (!hyperdog_uros_interfaces__msg__InitMotor__are_equal(
      &(lhs->rl_hip_roll), &(rhs->rl_hip_roll)))
  {
    return false;
  }
  // rl_hip_pitch
  if (!hyperdog_uros_interfaces__msg__InitMotor__are_equal(
      &(lhs->rl_hip_pitch), &(rhs->rl_hip_pitch)))
  {
    return false;
  }
  // rl_knee
  if (!hyperdog_uros_interfaces__msg__InitMotor__are_equal(
      &(lhs->rl_knee), &(rhs->rl_knee)))
  {
    return false;
  }
  return true;
}

bool
hyperdog_uros_interfaces__msg__InitLegMotors__copy(
  const hyperdog_uros_interfaces__msg__InitLegMotors * input,
  hyperdog_uros_interfaces__msg__InitLegMotors * output)
{
  if (!input || !output) {
    return false;
  }
  // fr_hip_roll
  if (!hyperdog_uros_interfaces__msg__InitMotor__copy(
      &(input->fr_hip_roll), &(output->fr_hip_roll)))
  {
    return false;
  }
  // fr_hip_pitch
  if (!hyperdog_uros_interfaces__msg__InitMotor__copy(
      &(input->fr_hip_pitch), &(output->fr_hip_pitch)))
  {
    return false;
  }
  // fr_knee
  if (!hyperdog_uros_interfaces__msg__InitMotor__copy(
      &(input->fr_knee), &(output->fr_knee)))
  {
    return false;
  }
  // fl_hip_roll
  if (!hyperdog_uros_interfaces__msg__InitMotor__copy(
      &(input->fl_hip_roll), &(output->fl_hip_roll)))
  {
    return false;
  }
  // fl_hip_pitch
  if (!hyperdog_uros_interfaces__msg__InitMotor__copy(
      &(input->fl_hip_pitch), &(output->fl_hip_pitch)))
  {
    return false;
  }
  // fl_knee
  if (!hyperdog_uros_interfaces__msg__InitMotor__copy(
      &(input->fl_knee), &(output->fl_knee)))
  {
    return false;
  }
  // rr_hip_roll
  if (!hyperdog_uros_interfaces__msg__InitMotor__copy(
      &(input->rr_hip_roll), &(output->rr_hip_roll)))
  {
    return false;
  }
  // rr_hip_pitch
  if (!hyperdog_uros_interfaces__msg__InitMotor__copy(
      &(input->rr_hip_pitch), &(output->rr_hip_pitch)))
  {
    return false;
  }
  // rr_knee
  if (!hyperdog_uros_interfaces__msg__InitMotor__copy(
      &(input->rr_knee), &(output->rr_knee)))
  {
    return false;
  }
  // rl_hip_roll
  if (!hyperdog_uros_interfaces__msg__InitMotor__copy(
      &(input->rl_hip_roll), &(output->rl_hip_roll)))
  {
    return false;
  }
  // rl_hip_pitch
  if (!hyperdog_uros_interfaces__msg__InitMotor__copy(
      &(input->rl_hip_pitch), &(output->rl_hip_pitch)))
  {
    return false;
  }
  // rl_knee
  if (!hyperdog_uros_interfaces__msg__InitMotor__copy(
      &(input->rl_knee), &(output->rl_knee)))
  {
    return false;
  }
  return true;
}

hyperdog_uros_interfaces__msg__InitLegMotors *
hyperdog_uros_interfaces__msg__InitLegMotors__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_interfaces__msg__InitLegMotors * msg = (hyperdog_uros_interfaces__msg__InitLegMotors *)allocator.allocate(sizeof(hyperdog_uros_interfaces__msg__InitLegMotors), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hyperdog_uros_interfaces__msg__InitLegMotors));
  bool success = hyperdog_uros_interfaces__msg__InitLegMotors__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hyperdog_uros_interfaces__msg__InitLegMotors__destroy(hyperdog_uros_interfaces__msg__InitLegMotors * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hyperdog_uros_interfaces__msg__InitLegMotors__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hyperdog_uros_interfaces__msg__InitLegMotors__Sequence__init(hyperdog_uros_interfaces__msg__InitLegMotors__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_interfaces__msg__InitLegMotors * data = NULL;

  if (size) {
    data = (hyperdog_uros_interfaces__msg__InitLegMotors *)allocator.zero_allocate(size, sizeof(hyperdog_uros_interfaces__msg__InitLegMotors), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hyperdog_uros_interfaces__msg__InitLegMotors__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hyperdog_uros_interfaces__msg__InitLegMotors__fini(&data[i - 1]);
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
hyperdog_uros_interfaces__msg__InitLegMotors__Sequence__fini(hyperdog_uros_interfaces__msg__InitLegMotors__Sequence * array)
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
      hyperdog_uros_interfaces__msg__InitLegMotors__fini(&array->data[i]);
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

hyperdog_uros_interfaces__msg__InitLegMotors__Sequence *
hyperdog_uros_interfaces__msg__InitLegMotors__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_interfaces__msg__InitLegMotors__Sequence * array = (hyperdog_uros_interfaces__msg__InitLegMotors__Sequence *)allocator.allocate(sizeof(hyperdog_uros_interfaces__msg__InitLegMotors__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hyperdog_uros_interfaces__msg__InitLegMotors__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hyperdog_uros_interfaces__msg__InitLegMotors__Sequence__destroy(hyperdog_uros_interfaces__msg__InitLegMotors__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hyperdog_uros_interfaces__msg__InitLegMotors__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hyperdog_uros_interfaces__msg__InitLegMotors__Sequence__are_equal(const hyperdog_uros_interfaces__msg__InitLegMotors__Sequence * lhs, const hyperdog_uros_interfaces__msg__InitLegMotors__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hyperdog_uros_interfaces__msg__InitLegMotors__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hyperdog_uros_interfaces__msg__InitLegMotors__Sequence__copy(
  const hyperdog_uros_interfaces__msg__InitLegMotors__Sequence * input,
  hyperdog_uros_interfaces__msg__InitLegMotors__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hyperdog_uros_interfaces__msg__InitLegMotors);
    hyperdog_uros_interfaces__msg__InitLegMotors * data =
      (hyperdog_uros_interfaces__msg__InitLegMotors *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hyperdog_uros_interfaces__msg__InitLegMotors__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          hyperdog_uros_interfaces__msg__InitLegMotors__fini(&data[i]);
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
    if (!hyperdog_uros_interfaces__msg__InitLegMotors__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
