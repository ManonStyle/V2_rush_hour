#ifndef _TREE_H_
#define _TREE_H_


typedef struct tree_s* tree;

tree new_tree(int* int_game, int nb_pieces);
void delete_tree(tree t);
void add_son(tree t, int* int_game, int nb_pieces);
void remove_son(tree t);
int* get_int_game(tree t);
tree get_father(tree t);
tree get_brother(tree t);
tree get_son(tree t);

#endif
