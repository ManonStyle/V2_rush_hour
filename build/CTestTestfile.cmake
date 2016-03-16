# CMake generated Testfile for 
# Source directory: /home/gg/Bureau/projet/v2_rush_hour
# Build directory: /home/gg/Bureau/projet/v2_rush_hour/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(tp "test_piece")
set_tests_properties(tp PROPERTIES  PASS_REGULAR_EXPRESSION "Youpi !")
add_test(tg "test_game")
set_tests_properties(tg PROPERTIES  PASS_REGULAR_EXPRESSION "Youpi !")
