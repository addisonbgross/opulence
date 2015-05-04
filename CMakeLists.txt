cmake_minimum_required(VERSION 2.8)
project(opulence)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)

include_directories(
  ${PROJECT_BINARY_DIR}
  ${OPENGL_INCLUDE_DIR}
  ${GLEW_INCLUDE_DIRS}
  ${GLUT_INCLUDE_DIRS}
  )

set(SOURCE_FILES opulence.c)
set_source_files_properties(opulence.c PROPERTIES LANGUAGE CXX )
add_executable(opulence ${SOURCE_FILES})

target_link_libraries(opulence ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES})
