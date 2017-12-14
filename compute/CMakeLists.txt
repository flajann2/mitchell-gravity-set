add_library (mgscompute SHARED compute.cpp)

target_include_directories (mgscompute
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  )

set_target_properties(mgscompute
  PROPERTIES VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER include/mgscompute.h
  )

install(TARGETS mgscompute DESTINATION lib/mgscompute)

file(GLOB HEADERS include/*.h)
install(FILES ${HEADERS} DESTINATION include/mgscompute)
