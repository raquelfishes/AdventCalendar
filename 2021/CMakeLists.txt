cmake_minimum_required (VERSION 3.12)


project("AdventOfCode_2021"
  VERSION 0.1.0
  DESCRIPTION "Advent of Code 2021"
  LANGUAGES C CXX)

set(TARGET_NAME AoC)

# Set minimum c++ version
set(CMAKE_CXX_STANDARD 14)


################
# Sources
################

#Headers and source directories
set( SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src )
set( INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )

#Header files                       
include_directories( ${INCLUDE_DIR} )

#Source files
file( GLOB SOURCE_FILES
  #Manually add all source files here
  #Day problems
  ${SOURCES_DIR}/sonar_sweep.cpp  
  #Main
  ${SOURCES_DIR}/main.cpp
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

add_executable( ${TARGET_NAME} ${SOURCE_FILES} ${GENERATED_FILES} )
