#include <stdlib.h>
#include <stdio.h>

#include "tree.h"
#include "game.h"
#include "file.h"

struct cell_tree_s{
  tree_game data;
  cell_tree next;
};

cell_tree new_cell_tree(tree_game data, cell_tree next){
  cell_tree new_cell = (cell_tree)malloc(sizeof(struct cell_tree_s));
  new_cell->data = data;
  new_cell->next = next;
  return new_cell;
}

void delete_cell_tree(cell_tree cell){
  free(cell);
}

struct file_tree_s{
  cell_tree first;
  cell_tree last;
};

file_tree new_file_tree(){
  file_tree new_file = (file_tree)malloc(sizeof(struct file_tree_s));
  return new_file;
}

void push_file_tree(file_tree file, tree_game data){
  cell_tree last = new_cell_tree(data, NULL);
  if(file->last == NULL){
    file->first = last;
    file->last = last;
  }
  else{
    (file->last)->next = last;
    file->last = last;
  }
}

tree_game pop_file_tree(file_tree file){
  if(file->first == NULL)
    return NULL;
  cell_tree cell = file->first;
  tree_game tree = cell->data;
  file->first = cell->next;
  delete_cell_tree(cell);
  if(file->first == NULL)
    file->last = NULL;
  return tree;
}

void clear_file_tree(file_tree file){
  tree_game tmp_tree = NULL;
  while(tmp_tree != NULL)
    tmp_tree = pop_file_tree(file);
  free(file);
}

