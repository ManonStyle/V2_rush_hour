#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "hash.h"


bool compare_to(int* t1, int* t2, int nb_pieces){
  for(int i=0; i<nb_pieces; ++i){
    if(t1[i] != t2[i])
      return false;
  }
  return true;
}

typedef struct cell_s* cell;

struct cell_s{
  int* int_game;
  cell next;
};

cell new_cell(int* int_game, cell next){
  cell new_cell = (cell)malloc(sizeof(struct cell_s));
  new_cell->int_game = int_game;
  new_cell->next = next;
  return new_cell;
}

cell delete_cell(cell c){
  cell tmp = c->next;
  free(c);
  return tmp;
}

struct hash_s{
  cell array[1024];
};

hash new_hash(){
  hash new_hash = (hash)malloc(sizeof(struct hash_s));
  if(new_hash == NULL)
    return NULL;
  return new_hash;
}

int hash_func(int* int_game, int nb_pieces){
  int some =0;
  for(int i=0; i<nb_pieces; ++i)
    some += int_game[i];
  return some%1024;
}

void add_hash(hash h, int* int_game, int nb_pieces){
  int index = hash_func(int_game,nb_pieces);
  h->array[index] = new_cell(int_game, h->array[index]);
}

bool in_hash(hash h, int* int_game, int nb_pieces){
  int index = hash_func(int_game,nb_pieces);
  cell tmp = h->array[index];
  while(tmp != NULL){
    if(compare_to(tmp->int_game, int_game, nb_pieces))
      return true;
    tmp = tmp->next;
  }
  return false;
}

void delete_hash(hash h){
  for(int i=0; i<1024; ++i){
    cell tmp = h->array[i];
    while(tmp != NULL){
      tmp = delete_cell(tmp);
    }
  }
  free(h);
}
