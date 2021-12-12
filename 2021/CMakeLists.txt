cmake_minimum_required (VERSION 3.12)


project("AdventOfCode_2021"
  VERSION 0.1.0
  DESCRIPTION "Advent of Code 2021"
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
)

#Source files
file( GLOB SOURCE_FILES
  #Manually add all source files here
  # General
  ${SOURCES_DIR}/main.cpp
  ${SOURCES_DIR}/utils.cpp
  # Day problems
  ${SOURCES_DIR}/sonar_sweep.cpp  
  ${SOURCES_DIR}/dive.cpp
  ${SOURCES_DIR}/binary_diagnostic.cpp
  ${SOURCES_DIR}/giant_squid.cpp
  ${SOURCES_DIR}/hydrothermal_venture.cpp
  ${SOURCES_DIR}/lanternfish.cpp
  ${SOURCES_DIR}/the_treachery_of_whales.cpp
  ${SOURCES_DIR}/seven_segment_search.cpp
  ${SOURCES_DIR}/smoke_basin.cpp
  ${SOURCES_DIR}/syntax_scoring.cpp
  ${SOURCES_DIR}/dumbo_octopus.cpp
  ${SOURCES_DIR}/passage_pathing.cpp
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
