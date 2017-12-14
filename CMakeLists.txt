# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.10.0)
project (MGS_COMPUTE)

add_subdirectory (compute)
add_subdirectory (gui)
add_subdirectory (test)
