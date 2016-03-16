
# cmake de game


add_library (game piece/piece.c game/game.c)

install(TARGETS game ARCHIVE DESTINATION ${JEU_BINARY_DIR}/lib)

install(FILES piece/piece.h game/game.h DESTINATION ${JEU_BINARY_DIR}/include)

add_subdirectory(game)
add_subdirectory(piece)
