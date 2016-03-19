#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "piece.h"

#define NB_PIECES 10

/**
 * @brief test if value is equal to expected; if not, displays an error message containing msg to standard error output 
 * @return true if expected==value
 */
bool test_equality_int(int expected, int value, char * msg) {
  if (expected != value)
    fprintf(stderr,"ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
  return expected == value;
}

/**
 * @brief test if value is equal to expected; if not, displays an error message containing msg to standard error output 
 */
bool test_equality_bool(bool expected, bool value, char * msg) {
  if (expected != value)
    fprintf(stderr,"ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
  return expected == value;
}

piece pieces[NB_PIECES];
/* configue de test ane rouge
1002
1002
3554
3674
8..9
 */

void set_up() {
  pieces[0] = new_piece(1, 3, 2, 2, true, true);
  pieces[1] = new_piece(0, 3, 1, 2, true, true);
  pieces[2] = new_piece(3, 3, 1, 2, true, true);
  pieces[3] = new_piece(0, 1, 1, 2, true, true);
  pieces[4] = new_piece(3, 1, 1, 2, true, true);
  pieces[5] = new_piece(1, 2, 2, 1, true, true);
  pieces[6] = new_piece(1, 1, 1, 1, true, true);
  pieces[7] = new_piece(2, 1, 1, 1, true, true);
  pieces[8] = new_piece(0, 0, 1, 1, true, true);
  pieces[9] = new_piece(3, 0, 1, 1, true, true);
}
void tear_down() {
  for (int i = 0 ; i < NB_PIECES; i++)
    delete_piece(pieces[i]);
}


bool test_copy_piece() {
  bool result = true;
  piece p = new_piece(0, 0, 0, 0, true, true);
  set_up();
  for (int i = 0; i < NB_PIECES; i++) {
    copy_piece(pieces[i], p);
    result = result && test_equality_int(get_x(pieces[i]), get_x(p), "test_copy_piece get_x");
    result = result && test_equality_int(get_y(pieces[i]), get_y(p), "test_copy_piece get_y");
    result = result && test_equality_int(get_width(pieces[i]), get_width(p), "test_copy_piece get_width");
    result = result && test_equality_int(get_height(pieces[i]), get_height(p), "test_copy_piece get_height");
    result = result && test_equality_int(can_move_x(pieces[i]), can_move_x(p), "test_copy_piece can_move_x");
    result = result && test_equality_int(can_move_y(pieces[i]), can_move_y(p), "test_copy_piece can_move_y");
  }
  tear_down();
  delete_piece(p);
  return result;
}


int main (int argc, char *argv[])
{
  bool result= true;

  result = result && test_equality_bool(true, test_copy_piece(), "copy_piece");

  if (result) {
    printf("Youpi !\n");
    return EXIT_SUCCESS;
  }
  else
    return EXIT_FAILURE;
}
