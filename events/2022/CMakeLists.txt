# Librería específica para el año 2022
set(YEAR_2022_SOURCES
    calendar/day01.cpp
)

# Crear la librería estática del año 2022
add_library(advent2022 STATIC ${YEAR_2022_SOURCES})

# Enlazar la librería "common" (se compila automáticamente si no está)
target_link_libraries(advent2022 PUBLIC common)

# Incluir el directorio de este año como cabecera pública
target_include_directories(advent2022 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
