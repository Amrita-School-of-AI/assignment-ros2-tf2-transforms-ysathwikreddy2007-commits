cmake_minimum_required(VERSION 3.8)
project(ros2_tf2)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ==============================
# Find Dependencies
# ==============================
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(geometry_msgs REQUIRED)

# ==============================
# Add Executable
# ==============================
add_executable(tf_broadcaster src/tf_broadcaster.cpp)

ament_target_dependencies(tf_broadcaster
  rclcpp
  tf2_ros
  geometry_msgs
)

# ==============================
# Install Target
# ==============================
install(TARGETS
  tf_broadcaster
  DESTINATION lib/${PROJECT_NAME}
)

# ==============================
# Testing
# ==============================
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
