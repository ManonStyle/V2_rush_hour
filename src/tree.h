#ifndef _TREE_H_
#define _TREE_H_
#include "game.h"

typedef struct tree_pos_s* tree_pos;

tree_pos new_tree_pos(int x, int y, tree_pos father, tree_pos son, tree_pos brother);

int get_x_pos(tree_pos tree);

int get_y_pos(tree_pos tree);

tree_pos get_brother_pos(tree_pos tree);

tree_pos get_father_pos(tree_pos tree);

tree_pos get_son_pos(tree_pos tree);

void set_data_pos(tree_pos tree, int x, int y);

void set_brother_pos(tree_pos tree, tree_pos brother);

void set_father_pos(tree_pos tree, tree_pos father);

void set_son_pos(tree_pos tree, tree_pos son);

void add_brother_pos(tree_pos tree, int x, int y);

void add_son_pos(tree_pos tree, int x, int y);

void delete_tree_pos(tree_pos tree);



typedef struct tree_game_s* tree_game;

tree_game new_tree_game(game data, tree_game father, tree_game son, tree_game brother, int* move);

game get_data_game(tree_game tree);

int get_move_game(tree_game tree, int i);

tree_game get_brother_game(tree_game tree);

tree_game get_father_game(tree_game tree);

tree_game get_son_game(tree_game tree);

void set_data_game(tree_game tree, game data);

void set_brother_game(tree_game tree, tree_game brother);

void set_father_game(tree_game tree, tree_game father);

void set_son_game(tree_game tree, tree_game son);

void add_brother_game(tree_game tree, game data, int* move);

void add_son_game(tree_game tree, game data, int* move);

void delete_tree_game(tree_game tree);

#endif

