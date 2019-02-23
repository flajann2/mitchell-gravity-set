# GUI
cmake_minimum_required (VERSION 3.10.0)

set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOMOC_RELAXED_MODE ON)
set (QT_VERSION_REQ "5.10.1")
set (CMAKE_PREFIX_PATH "/opt/Qt5.10.1/5.10.1/gcc_64/lib/cmake/")

add_executable (mgs main.cpp star_field_gui.cpp star_config.cpp viewport.cpp)

set_property(
  TARGET mgs
  PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/compute/header
  )

find_package(Qt5
  COMPONENTS
  Core
  Widgets
  DataVisualization
  Gui
  OpenGL
  REQUIRED)

if ( NOT Qt5Core_FOUND )
  message(FATAL_ERROR "Qt5 required but not found")
endif ( NOT Qt5Core_FOUND )

include_directories(
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/compute/include
  ${CMAKE_SOURCE_DIR}/compute
  )

# message(STATUS "Qt5 Included directories: \n"
#   "\t" $ENV{QT_LOCAL_DIR} "\n"
#   "\t" ${Qt5Core_INCLUDE_DIRS} "\n"
#   "\t" ${Qt5Widgets_INCLUDE_DIRS} "\n") 

target_link_libraries(mgs
  mgscompute
  Qt5::Core
  Qt5::Widgets
  Qt5::DataVisualization
  glut
  GLU
  GL
  )

add_custom_command(TARGET mgs PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/gui/assets $<TARGET_FILE_DIR:mgs>/assets)
