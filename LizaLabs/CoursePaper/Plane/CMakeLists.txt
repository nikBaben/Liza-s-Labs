cmake_minimum_required(VERSION 3.16)
project(PlaneAppProject LANGUAGES CXX)

# C++17 для SFML 2.6
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подсказать CMake, где лежит sfml@2 из brew
# (если путь другой — подставь вывод команды: brew --prefix sfml@2)
set(SFML_DIR "/opt/homebrew/opt/sfml@2/lib/cmake/SFML")

# Ищем SFML 2.x и нужные модули
find_package(SFML 2 COMPONENTS graphics window system REQUIRED)

# Исполняемый файл с нашими исходниками
add_executable(PlaneApp
    src/main.cpp
    src/Plane.cpp
    src/Scene.cpp
    src/PlaneApp.cpp
)

# Подключаем заголовки из include/
target_include_directories(PlaneApp PRIVATE include)

# Линкуем SFML
target_link_libraries(PlaneApp PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)
