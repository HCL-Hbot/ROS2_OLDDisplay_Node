cmake_minimum_required(VERSION 3.1...3.14)
project(old_display_driver C CXX)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)


add_subdirectory(src/nervousPico_connectivity)
add_executable(old_display_driver_node src/old_display_driver_node.cpp)
target_link_libraries(old_display_driver_node CLI_HOST)

ament_target_dependencies(old_display_driver_node
   rclcpp
   std_msgs
)
target_link_libraries(old_display_driver_node "${cpp_typesupport_target}")

if(UNIX AND NOT APPLE)  # Linux only
 target_compile_options(old_display_driver_node PRIVATE -Wall)
endif()

install(TARGETS
old_display_driver_node
DESTINATION lib/${PROJECT_NAME}) 

ament_package()
