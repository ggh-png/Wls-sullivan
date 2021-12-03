cmake_minimum_required(VERSION 2.8.0)
project(MR_2_UI)

add_compile_options(-std=c++11)

set(CMAKE_AUTOUIC ON)

find_package(catkin REQUIRED COMPONENTS
    qt_build
    roscpp
    rospy
    std_msgs
    geometry_msgs
    roslib
)

include_directories(${catkin_INCLUDE_DIRS})
catkin_package()
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets)
QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
QT5_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})

include_directories(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    )

include_directories(
    src/mrmainwindow
    src/mrdialog
    src/image
    )

set(SOURCES
    src/main.cpp
    src/mrmainwindow/mrmainwindow.cpp
    src/mrdialog/mrdialog.cpp
    src/image/image.cpp
    )
set(QT_UI
    src/mrmainwindow/mrmainwindow.ui
    src/mrdialog/mrdialog.ui
    )

add_executable(${PROJECT_NAME}_node
    ${SOURCES}
    ${QT_UI}
    ${QT_RESOURCES_CPP}
    ${QT_FORMS_HPP}
    ${QT_MOC_HPP}
    )

target_link_libraries(${PROJECT_NAME}_node
    ${QT_LIBRARIES}
    ${catkin_LIBRARIES}
    Qt5::Core
    Qt5::Widgets
    )

