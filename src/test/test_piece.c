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



// test unitaire


// 1 - test_new_piece_rh

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


// 2 - test_new_piece

bool test_new_piece() {
  bool result = true;
  for (int x = 0; x < 5; x++)
    for (int y = 0; y < 5; y++)
      for (int width = 1; width < 5 ; width++)
	for (int height = 1; height < 5; height++)
	  for (bool move_x = false; !move_x; move_x = !move_x)
	    for (bool move_y = false; !move_y; move_y = !move_y){
	      piece p = new_piece(x, y, width, height, move_x, move_y);
	      result = result && test_equality_int(x, get_x(p), "test_new_piece get_x");
	      result = result && test_equality_int(y, get_y(p), "test_new_piece get_y");
	      result = result && test_equality_int(width, get_width(p), "test_new_piece get_width");
	      result = result && test_equality_int(height, get_height(p), "test_new_piece get_height");
	      result = result && test_equality_int(move_x, can_move_x(p), "test_new_piece can_move_x");
	      result = result && test_equality_int(move_y, can_move_y(p), "test_new_piece can_move_y");
	      delete_piece(p);
	    }
  return result;
}


// 3 - test_copy_piece

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


// 4 - test_intersect

bool test_intersect() {
  bool result = true;
  set_up();
  for (int i = 0; i < NB_PIECES; i++)
    for (int j = 0; j < NB_PIECES; j++) {
      result = result && test_equality_bool (i == j, intersect(pieces[i], pieces[j]), "intersect");
    }
  piece pb_piece = new_piece(1, 0, 3, 1, true, true);
  result = result && test_equality_bool(true, intersect(pieces[9], pb_piece), "intersect pb 1");
  result = result && test_equality_bool(false, intersect(pieces[8], pb_piece), "intersect pb 2");
  delete_piece(pb_piece);
  tear_down();
  return result;
}


// 5 - test_move_piece

bool test_move_piece() {
  bool result = true;
  piece p = new_piece(0, 0, 0, 0, true, true);
  set_up();
  for (int dist = 1; dist < NB_PIECES; dist++)
    for (int i = 0; i < NB_PIECES; i++) {
      copy_piece(pieces[i], p);
      move_piece(p, LEFT, dist);
      if (can_move_x(pieces[i]))
	result = result && test_equality_int(get_x(pieces[i])-dist, get_x(p), "move LEFT");
      else
	result = result && test_equality_int(get_x(pieces[i]), get_x(p), "move LEFT");
      copy_piece(pieces[i], p);
      move_piece(p, RIGHT, dist);
      if (can_move_x(pieces[i]))
	result = result && test_equality_int(get_x(pieces[i])+dist, get_x(p), "move RIGHT");
      else
	result = result && test_equality_int(get_x(pieces[i]), get_x(p), "move RIGHT");
      copy_piece(pieces[i], p);
      move_piece(p, UP, dist);
      if (can_move_y(pieces[i]))
	result = result && test_equality_int(get_y(pieces[i])+dist, get_y(p), "move UP");
      else
	result = result && test_equality_int(get_y(pieces[i]), get_y(p), "move UP");
      copy_piece(pieces[i], p);
      move_piece(p, DOWN, dist);
      if (can_move_y(pieces[i]))
	result = result && test_equality_int(get_y(pieces[i])-dist, get_y(p), "move DOWN");
      else
	result = result && test_equality_int(get_y(pieces[i]), get_y(p), "move DOWN");
    }
  tear_down();
  delete_piece(p);
  return result;
}


// main

int main (int argc, char *argv[])
{
  bool result= true;

  result = result && test_equality_bool(true, test_new_piece_rh(), "new_piece_rh");
  result = result && test_equality_bool(true, test_new_piece(), "new_piece");
  result = result && test_equality_bool(true, test_copy_piece(), "copy_piece");
  result = result && test_equality_bool(true, test_intersect(), "intersect");
  result = result && test_equality_bool(true, test_move_piece(), "move_piece");

  if (result) {
    printf("Youpi !\n");
    return EXIT_SUCCESS;
  }
  else
    return EXIT_FAILURE;
}
