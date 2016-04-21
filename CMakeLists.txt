
# cmake principal


cmake_minimum_required(VERSION 3.2)

project(RHARGAME)

add_definitions(-std=c99 -g -Wall)

set(CMAKE_INSTALL_PREFIX .)

include_directories($(RHARGAME_SOURCE_DIR)/include)

enable_testing()

add_subdirectory(src)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

