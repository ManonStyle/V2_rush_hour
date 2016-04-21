#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "piece.h"


struct piece_s {
  int x;
  int y;
  int width;
  int height;
  bool move_x;
  bool move_y;
};

piece new_piece (int x, int y, int width, int height, bool move_x, bool move_y){
  piece p = (piece)malloc(sizeof(struct piece_s));
  if (p == NULL){
    fprintf(stderr, "Allocation problem");
    return NULL;
  }
  p->x = x;
  p->y = y;
  p->width= width;
  p->height= height;
  p->move_x = move_x;
  p->move_y = move_y;
  return p;
}

piece new_piece_rh(int x, int y, bool small, bool horizontal){
  piece p = (piece)malloc(sizeof(struct piece_s));
  if (p == NULL){
    fprintf(stderr, "Allocation problem");
    return NULL;
  }
  p->x = x;
  p->y = y;
  if(horizontal){
    p->height = 1;
    if(small)
      p->width = 2;
    else
      p->width = 3;
  }
  else{
    p->width = 1;
    if(small)
      p->height = 2;
    else
      p->height = 3;
  }
  p->move_x = horizontal;
  p->move_y = !horizontal;
  return p;
}


void delete_piece (piece p){
  free(p);
}



void copy_piece (cpiece src, piece dst){
  dst->x = src->x;
  dst->y = src->y;
  dst-> width=src->width;
  dst->height=src->height;
  dst-> move_x=src->move_x;
  dst-> move_y=src->move_y;
}


void move_piece (piece p, dir d, int distance){
    if(d == RIGHT)
      p->x += distance;
    else if(d == LEFT)
      p->x -= distance;
    else if(d == UP)
      p->y += distance;
    else
      p->y -= distance;
}


bool intersect(cpiece p1, cpiece p2){
  int x1 = get_x(p1);
  int x2 = get_x(p2);
  int y1 = get_y(p1);
  int y2 = get_y(p2);
  bool intersect_x = false;
  bool intersect_y = false;
  for(int i=0; i<get_width(p1); ++i){
    if(!intersect_x)
    for(int j=0; j<get_width(p2); ++j){
      if(x1+i == x2+j){
	intersect_x = true;
	break;
      }
    }
    else
      break;
  }
  if(!intersect_x)
    return false;
  for(int i=0; i<get_height(p1); ++i){
    if(!intersect_y)
    for(int j=0; j<get_height(p2); ++j){
      if(y1+i == y2+j){
	intersect_y = true;
	break;
      }
    }
    else
      break;
  }
  return intersect_x && intersect_y;
}


int get_x(cpiece p){
  return p->x;
}


int get_y(cpiece p){
  return p->y;
}


int get_height(cpiece p){
  return p->height;
}


int get_width(cpiece p){
  return p->width;
}


bool is_horizontal(cpiece p){
  return p->move_x;
}


bool can_move_x(cpiece p){
  return p->move_x;
}

bool can_move_y(cpiece p){
  return p->move_y;
}





