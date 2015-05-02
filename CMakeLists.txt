cmake_minimum_required(VERSION 2.8)
project(opulence)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

configure_file (
  "${PROJECT_SOURCE_DIR}/opulenceConfig.h.in"
  "${PROJECT_BINARY_DIR}/opulenceConfig.h"
  )

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
include_directories("${PROJECT_BINARY_DIR}")

set(SOURCE_FILES opulence.c)
add_executable(opulence ${SOURCE_FILES})

target_link_libraries(opulence ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES})
