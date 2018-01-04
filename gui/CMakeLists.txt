# GUI

set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOMOC_RELAXED_MODE ON)
set (QT_VERSION_REQ "5.6")

add_executable (mgs mgs.cpp)


set_property(
  TARGET mgs
  PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/compute/header
  )

find_package (Qt5Core REQUIRED)
find_package (Qt5Widgets REQUIRED)

if ( NOT Qt5Core_FOUND )
  message(FATAL_ERROR "Qt5 required but not found")
endif ( NOT Qt5Core_FOUND )

include_directories(
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/compute/include
  )

message(STATUS "Qt5 Included directories: "
  "<" ${Qt5Core_INCLUDE_DIRS} ">"
  "<" ${Qt5Widgets_INCLUDE_DIRS} ">") 

target_link_libraries(mgs
  mgscompute
  Qt5
  Qt5::Widgets
  )

# target_link_libraries(mgs mgscompute)
