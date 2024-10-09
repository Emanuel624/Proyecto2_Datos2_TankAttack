cmake_minimum_required(VERSION 3.28)
project(Proyecto2_TankAttack)

# Estándar de C++ 17
set(CMAKE_CXX_STANDARD 17)

# Activa el automoc para que CMake procese los archivos con Qt MOC automáticamente
set(CMAKE_AUTOMOC ON)

# Busca los módulos necesarios de Qt6 (Widgets y Charts)
find_package(Qt6 COMPONENTS Widgets Charts REQUIRED)

# Agrega el ejecutable del proyecto
add_executable(Proyecto2_TankAttack main.cpp
        GridGraph.cpp
        Tank.cpp
        Player.cpp
        PowerUp.cpp
        PowerUpQueue.cpp)

# Enlazar las bibliotecas de Qt6
target_link_libraries(Proyecto2_TankAttack Qt6::Widgets Qt6::Charts)
