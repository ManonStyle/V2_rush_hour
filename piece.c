#include <stdbool.h> //The type bool is defined in this file
#include <stdio.h>
#include <stdlib.h>
#include "piece.h"
/**
 * @file piece.h


 
 * @brief A piece represents a vehicle placed on the board of the game rush-hour.
 *
 **/

/**
 * @struct piece_s
 * @brief A piece represents a vehicle of the game rush hour placed on the board.
 *
 * A piece is characterized by its position, its shape and its ability to move vertically or horizontally.
 * piece is a pointer to the structure that describes a vehicle on the board.
 *
 * cpiece is a pointer toward a constant piece.
 * This means that it is not possible to modify the piece through to this pointer.
 * See also: http://www.geeksforgeeks.org/const-qualifier-in-c/
 * See also this more technical discussion: http://stackoverflow.com/questions/8504411/typedef-pointer-const-weirdness
 *
 */
typedef struct piece_s*{
  int x;
  int y;
  bool small;
  bool horizontal;
  int width;
  int height;
  bool move_x;
  bool move_y;
}piece;

typedef const struct piece_s* cpiece;

/**
 * @enum dir_e
 * @brief The enumeration of possible directions of a move
 */
typedef enum dir_e {UP, LEFT, DOWN, RIGHT} dir;

/**
 * @brief Creates a new piece.
 * @param x,y coordinates of the lower-left corner (Remark: x-axe is oriented from left to right and y-axe is oriented from bottom to top).
 * @param small indicates if the vehicle is of size 2 (small=true) or 3 (small=false)
 * @param horizontal indicates whether the vehicle can move horizontally or vertically
 * @return a pointer toward the generated piece
 */
piece new_piece_rh (int x, int y, bool small, bool horizontal){
  piece p = (piece)malloc(sizeof(struct piece_s));
  if (p == NULL){
    fprintf(stderr, "Allocation problem");
    exit(EXIT_FAILURE);
  }
  p->x = x;
  p->y = y;
  p->small = small;
  p->horizontal = horizontal;
  //si p n'est pas horizontal
   p->height=1;
   if (p->horizontal==false&&p->small==false)
     p->height=3;       
   else
     p->height=2;
   //si p est horizontal
    p->width=1;
   if (p->horizontal==true&&p->small==true)
     p->width=2;       
   else
     p->width=3;
  return p;
}


/**
 * @brief Destroys the piece and frees allocated memory
 * @param p the piece to destroy
 */
void delete_piece (piece p){
  free(p);
}

/**
 * @brief Clones the piece src into the piece dst.
 * @param[out] src the piece to copy
 * @param[in]  dst the copied piece
 */
void copy_piece (cpiece src, piece dst){
  dst->x = src->x;
  dst->y = src->y;
  dst->small = src->small;
  dst->horizontal = src->horizontal;
  dst-> width=src->width;
  dst->height=src->height;
  dst-> move_x=src->move_x;
  dst-> move_y=src->move_y;
}
/**
 *
 * @brief Tries to move the piece p in direction d with distance steps.
 * If the direction is LEFT or RIGHT and the piece is not allowed to move horizontally, then the piece is not moved.
 * Similarly, if the direction is UP or DOWN and the piece is not allowed to move vertically, then the piece is not moved.
 *
 */
/*************************fonction dorigine********************************/
void move_piece (piece p, dir d, int distance){
  if (p->horizontal){
    if (d == RIGHT)
      p->x += distance;
    if (d == LEFT)
      p->x -= distance;
    else{
      return;
    }
  }
  else{
    if (d == UP)
      p->y += distance;
    if (d == DOWN)
      p->y -= distance;
    else{
      return;
    }
  }
}
/****************************************************************************************/
/**
 * @brief tests whether or not pieces p1 and p2 overlap.
 * @return true if pieces p1 and p2 have at least one cell in common and false otherwise.
 */

/********************************original function***************************************/
bool intersect(cpiece p1, cpiece p2){

  if (is_horizontal(p1) && is_horizontal(p2)){
    for (int i = get_x(p1); i < get_x(p1) + get_width(p1); ++i){           //i & j are counters incrementing respectively
      for (int j = get_x(p2); j < get_x(p2) + get_width(p2); ++j){         //the abscissa x of p1 and p2

	if (i == j && get_y(p1) == get_y(p2))
	  return true;
      }
    }
    return false;
  }
  else if (!is_horizontal(p1) && !is_horizontal(p2)){
    for (int i = get_y(p1); i < get_y(p1) + get_height(p1); ++i){           //i & j are counters incrementing respectively
      for (int j = get_y(p2); j < get_y(p2) + get_height(p2); ++j){         //the ordinate y of p1 & p2
	if (get_x(p1) == get_x(p2) && i == j)
	  return true;
      }
    }
    return false;
  }
  else if (is_horizontal(p1) && !is_horizontal(p2)){
    for (int i = get_x(p1); i < get_x(p1) + get_width(p1); ++i){             //i & j are counters incrementing respectively
      for (int j = get_y(p2); j < get_y(p2) + get_height(p2); ++j){          //the abscissa x of p1 and the ordinate y of p2
	if (i == get_x(p2) && get_y(p1) == j)
	  return true;
      }
    }
    return false;
  }
  else {
    for (int i = get_y(p1); i < get_y(p1) + get_height(p1); ++i){             //i & j are counters incrementing respectively
      for (int j = get_x(p2); j < get_x(p2) + get_width(p2); ++j){            //the ordinate y of p1 and the abscissa of p2
	if (get_x(p1) == j && i == get_y(p2))
	  return true;
      }
    }
    return false;
  }
  
}
/*****************************************************************************************/
/**
 * @brief Returns the abscissa of leftmost point of the piece p.
 */
int get_x(cpiece p){
  return p->x;
}

/**
 * @brief Returns the ordinate of lowest point of the piece p.
 */
int get_y(cpiece p){
  return p->y;
}

/**
 * @brief Returns the different of ordinates of the uppermost and the lowest points of the piece p.
 */
int get_height(cpiece p){
  if (p->horizontal)
    return 1;
  else{
    if (p->small)
      return 2;
    return 3;
  }
}

/**
 * @brief Returns the different of abscissas of the leftmost and the rightmost points of the piece p.
 */
int get_width(cpiece p){
  if (!p->horizontal)
    return 1;
  else{
    if (p->small)
      return 2;
    return 3;
  }  
}

/**
 * @brief Returns true if the piece is
 */
bool is_horizontal(cpiece p){
  return p->horizontal;
}

/////////////////// VERSION 2 /////////////////////////////

bool can_move_x(cpiece p){
  if(ishorizontal(p);
  return true;
  return false;
}
bool can_move_y(cpiece p){
  if(!ishorizontal(p))
  return true;
  return false;
}
/**
 * @brief Initialized piece structure
 * @param x,y: coordinates of the bottom left corner of the piece
 * @param move_x: indicates if the piece is allowed to move horizontally
 * @param move_y: indicates if the piece is allowed to move vertically
 * @return created piece at a given position
 */
piece new_piece (int x, int y, int width, int height, bool move_x, bool move_y){
  piece p = (piece)malloc(sizeof(struct piece_s));
  if (p == NULL){
    fprintf(stderr, "Allocation problem");
    exit(EXIT_FAILURE);
  }
  p->x = x;
  p->y = y;
  p->width=width;
  p->height=height;
  p->move_x=move_x;
  p->move_y=move_y;
   //p n'est pas  horizontal;
  if (!can_move_x(p))
    p->horizontal=false;
  else{
    if (p->height==2)
      p->small=true;
   p->small=false;
  }
   //p est pas horizontal;
   if (can_move_x(p))
     p->horizontal=true;
  else{
    if (p->width==2)
      p->small=true;
    p->small=false;
  }
  return p;
}





