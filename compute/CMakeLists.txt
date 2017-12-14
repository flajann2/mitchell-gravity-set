add_library (mgscompute SHARED compute.cpp)

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (mgscompute PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(mgscompute PROPERTIES VERSION ${PROJECT_VERSION} PUBLIC_HEADER include/mgscompute.h)

