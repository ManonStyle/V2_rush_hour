#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "file.h"


typedef struct cell_s* cell;

struct cell_s{
  tree t;
  cell next;
};

cell new_cell_tree(tree t, cell next){
  cell new_cell = (cell)malloc(sizeof(struct cell_s));
  new_cell->t = t;
  new_cell->next = next;
  return new_cell;
}

cell delete_cell_tree(cell c){
  cell tmp = c->next;
  free(c);
  return tmp;
}



struct file_s{
  cell first;
  cell last;
};

file new_file(){
  file new_file = (file)malloc(sizeof(struct file_s));
  new_file->first = NULL;
  new_file->last = NULL;
  return new_file;
}

void push(file f, tree t){
  cell tmp = new_cell_tree(t, NULL);
  if(f->last == NULL){
    f->first = tmp;
    f->last = tmp;
  }
  else{
    (f->last)->next = tmp;
    f->last = tmp;
  }
}

tree pop(file f){
  if(f->first == NULL)
    return NULL;
  cell tmp_cell = f->first;
  f->first = tmp_cell->next;
  if(f->first == NULL)
    f->last = NULL;
  tree tmp_tree = tmp_cell->t;
  delete_cell_tree(tmp_cell);
  return tmp_tree;
}

bool is_empty(file f){
  return f->first == NULL;
}

void delete_file(file f){
  while(pop(f) != NULL){}
  free(f);
}
  
