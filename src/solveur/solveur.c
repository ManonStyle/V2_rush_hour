#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "file.h"
#include "tree.h"
#include "hash.h"
#include "game.h"
#include "piece.h"


game init_game(char* file_name){
  FILE* f = fopen(file_name, "r");
  if(f == NULL)
    exit(EXIT_FAILURE);
  char tmp[20]; 
  if(!fgets(tmp, 20, f)){
    fprintf(stderr, "Problem for read the file: %s\n", file_name);
    exit(EXIT_FAILURE);
  }
  const char limit[2] = " ";
  char* splited = strtok(tmp, limit);
  int g_width = atoi(splited);
  splited = strtok(NULL, limit);
  int g_height = atoi(splited);
  if(!fgets(tmp, 20, f)){
    fprintf(stderr, "Problem for read the file: %s\n", file_name);
    exit(EXIT_FAILURE);
  }
  splited = strtok(tmp, limit);
  int nb_pieces = atoi(splited);
  piece pieces[nb_pieces];
  char value[1];
  for(int i=0; i<nb_pieces; ++i){
    if(!fgets(tmp, 20, f)){
      fprintf(stderr, "Problem for read the file: %s\n", file_name);
      exit(EXIT_FAILURE);
    }
    splited = strtok(tmp, limit);
    value[0] = splited[0];
    int x = atoi(value);
    splited = strtok(NULL, limit);
    value[0] = splited[0];
    int y = atoi(value);
    splited = strtok(NULL, limit);
    value[0] = splited[0];
    int width = atoi(value);
    splited = strtok(NULL, limit);
    value[0] = splited[0];
    int height = atoi(value);
    splited = strtok(NULL, limit);
    value[0] = splited[0];
    bool move_x = atoi(value);
    splited = strtok(NULL, limit);
    value[0] = splited[0];
    bool move_y = atoi(value);
    pieces[i] = new_piece(x, y, width, height, move_x, move_y);
    if(pieces[i] == NULL)
      exit(EXIT_FAILURE);
  }
  fclose(f);
  game g = new_game(g_width, g_height, nb_pieces, pieces);
  if(g == NULL)
    exit(EXIT_FAILURE);
  for(int i=0; i<nb_pieces; ++i)
    delete_piece(pieces[i]);
  return g;
}


bool game_over(cgame g, int game_i){
  switch(game_i){
  case 0 : return game_over_hr(g);
  default :
    return get_x(game_piece(g, 0)) == 3 && get_y(game_piece(g, 0)) == 1;
  }
}


void usage(char* str){
  fprintf(stderr, "Usage: %s <a|r> <filename>\n", str);
  return exit(EXIT_FAILURE);
}


void game_to_int(cgame g, int* int_game){
  for(int i=0; i<game_nb_pieces(g); ++i){
    cpiece p = game_piece(g, i);
    int_game[i]= get_y(p) + get_x(p)*100 + i*10000;
  }
}


game int_to_game(cgame g, int* int_game){
  int nb_pieces = game_nb_pieces(g);
  piece pieces[nb_pieces];
  for(int i=0; i<nb_pieces; ++i){
    cpiece p = game_piece(g, i);
    int x = (int_game[i]/100)%100;
    int y = int_game[i]%100;
    pieces[i] = new_piece(x, y, get_width(p), get_height(p), can_move_x(p), can_move_y(p));
  }
  game new_g = new_game(game_width(g), game_height(g), nb_pieces, pieces);
  for(int i=0; i<nb_pieces; ++i)
    delete_piece(pieces[i]);
  return new_g;
}

void path_to_win(tree t){
  if(t == NULL){
    printf("-1\n");
    return;
  }
  printf("%d\n", get_nb_moves(t));
}
  

tree test_soluce(cgame g, int game_i, hash save_move, file f, 
		 tree t, int piece_num, int d, int size){
  int nb_pieces = game_nb_pieces(g);
  for(int i_dir=d; i_dir<4; i_dir+=2){
    for(int n=1; n<size; ++n){
      game tmp = int_to_game(g, get_int_game(t));
      if(play_move(tmp, piece_num , i_dir, n)){
	int int_game[nb_pieces];
	game_to_int(tmp, int_game);
	if(!in_hash(save_move, int_game, nb_pieces)){
	  add_son(t, int_game, nb_pieces, get_nb_moves(t)+n);
	  tree t_son = get_son(t);
	  add_hash(save_move, get_int_game(t_son), nb_pieces);
	  push(f, t_son);
	  if(game_over(tmp, game_i)){
	    delete_game(tmp);
	    return t_son;
	  }
	}
	delete_game(tmp);
      }
      else{
	delete_game(tmp);
	break;
      }
    }
  }
  return NULL;
}

void delete_all(hash h, tree t, file f){
  delete_hash(h);
  delete_file(f);
  delete_tree(t);
}

void solve_game(cgame g, int game_i){
  int width = game_width(g);
  int height = game_height(g);
  int nb_pieces = game_nb_pieces(g);
  int int_game[nb_pieces];
  game_to_int(g, int_game);
  tree tree_analyse = new_tree(int_game, nb_pieces, 0);
  file f =  new_file();
  push(f, tree_analyse);
  hash save_move = new_hash();
  add_hash(save_move, get_int_game(tree_analyse), nb_pieces);
  while(!is_empty(f)){
    tree tmp = pop(f);
    for(int i=0; i<nb_pieces; ++i){
      tree test = test_soluce(g, game_i, save_move, f, tmp, i, 0, height);
      if(test != NULL){
	path_to_win(test);
	delete_all(save_move, tree_analyse, f);
	return;
      }
      test = test_soluce(g, game_i, save_move, f, tmp, i, 1, width);
      if(test != NULL){
	path_to_win(test);
	delete_all(save_move, tree_analyse, f);
	return;
      }
    }
  }
  path_to_win(NULL);
  delete_all(save_move, tree_analyse, f);
}

int main(int argc, char* argv[]){
  if(argc != 3)
    usage(argv[0]);
  int game_i = -1;
  if(strcmp(argv[1], "r") == 0)
    game_i = 0;
  else if(strcmp(argv[1], "a") == 0)
    game_i = 1;
  else
     game_i = -1;
  if(game_i == -1)
    usage(argv[0]);
  game g = init_game(argv[2]);
  if(!game_over(g, game_i))
    solve_game(g, game_i);
  else
    printf("0\n");
  return EXIT_SUCCESS;
}
