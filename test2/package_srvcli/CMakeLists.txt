cmake_minimum_required(VERSION 3.8)
project(package_srvcli)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tutorial_interfaces REQUIRED)
# find_package(Python3 3.10 REQUIRED COMPONENTS Interpreter Development)

add_executable(caculator src/srv.cpp)
ament_target_dependencies(caculator rclcpp tutorial_interfaces)

add_executable(client src/cli.cpp)
ament_target_dependencies(client rclcpp tutorial_interfaces)

install(TARGETS
  caculator
  client
  DESTINATION lib/${PROJECT_NAME})

ament_package()
