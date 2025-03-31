cmake_minimum_required(VERSION 3.30)

set(PROJECT_NAME "bouncing_balls")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 2.32.2 EXACT REQUIRED)
add_executable(${PROJECT_NAME} Source/Main.cpp
        Source/Actors/Circle.cpp
        Source/Misc/Color.cpp
        Source/Context.cpp
        Source/Components/Component.cpp
        Source/Actors/Actor.cpp
        Source/Tools/Math.cpp
        Source/Components/DrawComponent.cpp
        Source/Components/CircleDrawComponent.cpp
)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})