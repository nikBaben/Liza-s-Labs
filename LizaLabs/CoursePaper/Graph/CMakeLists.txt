cmake_minimum_required(VERSION 3.16)
project(GraphAppProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "/opt/homebrew/opt/sfml@2/lib/cmake/SFML")

find_package(SFML 2 COMPONENTS graphics window system REQUIRED)

add_executable(GraphApp
    src/main.cpp
    src/GraphApp.cpp
    src/CoordinateSystem.cpp
    src/FunctionPlot.cpp
)

target_include_directories(GraphApp PRIVATE include)

target_link_libraries(GraphApp PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)
