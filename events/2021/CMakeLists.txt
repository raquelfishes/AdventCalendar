# Librería específica para el año 2021
set(YEAR_2021_SOURCES
    calendar/day01.cpp
)

# Crear la librería estática del año 2021
add_library(advent2021 STATIC ${YEAR_2021_SOURCES})

# Incluir headers de "common"
target_include_directories(advent2021 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../common)

# Enlazar la librería "common"
target_link_libraries(advent2021 PUBLIC common)
