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

// TU

// 1

bool test_new_game_rh() {
  bool result = true;
  set_up_rh();
  game g = new_game_hr(NB_PIECES, pieces);
  result = result && test_equality_int(6, game_width(g), "new_game_rh game_width");
  result = result && test_equality_int(6, game_height(g), "new_game_rh game_height");
  result = result && test_equality_int(NB_PIECES, game_nb_pieces(g), "new_game_rh game_nb_pieces");
  result = result && test_equality_int(0, game_nb_moves(g), "new_game_rh game_nb_moves");
  for (int i = 0; i < NB_PIECES; i++){
    result = result && test_equality_int(get_x(pieces[i]), get_x(game_piece(g, i)), "new_game_rh get_x");
    result = result && test_equality_int(get_y(pieces[i]), get_y(game_piece(g, i)), "new_game_rh get_y");
    result = result && test_equality_int(get_height(pieces[i]), get_height(game_piece(g, i)), "new_game_rh get_height");
    result = result && test_equality_int(get_width(pieces[i]), get_width(game_piece(g, i)), "new_game_rh get_width");
    result = result && test_equality_bool(can_move_x(pieces[i]), can_move_x(game_piece(g, i)), "new_game_rh can_move_x");
    result = result && test_equality_bool(can_move_y(pieces[i]), can_move_y(game_piece(g, i)), "new_game_rh can_move_y");
    }
  tear_down_rh();
  delete_game(g);
  return result; 
  }

// 2

bool test_new_game() {
  bool result = true;
  set_up_Bis();
  game g = new_game(WIDTH, HEIGHT, NB_PIECES, piecesBis);
  result = result && test_equality_int(WIDTH, game_width(g), "new_game game_width");
  result = result && test_equality_int(HEIGHT, game_height(g), "new_game game_height");
  result = result && test_equality_int(NB_PIECES, game_nb_pieces(g), "new_game game_nb_pieces");
  result = result && test_equality_int(0, game_nb_moves(g), "new_game game_nb_moves");
  for (int i = 0; i < NB_PIECES; i++){
    result = result && test_equality_int(get_x(piecesBis[i]), get_x(game_piece(g, i)), "new_game get_x");
    result = result && test_equality_int(get_y(piecesBis[i]), get_y(game_piece(g, i)), "new_game get_y");
    result = result && test_equality_int(get_height(piecesBis[i]), get_height(game_piece(g, i)), "new_game get_height");
    result = result && test_equality_int(get_width(piecesBis[i]), get_width(game_piece(g, i)), "new_game get_width");
    result = result && test_equality_bool(can_move_x(piecesBis[i]), can_move_x(game_piece(g, i)), "new_game can_move_x");
    result = result && test_equality_bool(can_move_y(piecesBis[i]), can_move_y(game_piece(g, i)), "new_game can_move_y");
  }
  delete_game(g);
  tear_down_Bis();
  return result; 
}

// 3

bool test_copy_game() {
  bool result = true;
  set_up_Bis();
  game g = new_game(WIDTH, HEIGHT, NB_PIECES, piecesBis);
  set_up_rh();
  game gC = new_game(1, 1, NB_PIECES, pieces);
  copy_game(g, gC);
  result = result && test_equality_int(game_width(g), game_width(gC), "copy_game game_width");
  result = result && test_equality_int(game_height(g), game_height(gC), "copy_game game_height");
  result = result && test_equality_int(game_nb_pieces(g), game_nb_pieces(gC), "copy_game game_nb_pieces");
  result = result && test_equality_int(game_nb_moves(g), game_nb_moves(gC), "copy_game game_nb_moves");
  for (int i = 0; i < NB_PIECES; i++){
    result = result && test_equality_int(get_x(game_piece(g, i)), get_x(game_piece(gC, i)), "copy_game get_x");
    result = result && test_equality_int(get_y(game_piece(g, i)), get_y(game_piece(gC, i)), "copy_game get_y");
    result = result && test_equality_int(get_height(game_piece(g, i)), get_height(game_piece(gC, i)), "copy_game get_height");
    result = result && test_equality_int(get_width(game_piece(g, i)), get_width(game_piece(gC, i)), "copy_game get_width");
    result = result && test_equality_bool(can_move_x(game_piece(g, i)), can_move_x(game_piece(gC, i)), "copy_game can_move_x");
    result = result && test_equality_bool(can_move_y(game_piece(g, i)), can_move_y(game_piece(gC, i)), "copy_game can_move_y");
    }
  delete_game(g);
  delete_game(gC);
  tear_down_Bis();
  tear_down_rh();
  return result;
}
void fillArrayWithPieces();

// 4

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


// 5

int piecesNum[WIDTH][HEIGHT];

void fillArrayWithPieces(){
  for(int x = 0; x < WIDTH; ++x){
    for(int y = 0; y < HEIGHT; ++y){
      piecesNum[x][y] = -1;
    }
  }
  for(int p = 0; p < NB_PIECES; ++p){
    for(int x = get_x(piecesBis[p]); x < get_x(piecesBis[p]) + get_width(piecesBis[p]); ++x){
      for(int y = get_y(piecesBis[p]); y < get_y(piecesBis[p]) + get_height(piecesBis[p]); ++y){
	piecesNum[x][y] = p;
      }
    }
  }
}

// 6

bool test_game_square_piece(){
  bool result = true;
  set_up_Bis();
  game g = new_game(WIDTH, HEIGHT, NB_PIECES, piecesBis);
  fillArrayWithPieces();
  for(int x = 0; x < WIDTH; x++){
    for(int y = 0; y < HEIGHT; y++){
      result = result && test_equality_int(piecesNum[x][y], game_square_piece(g, x, y), "game_square_piece");
    }
  }
  tear_down_Bis();
  delete_game(g);
  return result;
}




int main (int argc, char *argv[]){
  bool result = true;

  result = result && test_equality_bool(true, test_new_game_rh(), "new_game_rh");
  result = result && test_equality_bool(true, test_new_game(), "new_game");
  result = result && test_equality_bool(true, test_copy_game(), "copy_game");
  result = result && test_equality_bool(true, test_play_move(), "play_move");
  result = result && test_equality_bool(true, test_game_square_piece(), "game_square_piece");

  if (result) {
    printf("Youpi !\n");
    return EXIT_SUCCESS;
   }
  else
    return EXIT_FAILURE;
 }
