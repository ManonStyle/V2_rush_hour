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

  result = result && test_equality_bool(true, test_game_square_piece(), "game_square_piece");

  if (result) {
    printf("Youpi !\n");
    return EXIT_SUCCESS;
   }
  else
    return EXIT_FAILURE;
 }
