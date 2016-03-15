
# cmake de main


add_executable(jeu main.c)

target_link_libraries(jeu game)

install(TARGETS jeu RUNTIME DESTINATION ${JEU_BINARY_DIR}/bin)

install(FILES game_rh.txt DESTINATION ${JEU_BINARY_DIR}/bin)
