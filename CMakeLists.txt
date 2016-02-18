cmake_minimum_required(VERSION 2.8)
project(opulence)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${opulence_SOURCE_DIR}/")

find_package(Threads)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)

include_directories(${PROJECT_BINARY_DIR}
                    ${OPENGL_INCLUDE_DIRS}
                    ${SDL2_INCLUDE_DIR}
                    ${GLEW_INCLUDE_DIR}
                    ${GLM_INCLUDE_DIRS})

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
            ../src/service/PathFinder.h
            ../src/service/PathFinder.cpp

            # generators
            ../src/generator/SpriteGenerator.h
            ../src/generator/SpriteGenerator.cpp

            # generated includes
            ../src/anima/interface/population/FoodPopulation.h
            ../src/anima/interface/population/SquirrelPopulation.h
            ../src/anima/interface/population/CrowPopulation.h
            ../src/anima/interface/coin/Coin.h
            ../src/anima/interface/character/CharacterSet.cpp
            ../src/anima/interface/character/CharacterSet.h
            ../src/anima/interface/character/Character.cpp
            ../src/anima/interface/character/Character.h
            ../src/generator/InterfaceGenerator.cpp
            ../src/generator/InterfaceGenerator.h
            ../src/habitat/garbage/Garbage.cpp
            ../src/habitat/garbage/Garbage.h
            ../src/habitat/tree/Tree.cpp
            ../src/habitat/tree/Tree.h
            ../src/habitat/Habitat.h
            ../src/anima/interface/button/Button.cpp
            ../src/anima/interface/button/Button.h
            ../src/anima/interface/Interface.h
            ../src/service/Manipulator.cpp
            ../src/service/Manipulator.h
            ../src/sprite/AdvancedSprite.h
            ../src/sprite/crow/Crow.cpp
            ../src/sprite/crow/Crow.h
            ../src/utility/LevelObject.h
            ../src/utility/LevelMaker.cpp
            ../src/utility/LevelMaker.h
            ../src/anima/Anima.h
)

target_link_libraries(opulence
                    ${SDL2_LIBRARY}
                    ${OPENGL_LIBRARIES}
                    ${GLEW_LIBRARIES})
