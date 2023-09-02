cmake_minimum_required(VERSION 3.5)
project(hyperdog_ctrl_legs)

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
find_package(rclcpp REQUIRED)
find_package(hyperdog_uros_interfaces REQUIRED)

install(DIRECTORY
  src
  config
  DESTINATION share/${PROJECT_NAME}
)

# initLegMotors client
add_executable(initMotors src/init_leg_motors_client.cpp)
target_include_directories(initMotors PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
  initMotors 
  rclcpp 
  hyperdog_uros_interfaces
)
install(TARGETS initMotors
  DESTINATION lib/${PROJECT_NAME})

# enableAllMotors client
add_executable(enableAllMotors src/enable_all_motors_client.cpp)
target_include_directories(enableAllMotors PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
  enableAllMotors 
  rclcpp 
  hyperdog_uros_interfaces
)
install(TARGETS enableAllMotors
  DESTINATION lib/${PROJECT_NAME})

# disableAllMotors client
add_executable(disableAllMotors src/disable_all_motors_client.cpp)
target_include_directories(disableAllMotors PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
  disableAllMotors 
  rclcpp 
  hyperdog_uros_interfaces
)
install(TARGETS disableAllMotors
  DESTINATION lib/${PROJECT_NAME})

# disableAllMotors client
add_executable(setMotorZeroPosition src/set_motor_zero_position_client.cpp)
target_include_directories(setMotorZeroPosition PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
  setMotorZeroPosition 
  rclcpp 
  hyperdog_uros_interfaces
)
install(TARGETS setMotorZeroPosition
  DESTINATION lib/${PROJECT_NAME})


  

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
