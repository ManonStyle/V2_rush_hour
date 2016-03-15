
# cmake de test_game1.c


add_executable(test_game test_game1.c game.c)

target_link_libraries(test_game game)

add_test(tg test_game)

set_tests_properties(tg PROPERTIES PASS_REGULAR_EXPRESSION "Youpi !")
