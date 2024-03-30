cmake_minimum_required(VERSION 3.8)
project(cpp_gae)

# Set C++ standard
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

# Compiler options for GNU and Clang
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)
find_package(OpenCV REQUIRED)
find_package(yaml-cpp REQUIRED)

# Include directories
include_directories(include ${OpenCV_INCLUDE_DIRS})

# Declare executables
add_executable(image_publisher src/image_publisher.cpp)
add_executable(image_subscriber src/image_subscriber.cpp)

# Specify libraries to link a library or executable target against
ament_target_dependencies(image_publisher
  rclcpp
  sensor_msgs
  std_msgs
  cv_bridge
  image_transport
  OpenCV
  yaml-cpp
)

ament_target_dependencies(image_subscriber  
  rclcpp
  sensor_msgs
  std_msgs
  cv_bridge
  image_transport
  OpenCV
  yaml-cpp
)

target_link_libraries(image_publisher
  ${OpenCV_LIBS}
  yaml-cpp
)

target_link_libraries(image_subscriber
  ${OpenCV_LIBS}
  yaml-cpp
)


# Install the executables
install(TARGETS
  image_publisher
  image_subscriber
  DESTINATION lib/${PROJECT_NAME}
)

# Conditional block for linting and testing
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()

  # Skips cpplint if package is not in a git repo or if copyrights and license need to be added
  set(ament_cmake_cpplint_FOUND TRUE)
endif()

# Setup the project to be discoverable by other ROS 2 packages
ament_package()
