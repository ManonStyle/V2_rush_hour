#ifndef _HASH_H_
#define _HASH_H_
#include <stdbool.h>


typedef struct hash_s* hash;

hash new_hash();
void add_hash(hash h, int* int_game, int nb_pieces);
bool in_hash(hash h, int* int_game, int nb_pieces);
void delete_hash(hash h);

#endif
