cmake_minimum_required(VERSION 3.8)
project(turtlesim_joy)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)  
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_srvs REQUIRED)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_cppcheck_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()


add_executable(turtlesim_joy src/turtlesim_Joy.cpp)
ament_target_dependencies(turtlesim_joy rclcpp sensor_msgs geometry_msgs turtlesim std_srvs)

install(TARGETS
  turtlesim_joy
  DESTINATION lib/${PROJECT_NAME}
)
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
