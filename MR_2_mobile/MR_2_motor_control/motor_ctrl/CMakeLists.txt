cmake_minimum_required(VERSION 3.0.2)
project(motor_ctrl)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  #message_geration
  geometry_msgs
  tf
  tf2
  robot_msgs
)


catkin_package(
  INCLUDE_DIRS include
  LIBRARIES motor_node robot_msgs
  CATKIN_DEPENDS roscpp std_msgs 
  DEPENDS system_lib
)

include_directories(
  include
  include/odometry
  ${catkin_INCLUDE_DIRS}
)



add_executable(${PROJECT_NAME}_node src/main.cpp)
add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_node
   ${catkin_LIBRARIES}
 )
