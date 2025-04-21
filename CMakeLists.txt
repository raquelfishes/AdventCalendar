# Versión mínima requerida de CMake
cmake_minimum_required(VERSION 3.12)

# Nombre del proyecto
project(AdventOfCode VERSION 1.0.0 LANGUAGES CXX)

# Establecer el estándar de C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)  # Necesario para IntelliSense en VS Code

# ---- Librería "common" ----
add_library(common STATIC
    common/resources.cpp
    common/utils_2021.cpp
    common/string_utils.cpp
)

# Agregar las rutas necesarias para "common"
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/common)

# ---- Subdirectorios por año ----
add_subdirectory(events/2024)
add_subdirectory(events/2023)
add_subdirectory(events/2022)
add_subdirectory(events/2021)
add_subdirectory(events/2020)

# ---- Ejecutable principal ----
add_executable(${PROJECT_NAME} executable/main.cpp)

# Vincular librerías al ejecutable principal
target_link_libraries(${PROJECT_NAME}
    advent2024
    advent2023
    advent2022
    advent2021
    advent2020
    common
)

# Asegurar que el ejecutable puede incluir "common"
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/common)
