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


bool test_new_piece_rh() {
  bool result = true;
  for (int x = 0 ; x < 5; x++)
    for (int y = 0 ; y < 5; y++)
      for (bool small = false; !small; small = !small)
        for (bool horizontal = false; !horizontal; horizontal = !horizontal) {
          int size;
          if (small)
            size = 2;
          else
            size = 3;
          piece p = new_piece_rh(x, y, small, horizontal);
          result = result && test_equality_int(x, get_x(p),"new_piece_rh get_x");
          result = result && test_equality_int(y, get_y(p),"new_piece_rh get_y");
          if (horizontal) {
            result = result && test_equality_int(1, get_height(p), "new_piece_rh get_height");
            result = result && test_equality_int(size, get_width(p), "new_piece_rh get_width");
	    result = result && test_equality_bool(true, can_move_x(p), "new_piece_rh can_move_x");
	    result = result && test_equality_bool(false, can_move_y(p), "new_piece_rh can_move_y");
          }
          else {
            result = result && test_equality_int(size, get_height(p), "new_piece_rh get_height");
            result = result && test_equality_int(1, get_width(p), "new_piece_rh get_width");
	    result = result && test_equality_bool(false, can_move_x(p), "new_piece_rh can_move_x");
	    result = result && test_equality_bool(true, can_move_y(p), "new_piece_rh can_move_y");
          }
          delete_piece(p);
        }
  return result;
}


int main (int argc, char *argv[])
{
  bool result= true;

  result = result && test_equality_bool(true, test_new_piece_rh(), "new_piece_rh");

  if (result) {
    printf("Youpi !\n");
    return EXIT_SUCCESS;
  }
  else
    return EXIT_FAILURE;
}
