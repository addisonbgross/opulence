cmake_minimum_required(VERSION 2.8)
project(opulence)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${opulence_SOURCE_DIR}/")

# Set an output directory for our binaries
set(BIN_DIR ${opulence_SOURCE_DIR}/opulence/bin)

INCLUDE(FindPkgConfig)
find_package(OpenGL REQUIRED opengl)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(GLEW REQUIRED glew)

include_directories(${PROJECT_BINARY_DIR}
                    ${OPENGL_INCLUDE_DIR}
                    ${SDL2_INCLUDE_DIR}
                    ${GLEW_INCLUDE_DIRS})

set(SOURCE_FILES
    ../main.cpp
    opulence.cpp)

set(HEADER_FILES)
set_source_files_properties(../main.cpp
                            opulence.cpp
                            PROPERTIES
                            LANGUAGE CXX)

add_executable(opulence
            ${SOURCE_FILES}

            # entities
            src/entity/Entity.cpp
            src/entity/Entity.h
            src/entity/model/Model.cpp
            src/entity/model/Model.h
            src/entity/animation/Animation.cpp
            src/entity/animation/Animation.h
            src/entity/camera/Camera.cpp
            src/entity/camera/Camera.h
            src/entity/camera/RtsCamera.cpp
            src/entity/camera/RtsCamera.h
            src/entity/light/Light.cpp
            src/entity/light/Light.h
            src/entity/light/PointLight.cpp
            src/entity/light/PointLight.h
            src/entity/light/DirectionalLight.cpp
            src/entity/light/DirectionalLight.h

            # loaders
            src/loader/ShaderLoader.cpp
            src/loader/ShaderLoader.h
            src/loader/ObjLoader.cpp
            src/loader/ObjLoader.h

            # services
            src/service/BufferCourier.cpp
            src/service/BufferCourier.h
            src/service/GLManager.cpp
            src/service/GLManager.h
            src/service/TimeManager.cpp
            src/service/TimeManager.h

            # factories
            src/factory/CameraFactory.cpp
            src/factory/CameraFactory.h
            src/factory/LightFactory.cpp
            src/factory/LightFactory.h
            src/factory/ModelFactory.cpp
            src/factory/ModelFactory.h

            # containers
            src/container/obj_data.h
            src/container/mtl_data.h

            ############
            # crowgame #
            ############

            # sprites
            ../src/sprite/Sprite.h
            ../src/sprite/Sprite.cpp

            # controllers
            ../src/controller/Controller.h
            ../src/controller/standardcontroller/StandardController.h
            ../src/controller/standardcontroller/StandardController.cpp

                # control sets
                ../src/controller/controlset/ControlSet.h
                ../src/controller/controlset/PlayerSet.h

            # services
            ../src/service/SpriteFinder.h
            ../src/service/SpriteFinder.cpp
            ../src/service/PathFinder.h
            ../src/service/PathFinder.cpp

            # generators
            ../src/generator/SpriteGenerator.h
            ../src/generator/SpriteGenerator.cpp

            # generated includes
            ../src/anima/Anima.h
            ../src/anima/character/Crow.h
            ../src/anima/character/Crow.cpp
            ../src/anima/clock/Clock.h
            ../src/anima/clock/Clock.cpp
            ../src/anima/clock/Digit.h
            ../src/anima/clock/Digit.cpp
)

target_link_libraries(opulence
                    ${SDL2_LIBRARY}
                    ${OPENGL_LIBRARIES}
                    ${GLEW_LIBRARIES})
