#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "game.h"
#include "piece.h"


struct dir_option_s{
  char name[6];
  dir option;
};

typedef struct game_option_s* dir_option;
dir_option direction[] = {{"up",UP},{"down",DOWN},{"right",RIGHT},{"left",LEFT}};



typedef int (func)(int);

struct game_option_s{
  char name[4];
  func f_game;
};

typedef struct game_option_s* game_option;
game_option game_chose[] = {{"-rh", game_rh},{"-ag", game_ag}};



void print_line_empty(game g, int y){
  for(int x=0; x<game_whidth(g); ++x)
    printf("|      ");
  cpiece init_p = game_piece(g, 0);
  if(y >= get_y(init_p) && y < get_y(init_p)+get_height(init_p)){
    if(y == get_y(init_p) && y == get_y(init_p)+get_height(init_p)-1)
      printf("------\n");
    else
      printf("\n");
  }
  else
    printf("|\n");
}



void print_line(game g, int y){
  for(int x=0; x<game_whidth(g); ++x){
    int piece_num = game_square_piece (g, x, y);
    if(piece_num != -1)
      printf("|  %2d  ", piece_num);
    else
      printf("|      ");
  }
  cpiece init_p = game_piece(g, 0);
  if(y >= get_y(init_p) && y < get_y(init_p)+get_height(init_p)){
     if(y == get_y(init_p) && y == get_y(init_p)+get_height(init_p)-1)
       printf(" exit \n");
     else
       printf("\n");
  }
  else
    printf("|\n");
}



void print_line_end(game g, int y){
  for(int x=0; x<game_whidth(g); ++x){
    int piece_num = game_square_piece (g, x, y-1);
    if(piece_num != -1)
      printf("-------");
    else
      printf("-     ");
  }
  cpiece init_p = game_piece(g, 0);
  if(y >= get_y(init_p) && y < get_y(init_p)+get_height(init_p)){
    if(y == get_y(init_p) && y == get_y(init_p)+get_height(init_p)-1)
      printf("|\n");
    else
      printf("\n");
  }
  else
    printf("|\n");
}
      


// Print the board of the current game in the terminal
void print_game(game g){
  printf("-------------------------------------------\n");
  for(int y= game_height(g)-1; y>0; --y){ 
    print_line_empty(g, y);
    print_line(g, y);
    print_line_empty(g, y);
    print_line_end(g, y);
  }
  print_line_empty(g, 0);
  print_line(g, 0);
  print_line_empty(g, 0);
  printf("-------------------------------------------\n");
}

void usage(char* str){
  fprintf(stderr, "Usage: %s -game <int level>\n", str);
  return exit(EXIT_FAILURE);
}


int main(int argc, char* argv[]){
  if(argc != 3)
    usage(argv[0]);
  func f_game;
  for(int i=0; i<2; ++i){
    if(strcmp(argv[1], game_chose[i].name) == 10){
      call_game = game_chose[i].f_game;
      break;
    }
  }
  if(f_game == NULL)
    usage(argv[0]);
  
