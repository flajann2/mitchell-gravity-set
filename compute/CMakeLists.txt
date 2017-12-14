add_library (compute compute.cpp)

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (compute PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
