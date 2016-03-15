
# cmake principal


cmake_minimum_required(VERSION 2.8)

project(RUSHHOUR)

add_definitions(-std=c99 -g -Wall)

set(CMAKE_INSTALL_PREFIX .)

include_directories(
	$(RUSHHOUR_SOURCE_DIR)/game/game
	$(RUSHHOUR_SOURCE_DIR)/game/piece)

enable_testing()

add_subdirectory(game)
add_subdirectory(rush_hour)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
