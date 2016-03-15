
# cmake de rush_hour


add_executable(rush_hour rush_hour.c)

target_link_libraries(rush_hour game)

install(TARGETS rush_hour RUNTIME DESTINATION ${RUSHHOUR_BINARY_DIR}/bin)



