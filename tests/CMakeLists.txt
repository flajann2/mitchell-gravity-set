set(GOOGLE_TEST_INDIVIDUAL OFF)

include(AddGMock)
include(AddGTest)

add_gmock()

file(GLOB TESTS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/include/header
  ${CMAKE_SOURCE_DIR}/include
  )

foreach(TEST_PATH ${TESTS})
  get_filename_component(T ${TEST_PATH} NAME_WE)

  add_executable(${T} ${TEST_PATH})
  
  target_link_libraries(${T}
    ${LIBRARY_DEPENDENCIES}
    gtest gtest_main
    gmock gmock_main
    )

  add_test(${T} ${TEST_PATH} PUBLIC MERSEBERG) 
endforeach()
