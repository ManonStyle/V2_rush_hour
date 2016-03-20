#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "game.h"
#include "piece.h"



struct dir_option_s{
  char name[6];
  dir option;
};

typedef struct dir_option_s dir_option;
dir_option direction[] = {{"up",UP},{"down",DOWN},{"right",RIGHT},{"left",LEFT}};


struct game_option_s{
  char name[4];
  char file[30];
};

typedef struct game_option_s game_option;
game_option game_chose[] = {{"-rh", "game_rh.txt"},{"-ar", "game_ar.txt"}};



void print_line_empty(game g, int y, bool i){
  for(int x=0; x<game_width(g); ++x){
    int piece_num = game_square_piece (g, x, y);
    if(piece_num != -1){
      if(game_square_piece (g, x-1, y) == piece_num)
	printf("       ");
      else
	printf("|      ");
    }
    else
      printf("|      ");
  }
  // p is the gost piece for indicate the current exit.
  cpiece p = game_piece(g, game_nb_pieces(g));
  if(y >= get_y(p) && y < get_y(p) +get_height(p)){
    if(y == get_y(p) || y == get_y(p)+get_height(p)-1){
      if(i){
	if(y == get_y(p))
	  printf("------\n");
	else
	  printf("\n");
      }
      else{
	if(y == get_y(p)+get_height(p)-1)
	  printf("------\n");
	else
	  printf("\n");
      }
    }
    else
      printf("\n");
  }
  else
    printf("|\n");
}


void print_line(game g, int y){
  for(int x=0; x<game_width(g); ++x){
    int piece_num = game_square_piece (g, x, y);
    if(piece_num != -1){
      if(game_square_piece (g, x-1, y) == piece_num)
	printf("   %2d  ", piece_num);
      else
	printf("|  %2d  ", piece_num);
    }
    else
      printf("|      ");
  }
  // p is the gost piece for indicate the current exit.
  cpiece p = game_piece(g, game_nb_pieces(g));
  if(y >= get_y(p) && y < get_y(p)+get_height(p)){
    printf(" exit \n");
  }
  else
    printf("|\n");
}



void print_line_end(game g, int y){
  int piece_num = game_square_piece (g, 0, y);  
  if(piece_num != -1){
    if(game_square_piece (g, 0, y-1) == piece_num)
      printf("|      ");
    else
      printf("|------");
  }
  else
    printf("|------");
  for(int x=1; x<game_width(g); ++x){
    piece_num = game_square_piece (g, x, y);
    if(piece_num != -1){
      if(game_square_piece (g, x, y-1) == piece_num)
	printf("-      ");
      else
	printf("-------");
    }
    else
      printf("-------");
  }
  // p is the gost piece for indicate the current exit.
  cpiece p = game_piece(g, game_nb_pieces(g));
  if(y > get_y(p) && y < get_y(p)+get_height(p)){
    printf(" exit\n");
  }
  else
    printf("|\n");
}



// Print the board of the current game in the terminal
void print_game(game g){
  for(int x=0; x<game_width(g); ++x)
    printf("-------");
  printf("-\n");
  for(int y= game_height(g)-1; y>0; --y){ 
    print_line_empty(g, y, 0);
    print_line(g, y);
    print_line_empty(g, y, 1);
    print_line_end(g, y);
  }
  print_line_empty(g, 0, 0);
  print_line(g, 0);
  print_line_empty(g, 0, 1);
  for(int x=0; x<game_width(g); ++x)
    printf("-------");
  printf("-\n");
}



game init_game(int level, char* file){
  FILE* f = fopen(file, "r");
  if(f == NULL)
    exit(EXIT_FAILURE);
  char tmp[100]; 
  for(int i=0; i<level; ++i){
    if(!fgets(tmp, 100, f)){
      fprintf(stderr, "There is no level %d\n", level);
      exit(EXIT_FAILURE);
    }
  }
  const char limit[2] = ".";
  char* splited = strtok(tmp, limit);
  int g_width = atoi(splited);
  splited = strtok(NULL, limit);
  int g_height = atoi(splited);
  splited = strtok(NULL, limit);
  int nb_pieces = atoi(splited);
  piece pieces[nb_pieces+1];
  char value[1];
  for(int i=0; i<=nb_pieces; ++i){
    splited = strtok(NULL, limit);
    value[0] = splited[0];
    int x = atoi(value);
    value[0] = splited[1];
    int y = atoi(value);
    value[0] = splited[2];
    int width = atoi(value);
    value[0] = splited[3];
    int height = atoi(value);
    value[0] = splited[4];
    bool move_x = atoi(value);
    value[0] = splited[5];
    bool move_y = atoi(value);
    pieces[i] = new_piece(x, y, width, height, move_x, move_y);
  }
  fclose(f);
  game g = new_game(g_width, g_height, nb_pieces, pieces);
  for(int i=0; i<=nb_pieces; ++i)
    delete_piece(pieces[i]);
  return g;
}


//Use the gost piece for reference the current exit
bool can_move(game g, int piece_num){
  cpiece p = game_piece(g, piece_num);
  int x = get_x(p);
  int y = get_y(p);
  bool right = true;
  bool left = true;
  bool up = true;
  bool down = true;
  if(!can_move_x(p)){
    right = false;
    left = false;
  }
  else{
    for(int i=0; i<get_height(p); ++i){
      if(game_square_piece(g, x-1, y+i) != -1)
	left = false;
      if(game_square_piece(g, x+get_width(p), y+i) != -1)
	right = false;
    }
  }
  if(!can_move_y(p)){
    up = false;
    down = false;
  }
  else{
    for(int i=0; i<get_width(p); ++i){
      if(game_square_piece(g, x+i, y-1) != -1)
	down = false;
      if(game_square_piece(g, x+i, y+get_height(p)) != -1)
	up = false;
    }
  }
  return right || left || down || up;
}



int take_piece_num(game g, char* buf, int* piece_num){
  while(true){
    printf("What piece do you want to move?\n");
    read(0, buf, sizeof(char)*100);
    if(strcmp(buf, "cancel") == 10)
      break;
    if(strcmp(buf, "exit") == 10)
      return -1;
    if(strcmp(buf, "restart") == 10)
      return -2;
    if(buf[0]<48 || buf[0]>=48+game_nb_pieces(g) || buf[1] != 10)
      printf("Write a number between 0 and %dt\tor write cancel or exit.\n",game_nb_pieces(g)-1);
    else{
      *(piece_num) = atoi(buf);
      if(!can_move(g,*(piece_num)))
	printf("The piece %d cannot move.\n", *(piece_num));
      else
	return 1;
    }
  }
  return 0;
}


bool not_good_direction(int piece_num, char* src){
  printf("The piece %d cannot move to %s\n", piece_num, src);
  return false;
}


bool is_good_direction(game g, int piece_num, dir d){
  cpiece p =  game_piece(g, piece_num);
  int x = get_x(p);
  int y = get_y(p);
//Verify if the piece is not nears the limit board and if there is not an other piece sticks to her
  if(d == RIGHT){
    if(!can_move_x(p))
      return not_good_direction(piece_num, "right");
    if(x+get_width(p) >= game_width(g))
      return not_good_direction(piece_num, "right");
    for(int i=0; i<get_height(p); ++i){
      if(game_square_piece(g, x+get_width(p),y+i) != -1)
	return not_good_direction(piece_num, "right");
    }
  }
  if(d == LEFT){
    if(!can_move_x(p))
      return not_good_direction(piece_num, "left");
    if(x-1 < 0)
      return not_good_direction(piece_num, "left");
    for(int i=0; i<get_height(p); ++i){
      if(game_square_piece(g, x-1, y+i) != -1)
	return not_good_direction(piece_num, "left");
    }
  }
  if(d == UP){
    if(!can_move_y(p))
      return not_good_direction(piece_num, "up");
    if(y+get_height(p) >= game_height(g))
      return not_good_direction(piece_num, "up");
    for(int i=0; i<get_width(p); ++i){    
      if(game_square_piece(g, x+i, y+get_height(p)) != -1)
	return not_good_direction(piece_num, "up");
    }
  }
  if(d == DOWN){
    if(!can_move_y(p))
      return not_good_direction(piece_num, "down");
    if(y-1 < 0)
      return not_good_direction(piece_num, "down");
    for(int i=0; i<get_width(p); ++i){
      if(game_square_piece(g, x, y-1) != -1)
	return not_good_direction(piece_num, "down");
    }
  }
  return true;
}



int is_dir_option(char* str){
  //Verify if the string str is an option's name of direction.
  for(int i=0; i<4; ++i){
    if(strcmp(str, direction[i].name) == 10)
      return i;
  }
  return -1;
}




int take_direction(game g, int piece_num, char* buf, dir* d){
  while(true){
    printf("In what direction?\n");
    read(0, buf,  sizeof(char)*100);
    if(strcmp(buf, "cancel") == 10)
      break;
    if(strcmp(buf, "exit") == 10)
      return -1;
    if(strcmp(buf, "restart") == 10)
      return -2;
    int option_num = is_dir_option(buf);
    if(option_num == -1)
      printf("Write one of those direction: up, down, right, left\tor write cancel or exit.\n");
    else{
      *(d) = direction[option_num].option;
      if(is_good_direction(g, piece_num, *(d)))
	return 1;
    }
  }
  return 0;
}



int take_number_case(game g, int piece_num, dir d, char* buf, int* distance){
  while(true){
    bool good = true;
    printf("How many case?\n");
    read(0, buf,  sizeof(char)*100);
    if(strcmp(buf, "cancel") == 10)
      break;
    if(strcmp(buf, "exit") == 10)
      return -1;
    if(strcmp(buf, "restart") == 10)
      return -2;
    if(d == RIGHT || d == LEFT){
      if(buf[0]<48 || buf[0]>=48+game_width(g) || buf[1] != 10){
	printf("Write a number between 0 and %d\tor write cancel or exit.\n",game_width(g));
	good = false;
      }
    }
    else{
      if(buf[0]<48 || buf[0]>=48+game_height(g) || buf[1] != 10){
	printf("Write a number between 0 and %d\tor write cancel or exit.\n",game_height(g));
	good = false;
      }
    }
    if(good){
      *(distance) = atoi(buf);
      if(!play_move(g, piece_num, d, *(distance)))
	printf("The piece %d cannot move of %d case(s).\n", piece_num, *(distance));
      else{
	return 1;
      }
    }
  }
  return 0;
}



void usage(char* str){
  fprintf(stderr, "Usage: %s -game <int level>\n", str);
  fprintf(stderr, "game option:\n-rh: rush hour\n-ar: ane rouge\n");
  return exit(EXIT_FAILURE);
}



int main(int argc, char* argv[]){
  if(argc != 3)
    usage(argv[0]);
  char file[30];
  file[0] = '\0';
  for(int i=0; i<2; ++i){
    if(strcmp(argv[1], game_chose[i].name) == 0){
      strcpy(file, game_chose[i].file);
      break;
    }
  }
  if(strlen(file) == 0)
    usage(argv[0]);
  int level = atoi(argv[2]);
  if(level <= 0)
    usage(argv[0]);
  game g = init_game(level, file);
  char buf[3][100];
  int piece_num;
  dir d;
  int distance;
  int back_code;
  while(!game_over_hr(g)){
    bool good = false;
    while(!good){
      //Loop for the break of cancel instruction
      while(!good){
	system("clear");
	print_game(g);
	printf("Move the pieces for free the piece 0 to the exit:\n");
	printf("Write 'exit' for quit the game, 'cancel' for restart the current move or 'restart' for restart all the level game.\n");
	printf("Total move: %d\n",game_nb_moves(g));
	//First loop to take the number piece that you want to move
	back_code = take_piece_num(g, buf[0], &(piece_num));
	if(back_code == 0)
	  break;
	if(back_code == -1)
	  return EXIT_SUCCESS;
	if(back_code == -2){
	  delete_game(g);
	  g = init_game(level, file);
	  break;
	}
	//Second loop to take the direction where you want to move
	back_code = take_direction(g, piece_num, buf[1], &(d));
	if(back_code == 0)
	  break;
	if(back_code == -1)
	  return EXIT_SUCCESS;
	if(back_code == -2){
	  delete_game(g);
	  g = init_game(level, file);
	  break;
	}
	//Third loop to take the number of case that need for the move
	back_code = take_number_case(g, piece_num, d, buf[2], &(distance));
	if(back_code == 0)
	  break;
	if(back_code == -1)
	  return EXIT_SUCCESS;
	if(back_code == -2){
	  delete_game(g);
	  g = init_game(level, file);
	  break;
	}
	good = true;
      }
    }
  }
  system("clear");
  print_game(g);
  printf("CONGRATULATION\nYou won in %d moves\n", game_nb_moves(g));
  delete_game(g);
  return EXIT_SUCCESS;
}
