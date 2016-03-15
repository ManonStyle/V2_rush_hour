
# cmake de game


add_library (game piece/piece.c game/game.c)

install(TARGETS game ARCHIVE DESTINATION ${RUSHHOUR_BINARY_DIR}/lib)

install(FILES piece/piece.h game/game.h DESTINATION ${RUSHHOUR_BINARY_DIR}/include)

add_subdirectory(game)
add_subdirectory(piece)
