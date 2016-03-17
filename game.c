#include <stdlib.h>
#include <stdio.h>
#include "game.h"



struct game_s{
  int width;
  int height;
  int nb_pieces;
  int nb_moves;
  piece *pieces;
};


game new_game_hr (int nb_pieces, piece *pieces){
  game g = (game)malloc(sizeof(struct game_s));
  g->width = 6;
  g->height = 6;
  g->nb_pieces = nb_pieces;
  g->nb_moves = 0;
  g->pieces = (piece*)malloc(nb_pieces*sizeof(piece));
  if (g == NULL){
    fprintf(stderr, "Allocation problem");
    exit(EXIT_FAILURE);
  }
  for(int i=0; i<=nb_pieces; ++i){
    g->pieces[i] = new_piece_rh(0, 0, true, true);
    copy_piece(pieces[i], g->pieces[i]);
  }
  return g;
}

void delete_game (game g){
  for(int i=0; i<=g->nb_pieces; ++i)
    delete_piece(g->pieces[i]);
  free(g->pieces);
  free(g);
}

void copy_game (cgame src, game dst){
  dst->width = src->width;
  dst->height = src->height;
  dst->nb_pieces = src->nb_pieces;
  dst->nb_moves = src->nb_moves;
  for(int i=0; i<=src->nb_pieces; ++i){
    if(dst->pieces[i] == NULL)
      dst->pieces[i] = new_piece_rh(0, 0, true, true);
    copy_piece(src->pieces[i], dst->pieces[i]);
  }
}

int game_nb_pieces(cgame g){
  return g->nb_pieces;
}

cpiece game_piece(cgame g, int piece_num){
  if(piece_num > g->nb_pieces){
    fprintf(stderr, "index is out of range\n");
    return NULL;
  }
  return g->pieces[piece_num];
}


bool game_over_hr (cgame g){
  return get_x(g->pieces[0]) == get_x(g->pieces[g->nb_pieces]) && get_y(g->pieces[0]) == get_y(g->pieces[g->nb_pieces]);
}


bool play_move(game g, int piece_num, dir d, int distance){
  piece p = g->pieces[piece_num];
  if(!can_move_y(p)){
    if(d == UP || d == DOWN)
      return false;
  }
  if(!can_move_x(p)){
    if(d == RIGHT || d == LEFT)
      return false;
  }
  if(d == RIGHT){
    if(get_x(p)+get_width(p)+distance-1 >= game_width(g))
      return false;
    for(int i=0; i<distance; ++i){
      if(game_square_piece(g, get_x(p)+get_width(p)+i, get_y(p)) != -1)
	return false;
    }
  }
  else if(d == LEFT){
    if(get_x(p)-distance < 0)
       return false;
    for(int i=0; i<distance; ++i){
      if(game_square_piece(g, get_x(p)-1-i, get_y(p)) != -1)
	return false;
    }
  }
  else if(d == UP){
    if(get_y(p)+get_height(p)+distance-1 >= game_height(g))
       return false;
    for(int i=0; i<distance; ++i){
      if(game_square_piece(g, get_x(p), get_y(p)+get_height(p)+i) != -1)
	return false;
    }
  }
  else{
    if(get_y(p)-distance < 0)
      return false;
    for(int i=0; i<distance; ++i){
      if(game_square_piece(g, get_x(p), get_y(p)-1-i) != -1)
	return false;
    }
  }
  g->nb_moves += distance;
  move_piece(p, d, distance);
  return true;
}


int game_nb_moves(cgame g){
  return g->nb_moves;
}


game new_game (int width, int height, int nb_pieces, piece *pieces){
  game g = (game)malloc(sizeof(struct game_s));
  g->width = width;
  g->height = height;
  g->nb_pieces = nb_pieces;
  g->nb_moves = 0;
  g->pieces = (piece*)malloc(nb_pieces*sizeof(piece));
  if (g == NULL){
    fprintf(stderr, "Allocation problem");
    exit(EXIT_FAILURE);
  }
  for(int i=0; i<=nb_pieces; ++i){
    g->pieces[i] = new_piece_rh(0, 0, true, true);
    copy_piece(pieces[i], g->pieces[i]);
  }
  return g;
}

int game_width(cgame g){
  return g->width;
}

int game_height(cgame g){
  return g->height;
}


int game_square_piece (game g, int x, int y){
  int px, py, pw, ph;
  for (int piece_num= 0; piece_num<g->nb_pieces; ++piece_num) {
    cpiece p = g->pieces[piece_num];
    px = get_x(p);
    py = get_y(p);
    pw = get_width(p);
    ph = get_height(p);
    for (int w=0; w<pw; ++w){
      for (int h=0; h<ph; ++h){
	if ( x==px+w && y==py+h)
	  return piece_num;
      }
    }
  }
  return -1;
}

