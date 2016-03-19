
# cmake de game


add_library (game piece.c game.c)
install(TARGETS game ARCHIVE DESTINATION ${RHARGAME_BINARY_DIR}/lib)

install(FILES piece.h game.h DESTINATION ${RHARGAME_BINARY_DIR}/include)

add_executable(rush_hour-ane_rouge-game main.c)
target_link_libraries(rush_hour-ane_rouge-game game)
install(TARGETS rush_hour-ane_rouge-game RUNTIME DESTINATION ${RHARGAME_BINARY_DIR}/bin)


# cmake test-piece

add_executable(test_piece-test_new_piece_rh test-piece/test_piece1.c piece.c)
target_link_libraries(test_piece-test_new_piece_rh game)
add_test(tp1-test_new_piece_rh test_piece-test_new_piece_rh)
set_tests_properties(tp1-test_new_piece_rh PROPERTIES PASS_REGULAR_EXPRESSION "Youpi !")
set_tests_properties (tp1-test_new_piece_rh PROPERTIES TIMEOUT 1)

add_executable(test_piece-test_new_piece test-piece/test_piece2.c piece.c)
target_link_libraries(test_piece-test_new_piece game)
add_test(tp2-test_new_piece test_piece-test_new_piece)
set_tests_properties(tp2-test_new_piece PROPERTIES PASS_REGULAR_EXPRESSION "Youpi !")
set_tests_properties (tp2-test_new_piece PROPERTIES TIMEOUT 1)

add_executable(test_piece-test_copy_piece test-piece/test_piece3.c piece.c)
target_link_libraries(test_piece-test_copy_piece game)
add_test(tp3-test_copy_piece test_piece-test_copy_piece)
set_tests_properties(tp3-test_copy_piece PROPERTIES PASS_REGULAR_EXPRESSION "Youpi !")
set_tests_properties (tp3-test_copy_piece PROPERTIES TIMEOUT 1)

add_executable(test_piece-test_intersect test-piece/test_piece4.c piece.c)
target_link_libraries(test_piece-test_intersect game)
add_test(tp4-test_intersect test_piece-test_intersect)
set_tests_properties(tp4-test_intersect PROPERTIES PASS_REGULAR_EXPRESSION "Youpi !")
set_tests_properties (tp4-test_intersect PROPERTIES TIMEOUT 1)

add_executable(test_piece-test_move_piece test-piece/test_piece5.c piece.c)
target_link_libraries(test_piece-test_move_piece game)
add_test(tp5-test_move_piece test_piece-test_move_piece)
set_tests_properties(tp5-test_move_piece PROPERTIES PASS_REGULAR_EXPRESSION "Youpi !")
set_tests_properties (tp5-test_move_piece PROPERTIES TIMEOUT 1)


# cmake test-game

add_executable(test_game-test_new_game_rh test-game/test_game1.c game.c)
target_link_libraries(test_game-test_new_game_rh game)
add_test(tg1-test_new_game_rh test_game-test_new_game_rh)
set_tests_properties(tg1-test_new_game_rh PROPERTIES PASS_REGULAR_EXPRESSION "Youpi !")
set_tests_properties (tg1-test_new_game_rh PROPERTIES TIMEOUT 1)

add_executable(test_game-test_new_game test-game/test_game2.c game.c)
target_link_libraries(test_game-test_new_game game)
add_test(tg2-test_new_game test_game-test_new_game)
set_tests_properties(tg2-test_new_game PROPERTIES PASS_REGULAR_EXPRESSION "Youpi !")
set_tests_properties (tg2-test_new_game PROPERTIES TIMEOUT 1)

add_executable(test_game-test_copy_game test-game/test_game3.c game.c)
target_link_libraries(test_game-test_copy_game game)
add_test(tg3-test_copy_game test_game-test_copy_game)
set_tests_properties(tg3-test_copy_game PROPERTIES PASS_REGULAR_EXPRESSION "Youpi !")
set_tests_properties (tg3-test_copy_game PROPERTIES TIMEOUT 1)

add_executable(test_game-test_play_move test-game/test_game4.c game.c)
target_link_libraries(test_game-test_play_move game)
add_test(tg4-test_play_move test_game-test_play_move)
set_tests_properties(tg4-test_play_move PROPERTIES PASS_REGULAR_EXPRESSION "Youpi !")
set_tests_properties (tg4-test_play_move PROPERTIES TIMEOUT 1)

add_executable(test_game-test_game_square_piece test-game/test_game5.c game.c)
target_link_libraries(test_game-test_game_square_piece game)
add_test(tg5-test_game_square_piece test_game-test_game_square_piece)
set_tests_properties(tg5-test_game_square_piece PROPERTIES PASS_REGULAR_EXPRESSION "Youpi !")
set_tests_properties (tg5-test_game_square_piece PROPERTIES TIMEOUT 1)












