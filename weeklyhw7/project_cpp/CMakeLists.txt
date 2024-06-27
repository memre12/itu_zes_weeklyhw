cmake_minimum_required(VERSION 3.8)
project(project_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)
find_package(std_srvs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)
find_package(OpenCV REQUIRED)
find_package(X11 REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

# include directories
include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/src) # AStar include path

# Add library for AStar
add_library(AStar src/AStar.cpp)
target_include_directories(AStar PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Add executable for avoidance
add_executable(avoidance src/main.cpp)
ament_target_dependencies(avoidance rclcpp sensor_msgs geometry_msgs turtlesim std_srvs cv_bridge image_transport OpenCV X11)

# Link AStar library
target_link_libraries(avoidance AStar)

# Install directories
install(DIRECTORY
  include/
  DESTINATION include
)

install(DIRECTORY
  launch
  config
  DESTINATION share/${PROJECT_NAME}
)

# Install executables
install(TARGETS
  avoidance
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
