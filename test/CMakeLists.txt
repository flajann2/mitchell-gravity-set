# Testing the compute module
add_executable (mgstest test.cpp)

# Always set test suite in debug mode
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

set_property(
  TARGET mgstest
  PROPERTY IMPORTED_LOCATION
  ${CMAKE_SOURCE_DIR}/compute
  ${CMAKE_SOURCE_DIR}/compute/header
  )

include_directories(
  ${CMAKE_SOURCE_DIR}/compute/include
  )

target_link_libraries(mgstest mgscompute)
