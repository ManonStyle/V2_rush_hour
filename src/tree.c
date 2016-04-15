#include <stdlib.h>
#include <stdio.h>

#include "tree.h"
#include "game.h"



struct tree_pos_s{
  int x;
  int y;
  tree_pos father;
  tree_pos son;
  tree_pos brother;
};

tree_pos new_tree_pos(int x, int y, tree_pos father, tree_pos son, tree_pos brother){
  tree_pos new_tree = (tree_pos)malloc(sizeof(struct tree_pos_s));
  if(new_tree == NULL)
    return NULL;
  new_tree->x = x;
  new_tree->y = y;
  new_tree->father = father;
  new_tree->son = son;
  new_tree->brother = brother;
  return new_tree;
}

int get_x_pos(tree_pos tree){
  return tree->x;
}

int get_y_pos(tree_pos tree){
  return tree->y;
}


tree_pos get_brother_pos(tree_pos tree){
  return tree->brother;
}

tree_pos get_father_pos(tree_pos tree){
  return tree->father;
}

tree_pos get_son_pos(tree_pos tree){
  return tree->son;
}

void set_data_pos(tree_pos tree, int x, int y){
  tree->x = x;
  tree->y = y;
}

void set_brother_pos(tree_pos tree, tree_pos brother){
  tree->brother = brother;
}

void set_father_pos(tree_pos tree, tree_pos father){
  tree->father = father;
}

void set_son_pos(tree_pos tree, tree_pos son){
  tree->son = son;
}

void add_brother_pos(tree_pos tree, int x, int y){
  tree_pos tmp = tree;
  while(tmp->brother != NULL)
    tmp = tmp->brother;
  tmp->brother = new_tree_pos(x, y, tmp->father, NULL, NULL);
}

void add_son_pos(tree_pos tree, int x, int y){
  add_brother_pos(tree->son, x, y);
}

void delete_tree_pos(tree_pos tree){
  if(tree->son != NULL)
    delete_tree_pos(tree->son);
  tree->father->son = tree->brother;
  free(tree);
}

struct tree_game_s{
  game data;
  int move[3];
  tree_game father;
  tree_game son;
  tree_game brother;
};

tree_game new_tree_game(game data, tree_game father, tree_game son, tree_game brother,  int* move){
  tree_game new_tree = (tree_game)malloc(sizeof(struct tree_game_s));
  if(new_tree == NULL)
    return NULL;
  new_tree->data = data;
  for(int i=0; i<3; ++i)
    new_tree->move[i] = move[i];
  new_tree->father = father;
  new_tree->son = son;
  new_tree->brother = brother;
  return new_tree;
}

game get_data_game(tree_game tree){
  return tree->data;
}

int get_move_game(tree_game tree, int i){
  return tree->move[i];
}

tree_game get_brother_game(tree_game tree){
  return tree->brother;
}

tree_game get_father_game(tree_game tree){
  return tree->father;
}

tree_game get_son_game(tree_game tree){
  return tree->son;
}

void set_data_game(tree_game tree, game data){
  tree->data = data;
}

void set_move_game(tree_game tree, int* move){
  for(int i=0; i<3; ++i)
    tree->move[i] = move[i];
}

void set_brother_game(tree_game tree, tree_game brother){
  tree->brother = brother;
}

void set_father_game(tree_game tree, tree_game father){
  tree->father = father;
}

void set_son_game(tree_game tree, tree_game son){
  tree->son = son;
}

void add_brother_game(tree_game tree, game data, int* move){
  tree_game tmp = tree;
  while(tmp->brother != NULL)
    tmp = tmp->brother;
  tmp->brother = new_tree_game(data, tmp->father, NULL, NULL, move);
}

void add_son_game(tree_game tree, game data, int* move){
  add_brother_game(tree->son, data, move);
}

void delete_tree_game(tree_game tree){
  if(tree->son != NULL)
    delete_tree_game(tree->son);
  tree->father->son = tree->brother;
  free(tree);
}
