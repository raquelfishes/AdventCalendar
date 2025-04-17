# Librería específica para el año 2023
set(YEAR_2023_SOURCES
    calendar/day01.cpp
    calendar/day02.cpp
)

# Crear la librería estática del año 2023
add_library(advent2023 STATIC ${YEAR_2023_SOURCES})

# Enlazar la librería "common" (se compila automáticamente si no está)
target_link_libraries(advent2023 PUBLIC common)

# Incluir el directorio de este año como cabecera pública
target_include_directories(advent2023 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
