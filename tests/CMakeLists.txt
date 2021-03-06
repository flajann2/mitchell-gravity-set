# Testing the compute module

# Deal with Google Test
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/tests/googletest-download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/tests/googletest-download" )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/tests/googletest-src"
                 "${CMAKE_BINARY_DIR}/tests/googletest-build")

# The gtest/gmock targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if(CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include")
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package (Threads REQUIRED)

set(TEST_LIBS_DIR ${CMAKE_BINARY_DIR}/lib)

file(GLOB SOURCE_FILES "*.cpp" "*.h")
file(GLOB TEST_LIBS "${TEST_LIBS_DIR}/*.a")

message(STATUS "*** TEST_LIBS:" ${TEST_LIBS})

set(TARGET test_gsc)

add_test(NAME ${TARGET} COMMAND ${TARGET})

add_executable (mgstest ${SOURCE_FILES})

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

target_link_libraries(mgstest mgscompute ${CMAKE_THREAD_LIBS_INIT} ${TEST_LIBS})
