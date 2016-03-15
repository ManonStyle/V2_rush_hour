
# cmake principal


cmake_minimum_required(VERSION 3.2)

project(JEU)

add_definitions(-std=c99 -g -Wall)

set(CMAKE_INSTALL_PREFIX .)

include_directories(
	$(JEU_SOURCE_DIR)/game/game
	$(JEU_SOURCE_DIR)/game/piece)

enable_testing()

add_subdirectory(game)
add_subdirectory(jeu)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
