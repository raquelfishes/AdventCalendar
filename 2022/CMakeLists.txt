cmake_minimum_required (VERSION 3.12)


project("AdventOfCode_2022"
  VERSION 0.1.0
  DESCRIPTION "Advent of Code 2022"
  LANGUAGES C CXX)

set(TARGET_NAME AoC)

# Set minimum c++ version
set(CMAKE_CXX_STANDARD 20)


################
# Sources
################

#Headers and source directories
set( SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src )
set( INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )

#Header files                       
include_directories( ${INCLUDE_DIR} )
file( GLOB HEADER_FILES
  #Manually add all header files here    
  # General
  ${INCLUDE_DIR}/utils.h
  ${INCLUDE_DIR}/ansi_colors.h
  # Day problems
  ${INCLUDE_DIR}/adventdays_fwd.h
  ${INCLUDE_DIR}/sonar_sweep.h
  ${INCLUDE_DIR}/dive.h
  ${INCLUDE_DIR}/grid.h
  ${INCLUDE_DIR}/vector2.h
)

#Source files
file( GLOB SOURCE_FILES
  #Manually add all source files here
  # General
  ${SOURCES_DIR}/main.cpp
  ${SOURCES_DIR}/utils.cpp
  ${SOURCES_DIR}/vector2.cpp
  # Day problems
  ${SOURCES_DIR}/day1.cpp  
  ${SOURCES_DIR}/day2.cpp
  ${SOURCES_DIR}/day3.cpp
  ${SOURCES_DIR}/day4.cpp
  ${SOURCES_DIR}/day5.cpp
  ${SOURCES_DIR}/day6.cpp
  ${SOURCES_DIR}/day7.cpp
  ${SOURCES_DIR}/day8.cpp
  ${SOURCES_DIR}/day9.cpp
  ${SOURCES_DIR}/day10.cpp
  ${SOURCES_DIR}/day11.cpp
  ${SOURCES_DIR}/day12.cpp
  ${SOURCES_DIR}/day13.cpp
  ${SOURCES_DIR}/day14.cpp
  ${SOURCES_DIR}/day15.cpp
  ${SOURCES_DIR}/day16.cpp
  ${SOURCES_DIR}/day17.cpp
  ${SOURCES_DIR}/day18.cpp
  ${SOURCES_DIR}/day19.cpp  
  ${SOURCES_DIR}/day20.cpp  
  ${SOURCES_DIR}/day21.cpp  
  ${SOURCES_DIR}/day22.cpp  
  ${SOURCES_DIR}/day23.cpp  
  ${SOURCES_DIR}/day24.cpp  
  ${SOURCES_DIR}/day25.cpp
)


########
#Resource file
########
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/resource.h.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/resource.h"
)

list( APPEND GENERATED_FILES 
  ${CMAKE_CURRENT_SOURCE_DIR}/include/resource.h
)


###################
#Create executable
###################

#add_library(add ${SOURCES} ${INCLUDES})

add_executable( ${TARGET_NAME} ${GENERATED_FILES} ${HEADER_FILES} ${SOURCE_FILES} )

#target_link_libraries(${TARGET_NAME} add)

#add_subdirectory( tests )
