find_package(Doxygen REQUIRED)

# Prepare doxygen configuration file
set(OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
set(DOXYGEN_INPUT ${PROJECT_SOURCE_DIR}/include)
set(DOXYGEN_EXAMPLE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/examples)
set(DOXYGEN_PROJECT_NAME ${PROJECT_NAME})
string(TIMESTAMP DATE "%Y-%m-%d")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxygen.cfg.in ${CMAKE_CURRENT_BINARY_DIR}/doxygen.cfg)

# Where to place the generated doxygen documentation
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/docs)

# create the directory for the docs
add_custom_target(merseberg ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${DOXYGEN_OUTPUT_DIR})

# Add doxygen as target
add_custom_command(
  OUTPUT ${DOXYGEN_OUTPUT_DIR}
  COMMAND ${DOXYGEN_EXECUTABLE} ARGS ${CMAKE_CURRENT_BINARY_DIR}/doxygen.cfg
  COMMENT "Building doxygen documentation"
)

# Cleanup $build/doc/doxygen on "make clean"
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES doxygen)

add_custom_target(
  doxygen
  DEPENDS ${DOXYGEN_OUTPUT_DIR}
)

# Install HTML API documentation and manual pages
set(DOC_PATH "share/doc/${PROJECT_NAME}")

install(DIRECTORY ${DOXYGEN_OUTPUT_DIR}
  DESTINATION ${DOC_PATH}
)

add_custom_target(api-doc ALL)
add_dependencies(api-doc doxygen)
add_custom_target(doc ALL)
add_dependencies(doc api-doc)
