cmake_minimum_required(VERSION 3.5)
project(motor_states_decoder)

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
find_package(hyperdog_ctrl_legs REQUIRED)
find_library(libmotor_config NO_DEFAULT_PATH)

install(DIRECTORY
  src
  DESTINATION share/${PROJECT_NAME}
)



add_executable(motor_states_decoder_node src/motor_states_decoder_node.cpp src/minicheetah_motor_utils.cpp)
target_include_directories(motor_states_decoder_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
  motor_states_decoder_node
  rclcpp
  hyperdog_uros_interfaces
  hyperdog_ctrl_legs
)
install(TARGETS motor_states_decoder_node
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
