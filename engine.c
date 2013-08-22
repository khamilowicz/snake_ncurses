typedef struct Direction
{
  unsigned char y;
  unsigned char x;
} Direction;

Direction left = (Direction){0,-1};
Direction right = (Direction){0,1};
Direction up = (Direction){-1,0};
Direction down = (Direction){1,0};
Direction *current_direction = &(Direction){0,0};

typedef struct Pixel{
  unsigned char y;
  unsigned char x;
  char ch;
}Pixel;

void game_over(){
  endwin();
  printf("GAME OVER\n");
  exit(0);
}


void steer(Pixel* pixel, int command){
  switch(command){
    case KEY_UP: { current_direction = &up; break;}
    case KEY_DOWN: { current_direction = &down; break;}
    case KEY_LEFT: { current_direction = &left; break;}
    case KEY_RIGHT: { current_direction = &right; break;}
  }
}


bool collision_pixels(Pixel pixel_1, Pixel pixel_2){
  if((pixel_1.x == pixel_2.x) 
  && (pixel_1.y == pixel_2.y)){ return true;}
    return false;
}

void draw_pixel(Pixel pixel){
  move(pixel.y, pixel.x);
  addch(pixel.ch);
}

void prepare_screen(){
  WINDOW *w = initscr();
  cbreak();
  nodelay(w, TRUE);
keypad(stdscr, TRUE);  /* enable keyboard mapping */
  (void) nonl();    
}

void print_pixel_info(Pixel pixel){
  char buffer[20];
  char info[26] = "Pixel: y-";
  snprintf(info, 26, "Pixel y-%i x-%i", pixel.y, pixel.x);
  addstr(info);
}

void move_in_direction(Pixel *pixel, Direction direction){
  pixel->x += direction.x;
  pixel->y += direction.y;
  if ((pixel->y < 0) 
    || (pixel->x < 0) 
    || (pixel->x > COLS) 
    || (pixel->y > LINES) ){ 
    game_over();}
}

bool check_colision(Pixel *pixel, size_t size){
  int i;
  int j = 0;
  for (i = 1; i < size; i++) {
    if(collision_pixels(pixel[i], pixel[j])){
      return true;
    }
  }
  return false;
}

void clean(){
  endwin();
  exit(0);
}

static void finish(){
  endwin();
  exit(0);
}

void put_in_random_place(Pixel *pixel){
  int rand_x = (int)floor(( rand() / (double)RAND_MAX) * COLS);
  int rand_y = (int)floor(( rand() / (double)RAND_MAX) * LINES);
  pixel->x = rand_x;
  pixel->y = rand_y;
}