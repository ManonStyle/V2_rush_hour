#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "piece.h"
#include "game.h"

#define NB_PIECES 5
#define WIDTH 8
#define HEIGHT 10

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
/* configue de test new_game_rh & copy_game & new_game
......
....2.
00..21
..4.21
..4.33
......
 */
void set_up() {
  pieces[0] = new_piece_rh(0, 3, true, true);
  pieces[1] = new_piece_rh(5, 2, true, false);
  pieces[2] = new_piece_rh(4, 2, false, false);
  pieces[3] = new_piece_rh(4, 1, true, true);
  pieces[4] = new_piece_rh(2, 1, true, false);
}

void tear_down() {
  for (int i = 0 ; i < NB_PIECES; i++)
    delete_piece(pieces[i]);
}

piece piecesBis[2];
/* configue de test play_move 
......
......
...00.
..1...
..1...
......
 */
void set_up_Bis() {
  piecesBis[0] = new_piece_rh(3, 3, true, true);
  piecesBis[1] = new_piece_rh(2, 1, true, false);
}

void tear_down_Bis() {
  for (int i = 0 ; i < 2; i++)
    delete_piece(piecesBis[i]);
}

///////////// version 1 /////////////////

bool test_new_game_rh(){
  bool result = true;
  set_up();
  game g = new_game_hr(NB_PIECES, pieces);
  result = result && test_equality_int(NB_PIECES, game_nb_pieces(g), "new_game_rh game_nb_pieces");
  result = result && test_equality_int(0, game_nb_moves(g), "new_game_rh game_nb_moves");
  for (int i = 0; i < NB_PIECES; ++i){
    result = result && test_equality_int(get_x(pieces[i]), get_x(game_piece(g, i)), "new_game_rh game_piece get_x");
    result = result && test_equality_int(get_y(pieces[i]), get_y(game_piece(g, i)), "new_game_rh game_piece get_y");
    result = result && test_equality_int(get_height(pieces[i]), get_height(game_piece(g, i)), "new_game_rh game_piece get_height");
    result = result && test_equality_int(get_width(pieces[i]), get_width(game_piece(g, i)), "new_game_rh game_piece get_width");
    result = result && test_equality_bool(is_horizontal(pieces[i]), is_horizontal(game_piece(g, i)), "new_game_rh game_piece is_horizontal");
  }
  tear_down();
  delete_game(g);
  return result;
}

bool test_play_move(){
  bool result = true;
  set_up_Bis();
  game g = new_game_hr(2, piecesBis);
  result = result && test_equality_bool(false, game_over_hr(g), "play_move game_over_hr false");

  result = result && test_equality_bool(true, play_move(g, 0, LEFT, 3), "play_move LEFT true");
  result = result && test_equality_bool(false, play_move(g, 0, LEFT, 1), "play_move LEFT false");
  result = result && test_equality_bool(true, play_move(g, 0, RIGHT, 4), "play_move RIGHT true");
  result = result && test_equality_bool(false, play_move(g, 0, RIGHT, 1), "play_move RIGHT false");
  result = result && test_equality_bool(true, play_move(g, 1, UP, 3), "play_move UP true");
  result = result && test_equality_bool(false, play_move(g, 1, UP, 1), "play_move UP false");
  result = result && test_equality_bool(true, play_move(g, 1, DOWN, 4), "play_move DOWN true");
  result = result && test_equality_bool(false, play_move(g, 1, DOWN, 1), "play_move DOWN false");

  result = result && test_equality_bool(true, game_over_hr(g), "play_move game_over_hr true");

  play_move(g, 0, LEFT, 2);
  result = result && test_equality_bool(false, play_move(g, 1, UP, 2), "play_move UP intersect");
  delete_game(g);
  return result;
}

bool test_copy_game(){
  bool result = true;
  set_up();
  game g = new_game_hr(NB_PIECES, pieces);
  piece piecesC[] = {new_piece_rh(2, 1, true, false)};
  game gC = new_game_hr(1, piecesC);
  copy_game(g, gC);
  result = result && test_equality_int(game_nb_pieces(g), game_nb_pieces(gC), "copy game_nb_pieces");
  result = result && test_equality_int(game_nb_moves(g), game_nb_moves(gC), "copy game_nb_moves");
  for (int i = 0; i < NB_PIECES; ++i){
    result = result && test_equality_int(get_x(pieces[i]), get_x(game_piece(g, i)), "game_piece get_x");
    result = result && test_equality_int(get_y(pieces[i]), get_y(game_piece(g, i)), "game_piece get_y");
    result = result && test_equality_int(get_height(pieces[i]), get_height(game_piece(g, i)), "game_piece get_height");
    result = result && test_equality_int(get_width(pieces[i]), get_width(game_piece(g, i)), "game_piece get_width");
    result = result && test_equality_bool(is_horizontal(pieces[i]), is_horizontal(game_piece(g, i)), "game_piece is_horizontal");
  }
  tear_down();
  delete_game(g);
  //delete_game(gC); -> erreur à résoudre
  return result;
}

///////////// version 2 /////////////////

bool test_new_game(){
  bool result = true;
  set_up();
  game g = new_game(WIDTH, HEIGHT, NB_PIECES, pieces);
  result = result && test_equality_int(WIDTH, game_width(g), "new_game game_width");
  result = result && test_equality_int(HEIGHT, game_height(g), "new_game game_height");
  result = result && test_equality_int(NB_PIECES, game_nb_pieces(g), "new_game game_nb_pieces");
  result = result && test_equality_int(0, game_nb_moves(g), "new_game game_nb_moves");
  for (int i = 0; i < NB_PIECES; ++i){
    result = result && test_equality_int(get_x(pieces[i]), get_x(game_piece(g, i)), "new_game game_piece get_x");
    result = result && test_equality_int(get_y(pieces[i]), get_y(game_piece(g, i)), "new_game game_piece get_y");
    result = result && test_equality_int(get_height(pieces[i]), get_height(game_piece(g, i)), "new_game game_piece get_height");
    result = result && test_equality_int(get_width(pieces[i]), get_width(game_piece(g, i)), "new_game game_piece get_width");
    result = result && test_equality_bool(is_horizontal(pieces[i]), is_horizontal(game_piece(g, i)), "new_game game_piece is_horizontal");
  }
  tear_down();
  delete_game(g);
  return result;
}

int piecesNum[WIDTH][HEIGHT];

void fillArrayWithPieces(){
  for(int x = 0; x < WIDTH; ++x){
    for(int y = 0; y < HEIGHT; ++y){
      piecesNum[x][y] = -1;
    }
  }
  for(int p = 0; p < NB_PIECES; ++p){
    for(int x = get_x(pieces[p]); x < get_x(pieces[p]) + get_width(pieces[p]); ++x){
      for(int y = get_y(pieces[p]); y < get_y(pieces[p]) + get_width(pieces[p]); ++y)
	piecesNum[x][y] = p;
    }
  }
}

bool test_game_square_piece(){
  bool result = true;
  set_up();
  game g = new_game(WIDTH, HEIGHT, NB_PIECES, pieces);
  fillArrayWithPieces();
  for(int x = 0; x < WIDTH; x++){
    for(int y = 0; y < HEIGHT; y++){
      result = result && test_equality_int(piecesNum[x][y], game_square_piece(g, x, y), "game_square_piece");
    }
  }
  tear_down();
  delete_game(g);
  return result;
}


int main (int argc, char *argv[]){
  bool result = true;

  ///////////// version 1 /////////////////

  result = result && test_equality_bool(true, test_new_game_rh(), "new_game_rh");
  result = result && test_equality_bool(true, test_play_move(), "play_move");
  result = result && test_equality_bool(true, test_copy_game(), "copy_game");

  ///////////// version 2 /////////////////

  result = result && test_equality_bool(true, test_new_game(), "new_game");
  result = result && test_equality_bool(true, test_game_square_piece(), "game_square_piece");

  if (result) {
    printf("Youpi !\n");
    return EXIT_SUCCESS;
   }
  else
    return EXIT_FAILURE;
 }
