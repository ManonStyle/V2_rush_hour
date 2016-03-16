
# cmake de test_piece1.c


add_executable(test_piece test_piece1.c piece.c)

target_link_libraries(test_piece game)

add_test(tp test_piece)

set_tests_properties(tp PROPERTIES PASS_REGULAR_EXPRESSION "Youpi !")
