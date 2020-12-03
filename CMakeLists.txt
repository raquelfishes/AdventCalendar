cmake_minimum_required (VERSION 3.12)

project(AdventCalendar
VERSION 1.0.0
DESCRIPTION "AdventOfCode 2020"
LANGUAGES C CXX)

# Set minimum c++ version
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/build")

# Setting per day folders
set(AOC_DAY1 "${CMAKE_CURRENT_SOURCE_DIR}/day1/.")
set(AOC_DAY2 "${CMAKE_CURRENT_SOURCE_DIR}/day2/.")
set(AOC_DAY3 "${CMAKE_CURRENT_SOURCE_DIR}/day3/.")


add_subdirectory(${AOC_DAY1})
add_subdirectory(${AOC_DAY2})
add_subdirectory(${AOC_DAY3})
