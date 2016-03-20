#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "piece.h"
#include "game.h"

#define NB_PIECES 5
#define WIDTH 6
#define HEIGHT 5

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

piece pieces[NB_PIECES+1];
/* configue de test rh
......
....2.
00..21
..4.21
..4.33
......
 */

void set_up_rh() {
  pieces[0] = new_piece_rh(0, 3, true, true);
  pieces[1] = new_piece_rh(5, 2, true, false);
  pieces[2] = new_piece_rh(4, 2, false, false);
  pieces[3] = new_piece_rh(4, 1, true, true);
  pieces[4] = new_piece_rh(2, 1, true, false);
  pieces[5] = new_piece_rh(4, 3, true, true);
}

void tear_down_rh() {
  for (int i = 0 ; i < NB_PIECES+1; i++)
    delete_piece(pieces[i]);
}

piece piecesBis[NB_PIECES+1];
/* configue de test Bis 
4.....
...11.
.00...
.00...
2....3
 */

void set_up_Bis() {
  piecesBis[0] = new_piece(1, 1, 2, 2, true, true);
  piecesBis[1] = new_piece(3, 3, 2, 1, true, true);
  piecesBis[2] = new_piece(0, 0, 1, 1, true, false);
  piecesBis[3] = new_piece(5, 0, 1, 1, false, true);
  piecesBis[4] = new_piece(0, 4, 1, 1, true, true);
  piecesBis[5] = new_piece(2, 0, 2, 2, true, true);
}

void tear_down_Bis() {
  for (int i = 0 ; i < NB_PIECES+1; i++)
    delete_piece(piecesBis[i]);
}



bool test_play_move(){
  bool result = true;
  set_up_Bis();
  game g = new_game(WIDTH, HEIGHT, NB_PIECES, piecesBis);
  result = result && test_equality_bool(false, game_over_hr(g), "play_move game_over_hr false");
  result = result && test_equality_bool(true, play_move(g, 1, LEFT, 3), "play_move LEFT true");
  result = result && test_equality_bool(false, play_move(g, 1, LEFT, 1), "play_move LEFT false");
  result = result && test_equality_bool(true, play_move(g, 1, RIGHT, 4), "play_move RIGHT true");
  result = result && test_equality_bool(false, play_move(g, 1, RIGHT, 1), "play_move RIGHT false");
  result = result && test_equality_bool(true, play_move(g, 0, UP, 2), "play_move UP true");
  result = result && test_equality_bool(false, play_move(g, 0, UP, 1), "play_move UP false");
  result = result && test_equality_bool(true, play_move(g, 0, DOWN, 3), "play_move DOWN true");
  result = result && test_equality_bool(false, play_move(g, 0, DOWN, 1), "play_move DOWN false");
  play_move(g, 0, RIGHT, 1);
  result = result && test_equality_bool(true, game_over_hr(g), "play_move game_over_hr true");
  result = result && test_equality_bool(false, play_move(g, 3, LEFT, 1), "play_move_x !can_move_x LEFT");
  result = result && test_equality_bool(false, play_move(g, 3, RIGHT, 1), "play_move_x !can_move_x RIGHT");
  result = result && test_equality_bool(false, play_move(g, 2, UP, 1), "play_move !can_move_y UP");
  result = result && test_equality_bool(false, play_move(g, 2, DOWN, 1), "play_move !can_move_y DOWN");
  result = result && test_equality_bool(false, play_move(g, 4, DOWN, 4), "play_move DOWN intersect");
  delete_game(g);
  tear_down_Bis();
  return result;
}



int main (int argc, char *argv[]){
  bool result = true;

  result = result && test_equality_bool(true, test_play_move(), "play_move");

  if (result) {
    printf("Youpi !\n");
    return EXIT_SUCCESS;
   }
  else
    return EXIT_FAILURE;
 }
