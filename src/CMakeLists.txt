
# cmake de game


add_library (game piece.c game.c)
install(TARGETS game ARCHIVE DESTINATION ${RHARGAME_BINARY_DIR}/lib)

add_executable(jeu main.c)
target_link_libraries(jeu game)
install(TARGETS jeu RUNTIME DESTINATION ${RHARGAME_BINARY_DIR}/bin)


# cmake solveur

add_executable(solveur solveur/solveur.c solveur/file.c solveur/tree.c solveur/hash.c game.c piece.c)


# cmake test-piece

add_executable(test_piece test/test_piece.c piece.c)
target_link_libraries(test_piece game)
add_test(test_piece test_piece)
set_tests_properties(test_piece PROPERTIES PASS_REGULAR_EXPRESSION "Youpi !")
set_tests_properties (test_piece PROPERTIES TIMEOUT 1)


# cmake test-game

add_executable(test_game test/test_game.c game.c)
target_link_libraries(test_game game)
add_test(test_game test_game)
set_tests_properties(test_game PROPERTIES PASS_REGULAR_EXPRESSION "Youpi !")
set_tests_properties (test_game PROPERTIES TIMEOUT 1)













