cmake_minimum_required(VERSION 3.28)
project(Proyecto2_TankAttack)
set(CMAKE_PREFIX_PATH "C:/Qt/6.7.2/mingw_64/lib/cmake")

set(CMAKE_CXX_STANDARD 17)

# Busca los módulos necesarios de Qt (Widgets y Charts)
find_package(Qt6 COMPONENTS Widgets Charts REQUIRED)

# Incluye los directorios de Qt necesarios
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5Charts_INCLUDE_DIRS})
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(Proyecto2_TankAttack main.cpp
        main.cpp)

# Enlazar las bibliotecas de Qt
target_link_libraries(Proyecto2_TankAttack Qt6::Widgets Qt6::Charts)