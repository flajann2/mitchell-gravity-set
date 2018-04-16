# Testing the compute module
include(AddGTestTest)
include(AddGMock)

add_gmock()

file(GLOB SOURCE_FILES "*.cpp" "*.h")

set(TARGET test_gsc)

add_test(NAME ${TARGET} COMMAND ${TARGET})

add_executable (mgstest test.cpp)

# Always set test suite in debug mode
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

set_property(
  TARGET mgstest
  PROPERTY IMPORTED_LOCATION
  ${CMAKE_SOURCE_DIR}/compute
  ${CMAKE_SOURCE_DIR}/compute/include
  )

include_directories(
  ${CMAKE_SOURCE_DIR}/compute/include
  )

target_link_libraries(mgstest mgscompute)
