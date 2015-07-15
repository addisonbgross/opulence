cmake_minimum_required(VERSION 2.8)
project(opulence)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${opulence_SOURCE_DIR}/CMakeFiles")

# Set an output directory for our binaries
set(BIN_DIR ${opulence_SOURCE_DIR}/opulence/bin)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${PROJECT_BINARY_DIR}
                    ${OPENGL_INCLUDE_DIR}
                    ${SDL2_INCLUDE_DIR}
                    ${GLEW_INCLUDE_DIRS})

set(SOURCE_FILES
    ../main.c
    opulence.cpp)

set(HEADER_FILES)
set_source_files_properties(../main.c opulence.cpp PROPERTIES LANGUAGE CXX )
add_executable(opulence ${SOURCE_FILES}
               src/entity/Entity.cpp
               src/entity/Entity.h
               src/loaders/ShaderLoader.cpp
               src/loaders/ShaderLoader.h
               src/entity/model/Model.cpp
               src/entity/model/Model.h
               src/loaders/ObjLoader.cpp
               src/loaders/ObjLoader.h
               src/entity/camera/Camera.cpp
               src/entity/camera/Camera.h
               src/service/BufferCourier.cpp
               src/service/BufferCourier.h src/service/GLManager.cpp src/service/GLManager.h)

target_link_libraries(opulence
                      ${SDL2_LIBRARY}
                      ${OPENGL_LIBRARIES}
                      ${GLEW_LIBRARIES})
