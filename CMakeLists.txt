cmake_minimum_required(VERSION 3.14)
project(easter_hunt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
    SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

set(
    INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/lib/raylib-cpp/include
    ${CMAKE_SOURCE_DIR}/lib/raylib-cpp/bin/_deps/raylib-src/src
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