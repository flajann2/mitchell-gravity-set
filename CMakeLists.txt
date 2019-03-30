# Main project
cmake_minimum_required (VERSION 3.12.1)
project (mgs VERSION 0.0.0 DESCRIPTION "Mitchell Gravity Set 4th Generation")

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set (CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")

add_subdirectory (compute)
add_subdirectory (gui)
add_subdirectory (submods)

if (ENABLE_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if (ENABLE_DOXYGEN)
  message("Doxygen is enabled")
  # apt install graphviz mscgen dia
  # for full functionality
  find_package(Doxygen REQUIRED dot mscgen dia)

  set(doxywork "${CMAKE_CURRENT_SOURCE_DIR}/documentation")
  set(doxyfile_in ${doxywork}/Doxyfile.in)
  set(doxyfile ${doxywork}/Doxyfile)
  set(doxytarget ${doxywork}/doxy)

  file(REMOVE_RECURSE ${doxytarget})
  
  doxygen_add_docs(doxygen
    ${PROJECT_SOURCE_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

  add_custom_target(doc ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM)
  
endif()
