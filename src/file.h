#ifndef _FILE_H_
#define _FILE_H_
#include <stdbool.h>

#include "tree.h"

typedef struct file_s* file;

file new_file();
void push(file f, tree t);
tree pop(file f);
bool is_empty(file f);
void delete_file(file f);

#endif
