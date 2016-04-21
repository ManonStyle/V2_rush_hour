#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "file.h"
#include "tree.h"
#include "hash.h"
#include "game.h"
#include "piece.h"

struct game_option_s{
  char name[4];
  char file[30];
};


typedef struct game_option_s game_option;
game_option game_chose[] = {{"-rh", "game_rh.txt"},{"-ar", "game_ar.txt"}};


game init_game(int level, int game_i){
  FILE* f = fopen(game_chose[game_i].file, "r");
  if(f == NULL)
    exit(EXIT_FAILURE);
  char tmp[100]; 
  for(int i=0; i<level; ++i){
    if(!fgets(tmp, 100, f)){
      fprintf(stderr, "There is no level %d\n", level);
      exit(EXIT_FAILURE);
    }
  }
  const char limit[2] = ".";
  char* splited = strtok(tmp, limit);
  int g_width = atoi(splited);
  splited = strtok(NULL, limit);
  int g_height = atoi(splited);
  splited = strtok(NULL, limit);
  int nb_pieces = atoi(splited);
  piece pieces[nb_pieces];
  char value[1];
  for(int i=0; i<nb_pieces; ++i){
    splited = strtok(NULL, limit);
    value[0] = splited[0];
    int x = atoi(value);
    value[0] = splited[1];
    int y = atoi(value);
    value[0] = splited[2];
    int width = atoi(value);
    value[0] = splited[3];
    int height = atoi(value);
    value[0] = splited[4];
    bool move_x = atoi(value);
    value[0] = splited[5];
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
  fprintf(stderr, "Usage: %s -game <int level>\n", str);
  fprintf(stderr, "game option:\n-rh: rush hour\n-ar: ane rouge\n");
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

void resize_array(int* array, int size){
  array = (int*)realloc(array, size*sizeof(int)*2);
  if(array == NULL){
    fprintf(stderr,"Not enough memory!\n");
    exit(EXIT_FAILURE);
  }
}


void path_to_win(tree t, int nb_pieces){
  if(t == NULL){
    printf("There is no solution. The game is impossible\n");
    return;
  }
  int* move = (int*)malloc(sizeof(int)*100);
  int size = 0;
  int max_size = 100;
  tree tmp = t;
  while(get_father(tmp) != NULL){
    tree tmp_father = get_father(tmp);
    int* int_game_son = get_int_game(tmp);
    int* int_game_father = get_int_game(tmp_father);
    for(int i=0; i<nb_pieces; ++i){
      if(int_game_son[i] != int_game_father[i]){
	if(max_size == size)
	  resize_array(move, size);
	move[size] = int_game_son[i];
	size++;
	break;
      }
    }
    tmp = tmp_father;
  }
  printf("Path to win in %d moves:\n", size);
  for(int i=size-1; i>=0; --i)
    printf("%d in (%d,%d); ", move[i]/10000, (move[i]/100)%100, move[i]%100);
  printf("\n");
  free(move);
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
	  add_son(t, int_game, nb_pieces);
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
  tree tree_analyse = new_tree(int_game, nb_pieces);
  file f =  new_file();
  push(f, tree_analyse);
  hash save_move = new_hash();
  add_hash(save_move, get_int_game(tree_analyse), nb_pieces);
  while(!is_empty(f)){
    tree tmp = pop(f);
    for(int i=0; i<nb_pieces; ++i){
      tree test = test_soluce(g, game_i, save_move, f, tmp, i, 0, height);
      if(test != NULL){
	path_to_win(test, nb_pieces);
	delete_all(save_move, tree_analyse, f);
	return;
      }
      test = test_soluce(g, game_i, save_move, f, tmp, i, 1, width);
      if(test != NULL){
	path_to_win(test, nb_pieces);
	delete_all(save_move, tree_analyse, f);
	return;
      }
    }
  }
  path_to_win(NULL, 0);
  delete_all(save_move, tree_analyse, f);
}

int main(int argc, char* argv[]){
  if(argc != 3)
    usage(argv[0]);
  int game_i = -1;
  for(int i=0; i<2; ++i){
    if(strcmp(argv[1], game_chose[i].name) == 0){
      game_i = i;
      break;
    }
  }
  if(game_i == -1)
    usage(argv[0]);
  int level = atoi(argv[2]);
  if(level <= 0)
    usage(argv[0]);
  game g = init_game(level, game_i);
  if(!game_over(g, game_i))
    solve_game(g, game_i);
  else
    printf("The game is terminate whithout moving\n");
  return EXIT_SUCCESS;
}
