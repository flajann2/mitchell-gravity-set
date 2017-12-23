# GUI
add_executable (mgs mgs.cpp configuration.cpp)

set_property(
  TARGET mgs
  PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/compute/header
  )

find_package (Qt REQUIRED COMPONENTS 
  QtGui
  QtOpenGL
  QtQml
  QtWidgets
  )

include_directories(
  ${Qt_INCLUDES}
  ${Qt_QtGui_INCLUDES}
  ${Qt_QtOpenGL_INCLUDES}
  ${Qt_QtQml_INCLUDES}
  ${Qt_QtWidgets_INCLUDES}
  ${CMAKE_SOURCE_DIR}/compute/include
  )
message(INFO ${Qt_INCLUDES})

target_link_libraries(mgs
  ${Qt_LIBS}
  ${Qt_QtGui_LIBS}
  ${Qt_QtOpenGL_LIBS}
  ${Qt_QtQml_LIBS}
  ${Qt_QtWidgets_LIBS}
  mgscompute
  )

# target_link_libraries(mgs mgscompute)
