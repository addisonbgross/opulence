cmake_minimum_required(VERSION 2.8)
project(opulence)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${opulence_SOURCE_DIR}/CMakeFiles")

# Set an output directory for our binaries
set(BIN_DIR ${opulence_SOURCE_DIR}/bin)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(
  ${PROJECT_BINARY_DIR}
  ${OPENGL_INCLUDE_DIR}
  ${SDL2_INCLUDE_DIR}
  ${GLEW_INCLUDE_DIRS}
  )

set(SOURCE_FILES ../main.c opulence.cpp)
set(HEADER_FILES ${PROJECT_BINARY_DIR}/src/ControllerInterface.h)
set_source_files_properties(../main.c opulence.cpp PROPERTIES LANGUAGE CXX )
add_executable(opulence ${SOURCE_FILES} src/loaders/ShaderLoader.cpp src/loaders/ShaderLoader.h src/entity/Model.cpp src/entity/Model.h src/loaders/ObjLoader.cpp src/loaders/ObjLoader.h)

target_link_libraries(opulence ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
