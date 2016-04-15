#ifndef _FILE_H_
#define _FILE_H_
#include <stdbool.h>
#include "game.h"
#include "tree.h"


typedef struct cell_tree_s* cell_tree;

cell_tree new_cell_tree(tree_game data, cell_tree next);

void delete_cell_tree(cell_tree cell);



typedef struct file_tree_s* file_tree;

file_tree new_file_tree();

void push_file_tree(file_tree file, tree_game data);

tree_game pop_file_tree(file_tree file);

void clear_file_tree(file_tree file);

#endif
