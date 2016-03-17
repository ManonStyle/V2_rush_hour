
# cmake principal


cmake_minimum_required(VERSION 2.8)

project(JEU)

add_definitions(-std=c99 -g -Wall)

set(CMAKE_INSTALL_PREFIX .)


add_library (game piece.c game.c)
install(TARGETS game ARCHIVE DESTINATION ${JEU_BINARY_DIR}/lib)
install(FILES piece.h game.h DESTINATION ${JEU_BINARY_DIR}/include)

add_executable(jeu main.c)
target_link_libraries(jeu game)
install(TARGETS jeu RUNTIME DESTINATION ${JEU_SOURCE_DIR})

enable_testing()

# cmake de test_piece1.c
add_executable(test_piece test_piece1.c piece.c)
target_link_libraries(test_piece game)
install(TARGETS test_piece RUNTIME DESTINATION ${JEU_SOURCE_DIR})
add_test(tp test_piece)
set_tests_properties(tp PROPERTIES PASS_REGULAR_EXPRESSION "Youpi !")

# cmake de test_game1.c
add_executable(test_game test_game1.c game.c)
target_link_libraries(test_game game)
install(TARGETS test_game RUNTIME DESTINATION ${JEU_SOURCE_DIR})
add_test(tg test_game)
set_tests_properties(tg PROPERTIES PASS_REGULAR_EXPRESSION "Youpi !")

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
