cmake_minimum_required(VERSION 2.8)
project(opulence)

IF (WIN32)
    add_definitions(-DGLEW_STATIC)
ENDIF()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${opulence_SOURCE_DIR}/")

find_package(Threads)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)

IF (NOT WIN32)
    find_package(GLEW REQUIRED)
ENDIF()


include_directories(${PROJECT_BINARY_DIR}
                    ${OPENGL_INCLUDE_DIRS}
                    ${SDL2_INCLUDE_DIR}
                    ${GLEW_INCLUDE_DIR}
                    ${GLM_INCLUDE_DIRS})

IF (WIN32)
    set(SOURCE_FILES
        ../main.cpp
        opulence.cpp
        src/service/glew/glew.h
        src/service/glew/wglew.h
        src/service/glew/glew.c)
ELSE()
    set(SOURCE_FILES
        ../main.cpp
        opulence.cpp)
ENDIF()

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
            src/service/OsType.h

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
            ../src/sprite/Sprite.hpp
            ../src/sprite/Sprite.cpp

            # controllers
            ../src/controller/Controller.hpp
            ../src/controller/standardcontroller/StandardController.hpp
            ../src/controller/standardcontroller/StandardController.cpp

                # control sets
                ../src/controller/controlset/ControlSet.hpp
                ../src/controller/controlset/PlayerSet.hpp

            # services
            ../src/service/PathFinder.hpp
            ../src/service/PathFinder.cpp

            # generators
            ../src/generator/SpriteGenerator.hpp
            ../src/generator/SpriteGenerator.cpp

            # generated includes
            ../src/sprite/AdvancedSprite.cpp
            ../src/ai/AiState.hpp
            ../src/ai/Ai.cpp
            ../src/ai/Ai.hpp
            ../src/utility/DayManager.cpp
            ../src/utility/DayManager.hpp
            ../src/anima/interface/character/population/Population.hpp
            ../src/anima/interface/coin/Coin.hpp
            ../src/anima/interface/character/CharacterSet.cpp
            ../src/anima/interface/character/CharacterSet.hpp
            ../src/anima/interface/character/Character.cpp
            ../src/anima/interface/character/Character.hpp
            ../src/generator/InterfaceGenerator.cpp
            ../src/generator/InterfaceGenerator.hpp
            ../src/habitat/garbage/Garbage.cpp
            ../src/habitat/garbage/Garbage.hpp
            ../src/habitat/tree/Tree.cpp
            ../src/habitat/tree/Tree.hpp
            ../src/habitat/Habitat.hpp
            ../src/anima/interface/button/Button.cpp
            ../src/anima/interface/button/Button.hpp
            ../src/anima/interface/Interface.hpp
            ../src/service/Manipulator.cpp
            ../src/service/Manipulator.hpp
            ../src/service/Lobber.cpp
            ../src/service/Lobber.hpp
            ../src/sprite/AdvancedSprite.hpp
            ../src/utility/LevelObject.hpp
            ../src/utility/LevelMaker.cpp
            ../src/utility/LevelMaker.hpp
            ../src/anima/Anima.hpp
)

target_link_libraries(opulence
                    ${SDL2_LIBRARY}
                    ${GLEW_LIBRARY}
                    ${OPENGL_LIBRARIES})
