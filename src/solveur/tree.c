#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

struct tree_s{
  int nb_moves;
  int* int_game;
  tree father;
  tree brother;
  tree son;
};

tree new_tree(int* int_game, int nb_pieces, int nb_moves){
  tree new_tree = (tree)malloc(sizeof(struct tree_s));
  if(new_tree == NULL)
    return NULL;
  new_tree->int_game = (int*)malloc(sizeof(int)*nb_pieces);
  if(new_tree->int_game == NULL)
    return NULL;
  for(int i=0; i<nb_pieces; ++i)
    new_tree->int_game[i] = int_game[i];
  new_tree->father = NULL;
  new_tree->brother = NULL;
  new_tree->son = NULL;
  new_tree->nb_moves = nb_moves;
  return new_tree;
}

void delete_tree(tree t){
  free(t->int_game);
  free(t);
}

void add_son(tree t, int* int_game, int nb_pieces, int nb_moves){
  tree tmp = new_tree(int_game, nb_pieces, nb_moves);
  tmp->father = t;
  tmp->brother = t->son;
  t->son = tmp;
}

void remove_son(tree t){
  if(t->son == NULL)
    return;
  tree tmp = t->son;
  t->son = tmp->brother;
  while(tmp->son != NULL)
    remove_son(tmp->son);
  delete_tree(tmp);
}

int* get_int_game(tree t){
  return t->int_game;
}

tree get_father(tree t){
  return t->father;
}

tree get_brother(tree t){
  return t->brother;
}

tree get_son(tree t){
  return t->son;
}

int get_nb_moves(tree t){
  return t->nb_moves;
}
