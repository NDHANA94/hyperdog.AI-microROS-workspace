// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hyperdog_uros_msgs:srv/SetMotorsControlLimits.idl
// generated code does not contain a copyright notice
#include "hyperdog_uros_msgs/srv/detail/set_motors_control_limits__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `fr_hip_pitch`
// Member `fr_hip_roll`
// Member `fr_knee`
// Member `fl_hip_pitch`
// Member `fl_hip_roll`
// Member `fl_knee`
// Member `rr_hip_pitch`
// Member `rr_hip_roll`
// Member `rr_knee`
// Member `rl_hip_pitch`
// Member `rl_hip_roll`
// Member `rl_knee`
#include "hyperdog_uros_msgs/msg/detail/motor_ctrl_limits__functions.h"

bool
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__init(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request * msg)
{
  if (!msg) {
    return false;
  }
  // fr_hip_pitch
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__init(&msg->fr_hip_pitch)) {
    hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__fini(msg);
    return false;
  }
  // fr_hip_roll
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__init(&msg->fr_hip_roll)) {
    hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__fini(msg);
    return false;
  }
  // fr_knee
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__init(&msg->fr_knee)) {
    hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__fini(msg);
    return false;
  }
  // fl_hip_pitch
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__init(&msg->fl_hip_pitch)) {
    hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__fini(msg);
    return false;
  }
  // fl_hip_roll
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__init(&msg->fl_hip_roll)) {
    hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__fini(msg);
    return false;
  }
  // fl_knee
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__init(&msg->fl_knee)) {
    hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__fini(msg);
    return false;
  }
  // rr_hip_pitch
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__init(&msg->rr_hip_pitch)) {
    hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__fini(msg);
    return false;
  }
  // rr_hip_roll
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__init(&msg->rr_hip_roll)) {
    hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__fini(msg);
    return false;
  }
  // rr_knee
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__init(&msg->rr_knee)) {
    hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__fini(msg);
    return false;
  }
  // rl_hip_pitch
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__init(&msg->rl_hip_pitch)) {
    hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__fini(msg);
    return false;
  }
  // rl_hip_roll
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__init(&msg->rl_hip_roll)) {
    hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__fini(msg);
    return false;
  }
  // rl_knee
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__init(&msg->rl_knee)) {
    hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__fini(msg);
    return false;
  }
  return true;
}

void
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__fini(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request * msg)
{
  if (!msg) {
    return;
  }
  // fr_hip_pitch
  hyperdog_uros_msgs__msg__MotorCtrlLimits__fini(&msg->fr_hip_pitch);
  // fr_hip_roll
  hyperdog_uros_msgs__msg__MotorCtrlLimits__fini(&msg->fr_hip_roll);
  // fr_knee
  hyperdog_uros_msgs__msg__MotorCtrlLimits__fini(&msg->fr_knee);
  // fl_hip_pitch
  hyperdog_uros_msgs__msg__MotorCtrlLimits__fini(&msg->fl_hip_pitch);
  // fl_hip_roll
  hyperdog_uros_msgs__msg__MotorCtrlLimits__fini(&msg->fl_hip_roll);
  // fl_knee
  hyperdog_uros_msgs__msg__MotorCtrlLimits__fini(&msg->fl_knee);
  // rr_hip_pitch
  hyperdog_uros_msgs__msg__MotorCtrlLimits__fini(&msg->rr_hip_pitch);
  // rr_hip_roll
  hyperdog_uros_msgs__msg__MotorCtrlLimits__fini(&msg->rr_hip_roll);
  // rr_knee
  hyperdog_uros_msgs__msg__MotorCtrlLimits__fini(&msg->rr_knee);
  // rl_hip_pitch
  hyperdog_uros_msgs__msg__MotorCtrlLimits__fini(&msg->rl_hip_pitch);
  // rl_hip_roll
  hyperdog_uros_msgs__msg__MotorCtrlLimits__fini(&msg->rl_hip_roll);
  // rl_knee
  hyperdog_uros_msgs__msg__MotorCtrlLimits__fini(&msg->rl_knee);
}

bool
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__are_equal(const hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request * lhs, const hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // fr_hip_pitch
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__are_equal(
      &(lhs->fr_hip_pitch), &(rhs->fr_hip_pitch)))
  {
    return false;
  }
  // fr_hip_roll
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__are_equal(
      &(lhs->fr_hip_roll), &(rhs->fr_hip_roll)))
  {
    return false;
  }
  // fr_knee
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__are_equal(
      &(lhs->fr_knee), &(rhs->fr_knee)))
  {
    return false;
  }
  // fl_hip_pitch
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__are_equal(
      &(lhs->fl_hip_pitch), &(rhs->fl_hip_pitch)))
  {
    return false;
  }
  // fl_hip_roll
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__are_equal(
      &(lhs->fl_hip_roll), &(rhs->fl_hip_roll)))
  {
    return false;
  }
  // fl_knee
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__are_equal(
      &(lhs->fl_knee), &(rhs->fl_knee)))
  {
    return false;
  }
  // rr_hip_pitch
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__are_equal(
      &(lhs->rr_hip_pitch), &(rhs->rr_hip_pitch)))
  {
    return false;
  }
  // rr_hip_roll
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__are_equal(
      &(lhs->rr_hip_roll), &(rhs->rr_hip_roll)))
  {
    return false;
  }
  // rr_knee
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__are_equal(
      &(lhs->rr_knee), &(rhs->rr_knee)))
  {
    return false;
  }
  // rl_hip_pitch
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__are_equal(
      &(lhs->rl_hip_pitch), &(rhs->rl_hip_pitch)))
  {
    return false;
  }
  // rl_hip_roll
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__are_equal(
      &(lhs->rl_hip_roll), &(rhs->rl_hip_roll)))
  {
    return false;
  }
  // rl_knee
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__are_equal(
      &(lhs->rl_knee), &(rhs->rl_knee)))
  {
    return false;
  }
  return true;
}

bool
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__copy(
  const hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request * input,
  hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // fr_hip_pitch
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__copy(
      &(input->fr_hip_pitch), &(output->fr_hip_pitch)))
  {
    return false;
  }
  // fr_hip_roll
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__copy(
      &(input->fr_hip_roll), &(output->fr_hip_roll)))
  {
    return false;
  }
  // fr_knee
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__copy(
      &(input->fr_knee), &(output->fr_knee)))
  {
    return false;
  }
  // fl_hip_pitch
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__copy(
      &(input->fl_hip_pitch), &(output->fl_hip_pitch)))
  {
    return false;
  }
  // fl_hip_roll
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__copy(
      &(input->fl_hip_roll), &(output->fl_hip_roll)))
  {
    return false;
  }
  // fl_knee
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__copy(
      &(input->fl_knee), &(output->fl_knee)))
  {
    return false;
  }
  // rr_hip_pitch
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__copy(
      &(input->rr_hip_pitch), &(output->rr_hip_pitch)))
  {
    return false;
  }
  // rr_hip_roll
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__copy(
      &(input->rr_hip_roll), &(output->rr_hip_roll)))
  {
    return false;
  }
  // rr_knee
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__copy(
      &(input->rr_knee), &(output->rr_knee)))
  {
    return false;
  }
  // rl_hip_pitch
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__copy(
      &(input->rl_hip_pitch), &(output->rl_hip_pitch)))
  {
    return false;
  }
  // rl_hip_roll
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__copy(
      &(input->rl_hip_roll), &(output->rl_hip_roll)))
  {
    return false;
  }
  // rl_knee
  if (!hyperdog_uros_msgs__msg__MotorCtrlLimits__copy(
      &(input->rl_knee), &(output->rl_knee)))
  {
    return false;
  }
  return true;
}

hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request *
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request * msg = (hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request *)allocator.allocate(sizeof(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request));
  bool success = hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__destroy(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__Sequence__init(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request * data = NULL;

  if (size) {
    data = (hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request *)allocator.zero_allocate(size, sizeof(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__fini(&data[i - 1]);
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
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__Sequence__fini(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__Sequence * array)
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
      hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__fini(&array->data[i]);
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

hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__Sequence *
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__Sequence * array = (hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__Sequence *)allocator.allocate(sizeof(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__Sequence__destroy(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__Sequence__are_equal(const hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__Sequence * lhs, const hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__Sequence__copy(
  const hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__Sequence * input,
  hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request);
    hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request * data =
      (hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__fini(&data[i]);
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
    if (!hyperdog_uros_msgs__srv__SetMotorsControlLimits_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `error_msg`
#include "rosidl_runtime_c/string_functions.h"

bool
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__init(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response * msg)
{
  if (!msg) {
    return false;
  }
  // is_set
  // error_msg
  if (!rosidl_runtime_c__String__init(&msg->error_msg)) {
    hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__fini(msg);
    return false;
  }
  return true;
}

void
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__fini(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response * msg)
{
  if (!msg) {
    return;
  }
  // is_set
  // error_msg
  rosidl_runtime_c__String__fini(&msg->error_msg);
}

bool
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__are_equal(const hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response * lhs, const hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // is_set
  if (lhs->is_set != rhs->is_set) {
    return false;
  }
  // error_msg
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->error_msg), &(rhs->error_msg)))
  {
    return false;
  }
  return true;
}

bool
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__copy(
  const hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response * input,
  hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // is_set
  output->is_set = input->is_set;
  // error_msg
  if (!rosidl_runtime_c__String__copy(
      &(input->error_msg), &(output->error_msg)))
  {
    return false;
  }
  return true;
}

hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response *
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response * msg = (hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response *)allocator.allocate(sizeof(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response));
  bool success = hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__destroy(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__Sequence__init(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response * data = NULL;

  if (size) {
    data = (hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response *)allocator.zero_allocate(size, sizeof(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__fini(&data[i - 1]);
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
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__Sequence__fini(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__Sequence * array)
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
      hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__fini(&array->data[i]);
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

hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__Sequence *
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__Sequence * array = (hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__Sequence *)allocator.allocate(sizeof(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__Sequence__destroy(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__Sequence__are_equal(const hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__Sequence * lhs, const hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__Sequence__copy(
  const hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__Sequence * input,
  hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response);
    hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response * data =
      (hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__fini(&data[i]);
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
    if (!hyperdog_uros_msgs__srv__SetMotorsControlLimits_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
