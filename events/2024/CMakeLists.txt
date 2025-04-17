# Librería específica para el año 2024
set(YEAR_2024_SOURCES
    calendar/day01.cpp
    calendar/day02.cpp
)

# Crear la librería estática del año 2024
add_library(advent2024 STATIC ${YEAR_2024_SOURCES})

# Enlazar la librería "common" (se compila automáticamente si no está)
target_link_libraries(advent2024 PUBLIC common)

# Incluir el directorio de este año como cabecera pública
target_include_directories(advent2024 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
