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
set(AOC_DAY4 "${CMAKE_CURRENT_SOURCE_DIR}/day4/.")
set(AOC_DAY5 "${CMAKE_CURRENT_SOURCE_DIR}/day5/.")
set(AOC_DAY6 "${CMAKE_CURRENT_SOURCE_DIR}/day6/.")
set(AOC_DAY7 "${CMAKE_CURRENT_SOURCE_DIR}/day7/.")
set(AOC_DAY8 "${CMAKE_CURRENT_SOURCE_DIR}/day8/.")
set(AOC_DAY9 "${CMAKE_CURRENT_SOURCE_DIR}/day9/.")
set(AOC_DAY10 "${CMAKE_CURRENT_SOURCE_DIR}/day10/.")
set(AOC_DAY11 "${CMAKE_CURRENT_SOURCE_DIR}/day11/.")


add_subdirectory(${AOC_DAY1})
add_subdirectory(${AOC_DAY2})
add_subdirectory(${AOC_DAY3})
add_subdirectory(${AOC_DAY4})
add_subdirectory(${AOC_DAY5})
add_subdirectory(${AOC_DAY6})
add_subdirectory(${AOC_DAY7})
add_subdirectory(${AOC_DAY8})
add_subdirectory(${AOC_DAY9})
add_subdirectory(${AOC_DAY10})
add_subdirectory(${AOC_DAY11})
