# GUI
add_executable (mgs mgs.cpp)

set_property(
  TARGET mgs
  PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/compute/header
  )

include_directories(
  ${CMAKE_SOURCE_DIR}/compute/include
  )

target_link_libraries(mgs mgscompute)
