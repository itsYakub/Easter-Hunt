cmake_minimum_required(VERSION 3.14)
project(easter_hunt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
    SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/Egg.cpp
    ${CMAKE_SOURCE_DIR}/src/EggController.cpp
    ${CMAKE_SOURCE_DIR}/src/Player.cpp
    ${CMAKE_SOURCE_DIR}/src/Timer.cpp
    ${CMAKE_SOURCE_DIR}/src/SceneMenager.cpp
    ${CMAKE_SOURCE_DIR}/src/SceneGameplay.cpp
    ${CMAKE_SOURCE_DIR}/src/SceneSplashScreen.cpp
    ${CMAKE_SOURCE_DIR}/src/Display.cpp    
    ${CMAKE_SOURCE_DIR}/src/Background.cpp    
    ${CMAKE_SOURCE_DIR}/src/ColorList.cpp    
)

set(
    INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/lib/raylib-cpp/include
    ${CMAKE_SOURCE_DIR}/lib/raylib-cpp/bin/_deps/raylib-src/src
    ${CMAKE_SOURCE_DIR}/lib/raygui/src
)

set(
    LINK_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/lib/raylib-cpp/bin/_deps/raylib-build/raylib
)

set(
    LINK_LIBRARIES
    -lraylib
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRECTORIES})
target_link_directories(${PROJECT_NAME} PRIVATE ${LINK_DIRECTORIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LINK_LIBRARIES})