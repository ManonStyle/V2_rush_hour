
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

add_executable(test-game test-game/test_game1.c game.c)
target_link_libraries(test-game game)
add_test(tg test-game)
set_tests_properties(tg PROPERTIES PASS_REGULAR_EXPRESSION "Youpi !")
set_tests_properties (tg PROPERTIES TIMEOUT 1)
