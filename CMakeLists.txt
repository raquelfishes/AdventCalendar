cmake_minimum_required (VERSION 3.12)

project("AdventOfCode"
VERSION 1.0.0
DESCRIPTION "AdventOfCode"
LANGUAGES C CXX)

set(TARGET_NAME AoC)

# Set minimum c++ version
set(CMAKE_CXX_STANDARD 20)

################
# Sources
################

#Headers and source directories
set( COMMON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/common )

#Header files                       
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/common
                     ${CMAKE_CURRENT_SOURCE_DIR}/events/2024
                     ${CMAKE_CURRENT_SOURCE_DIR}/events/2023
)

# Archivos específicos de cada año
set(YEAR_2024_SOURCES
    events/2024/design.h
    events/2024/calendar/day01.cpp
)

# Archivos específicos de cada año
set(YEAR_2023_SOURCES
    events/2023/design.h
    events/2023/calendar/day01.cpp
)

#Source files
file( GLOB SOURCE_FILES
  #Manually add all source files here
  # General
  ${CMAKE_CURRENT_SOURCE_DIR}/executable/main.cpp
)


###################
#Create executable
###################


add_executable( ${TARGET_NAME} ${GENERATED_FILES} ${YEAR_2024_SOURCES} ${YEAR_2023_SOURCES} ${SOURCE_FILES} )


# Organizar la estructura de carpetas en Visual Studio
source_group("common" FILES ${COMMON_SOURCES})
source_group("events\\2024" FILES ${YEAR_2024_SOURCES})
source_group("events\\2023" FILES ${YEAR_2023_SOURCES})
source_group("executable" FILES executable/main.cpp)


##  
##  # Versión mínima requerida de CMake
##  cmake_minimum_required(VERSION 3.10)
##  
##  # Nombre del proyecto
##  project(AdventOfCode)
##  
##  # Establecer el estándar de C++ (por ejemplo, C++17)
##  set(CMAKE_CXX_STANDARD 17)
##  set(CMAKE_CXX_STANDARD_REQUIRED True)
##  
##  # Incluir carpetas de cabeceras
##  include_directories(
##      ${PROJECT_SOURCE_DIR}/common
##      ${PROJECT_SOURCE_DIR}/events/2024
##      ${PROJECT_SOURCE_DIR}/events/2023
##  )
##  
##  # Archivos comunes (utilidades compartidas)
##  set(COMMON_SOURCES
##      common/utils.cpp
##  )
##  
##  # Archivos específicos de cada año
##  set(YEAR_2024_SOURCES
##      events/2024/calendar/day1.cpp
##      events/2024/calendar/day2.cpp
##  )
##  
##  set(YEAR_2023_SOURCES
##      events/2023/calendar/day1.cpp
##      events/2023/calendar/day2.cpp
##  )
##  
##  # Ejecutable principal
##  add_executable(advent_of_code
##      executable/main.cpp
##      ${COMMON_SOURCES}
##      ${YEAR_2024_SOURCES}
##      ${YEAR_2023_SOURCES}
##  )
##  
##  # Configurar Google Test
##  include(FetchContent)
##  FetchContent_Declare(
##      googletest
##      GIT_REPOSITORY https://github.com/google/googletest.git
##      GIT_TAG release-1.12.1
##  )
##  FetchContent_MakeAvailable(googletest)
##  
##  # Crear un objetivo para las pruebas de 2024
##  set(TEST_2024_SOURCES
##      events/2024/tests/test_day1.cpp
##      events/2024/tests/test_day2.cpp
##  )
##  
##  add_executable(tests_2024
##      ${TEST_2024_SOURCES}
##      ${YEAR_2024_SOURCES}
##      ${COMMON_SOURCES}
##  )
##  target_link_libraries(tests_2024 gtest gtest_main)
##  
##  # Crear un objetivo para las pruebas de 2023
##  set(TEST_2023_SOURCES
##      events/2023/tests/test_day1.cpp
##      events/2023/tests/test_day2.cpp
##  )
##  
##  add_executable(tests_2023
##      ${TEST_2023_SOURCES}
##      ${YEAR_2023_SOURCES}
##      ${COMMON_SOURCES}
##  )
##  target_link_libraries(tests_2023 gtest gtest_main)
##  
##  # Si necesitas enlazar bibliotecas externas
##  # find_package(BibliotecaRequerida REQUIRED)
##  # target_link_libraries(advent_of_code BibliotecaRequerida::BibliotecaRequerida)
