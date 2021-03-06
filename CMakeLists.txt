###############################################################################
#                 Made by Daniel Aaron Salwerowicz 2018-03-12
###############################################################################
# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

###############################################################################
# Global name of the project
project(StartCode)

###############################################################################
# Include required packages
find_package(Qt5Core REQUIRED)

###############################################################################
# Compile and build
option(BUILD_APPLICATION "Build demo application" TRUE)
if(BUILD_APPLICATION)

  #############################################################################
  # Source files and friends
  set( HDRS
    include/BattleField.hpp
    include/Camera.hpp
    include/Clock.hpp
    include/Enemy.hpp
    include/FpsCounter.hpp
    include/GameManager.hpp
    include/Input.hpp
    include/SceneObject.hpp
    include/SpaceShip.hpp
    include/Weapons.hpp
    include/Shader.hpp
    include/Skybox.hpp
    include/Water.hpp
    include/SpaceShipModel.hpp
    include/OBJLoader.hpp
    include/Particles.hpp
    include/Text.hpp
    include/Vector3.hpp
    )

  set( SRCS
    src/BattleField.cpp
    src/Camera.cpp
    src/GameManager.cpp
    src/SceneObject.cpp
    src/Enemy.cpp
    src/Weapons.cpp
    src/SpaceShip.cpp
    src/Shader.cpp
    src/Skybox.cpp
    src/Water.cpp
    src/SpaceShipModel.cpp
    src/OBJLoader.cpp
    src/Particles.cpp
    src/Text.cpp

    app/main.cpp
    )
    
    set( SHAD
        shaders/red.vert
        shaders/red.frag
        shaders/map.frag
        shaders/map.vert
        shaders/skybox.vert
        shaders/skybox.frag
        shaders/water.frag
        shaders/water.vert
        shaders/ship.frag
        shaders/ship.vert
        shaders/part.frag
        shaders/part.vert)

    set( TEXT
        textures/colorm.bmp
        textures/heightm.bmp )

    set( SBOX
        skybox/up.jpg
        skybox/down.jpg
        skybox/left.jpg
        skybox/right.jpg
        skybox/back.jpg
        skybox/front.jpg
        )

  add_executable(${PROJECT_NAME}
    ${HDRS}
    ${SRCS}
    ${SHAD}
    ${TEXT}
    ${SBOX})

  #############################################################################
  # TURN ON C++17 FEATURES
  if(${CMAKE_VERSION} VERSION_LESS "3.8.0")

    message(STATUS 
    "${PROJECT_NAME} requires compiling in mode supporting C++17 features.")
    
  else()
  
    target_compile_features(${PROJECT_NAME}
      PUBLIC $<$<CXX_COMPILER_ID:Clang>:cxx_std_17>
      PUBLIC $<$<CXX_COMPILER_ID:GNU>:cxx_std_17>
      )
      
  endif() # end ${CMAKE_VERSION} VERSION_LESS "3.8.0"

  #############################################################################
  # Default from QtCreator
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
  set(CMAKE_AUTOMOC ON)

  #############################################################################
  # Qt dependencies
  target_link_libraries(${PROJECT_NAME} Qt5::Core GLEW GL GLU glut SOIL assimp)

endif() # end BUILD_APPLICATION
