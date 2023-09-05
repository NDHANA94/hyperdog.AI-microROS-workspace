cmake_minimum_required(VERSION 3.5)
project(hyperdog_uros_interfaces)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

# <!--  -->
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/InitLegMotors.msg"
  "msg/InitMotor.msg"
  "msg/LegCmd.msg"
  "msg/LegsCmd.msg"
  "msg/LegsStates.msg"
  "msg/LegStates.msg"
  "msg/Limit.msg"
  "msg/MotorCmd.msg"
  "msg/MotorCmdEncoded.msg"
  "msg/MotorCtrlLimits.msg"
  "msg/MotorFeedback.msg"
  "msg/MotorFeedbackEncoded.msg"
  "msg/MotorParams.msg"
  "msg/MotorsCmdEncoded.msg"
  "msg/MotorsStates.msg"
  "msg/MotorsStatesEncoded.msg"
  "msg/MotorStates.msg"
  "msg/MotorStatesEncoded.msg"
  "msg/Vector3.msg"

  "srv/DisableAllMotors.srv"
  "srv/DisableMotor.srv"
  "srv/DisableMotor2.srv"
  "srv/EnableAllMotors.srv"
  "srv/EnableMotor.srv"
  "srv/EnableMotor2.srv"
  "srv/InitLegMotors.srv"
  "srv/InitMotor.srv"
  "srv/SetLegDamping.srv"
  "srv/SetLegStiffness.srv"
  "srv/SetMotorCmdFrequency.srv"
  "srv/SetMotorIff.srv"
  "srv/SetWatchdogFequency.srv"
  "srv/SetZeroPosition.srv"
  "srv/SetZeroPosition2.srv"
 )
# <!--  -->


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()
ament_export_dependencies(rosidl_default_runtime)
ament_package()
