# ===============================================================================
# Made by: Yakub (https://github.com/itsYakub)
# Version: 1.0.0
# ===============================================================================
# Project's Licence:
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
# OR OTHER DEALINGS IN THE SOFTWARE.
# ===============================================================================

cmake_minimum_required(VERSION 3.14)
project(easter_hunt VERSION 1.0.0)

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
    ${CMAKE_SOURCE_DIR}/src/Resources.cpp    
)

set(
    INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/lib/raylib-cpp/include
    ${CMAKE_SOURCE_DIR}/lib/raylib-cpp/bin/_deps/raylib-src/src
)

set(
    LINK_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/lib/raylib-cpp/bin/_deps/raylib-build/raylib
)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows") 
    set(
        COMPILE_OPTIONS
        -std=c++20
        -Wall
        -Werror
        -Wextra
        -Wpedantic
        -O2
        -static-libgcc
        -static-libstdc++
        -static
        -mwindows
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(
        COMPILE_OPTIONS
        -std=c++20
        -Wall
        -Werror
        -Wextra
        -Wpedantic
        -O2
        -static-libgcc
        -static-libstdc++
    )
endif()

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRECTORIES})
target_link_directories(${PROJECT_NAME} PRIVATE ${LINK_DIRECTORIES})

if (CMAKE_SYSTEM_NAME STREQUAL "Windows") 
    target_link_libraries(${PROJECT_NAME} PRIVATE -lraylib -lgdi32 -lwinmm)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(${PROJECT_NAME} PRIVATE -lraylib)
endif()
