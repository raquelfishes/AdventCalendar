# Librería específica para el año 2020
set(YEAR_2020_SOURCES
    calendar/day01.cpp
    calendar/day02.cpp
    calendar/day03.cpp
    calendar/day04.cpp
    calendar/day05.cpp
    calendar/day06.cpp
    calendar/day07.cpp
    calendar/day08.cpp
    calendar/day09.cpp
    calendar/day10.cpp
    calendar/day11.cpp
    calendar/day12.cpp
    calendar/day13.cpp
    calendar/day14.cpp
    calendar/day15.cpp
    calendar/day16.cpp
    calendar/day17.cpp
    calendar/day18.cpp
    calendar/day19.cpp
    calendar/day20.cpp
    calendar/day21.cpp
    calendar/day22.cpp
    calendar/day23.cpp
    calendar/day24.cpp
    calendar/day25.cpp
)

# Crear la librería estática del año 2020
add_library(advent2020 STATIC ${YEAR_2020_SOURCES})

# Incluir headers de "common"
target_include_directories(advent2020 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../common)

# Enlazar la librería "common"
target_link_libraries(advent2020 PUBLIC common)
