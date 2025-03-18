cmake_minimum_required(VERSION 3.30)

set(PROJECT_NAME "bouncing_balls")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 2.32.2 EXACT REQUIRED)
include_directories(include)
add_executable(${PROJECT_NAME} src/main.cpp
        src/Circle.cpp
        src/Coord.cpp
        src/Color.cpp
        src/Context.cpp
)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})