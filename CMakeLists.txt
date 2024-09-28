cmake_minimum_required(VERSION 3.28)
project(Proyecto2_TankAttack)

set(CMAKE_CXX_STANDARD 17)

# Busca los módulos necesarios de Qt (Widgets y Charts)
find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

# Incluye los directorios de Qt necesarios
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5Charts_INCLUDE_DIRS})

add_executable(Proyecto2_TankAttack main.cpp)

# Enlazar las bibliotecas de Qt
target_link_libraries(Proyecto2_TankAttack Qt5::Charts)