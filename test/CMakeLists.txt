# Testing the compute module
add_executable (mgstest test.cpp)

set_property(
  TARGET mgstest
  PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/compute
  )

include_directories(
  ${CMAKE_SOURCE_DIR}/compute/include
  )

target_link_libraries(mgstest mgscompute)
