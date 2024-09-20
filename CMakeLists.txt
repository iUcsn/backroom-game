cmake_minimum_required(VERSION 3.10)

project(Backrooms)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

set(SOURCES
    src/main.cpp
    src/ProceduralGenerator.cpp
    src/Room.cpp
)

add_executable(backrooms-game ${SOURCES})

target_link_libraries(backrooms-game SDL2::SDL2 OpenGL::GL GLU)
