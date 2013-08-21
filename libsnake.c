#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#define MAX_SNAKE_SIZE 10
#define SKIP_FRAME 20000
#define NO_INPUT -1

typedef struct{
  unsigned char y;
  unsigned char x;
  char ch;
}Pixel;

typedef struct{
  size_t size;
  Pixel segment[MAX_SNAKE_SIZE];
}Snake;

void steer(Pixel*, int command);
void draw_pixel(Pixel pixel);

void prepare_screen(){
  WINDOW *w = initscr();
  cbreak();
  nodelay(w, TRUE);
  keypad(stdscr, TRUE);  /* enable keyboard mapping */
  (void) nonl();    
}

void draw_pixel(Pixel pixel){
  move(pixel.y, pixel.x);
  addch(pixel.ch);
}

void draw_snake(Snake snake){
  int i;
  for (i = 0; i < snake.size; i++){
    draw_pixel(snake.segment[i]);
  }
}

void print_pixel_info(Pixel pixel){
  char buffer[20];
  char info[26] = "Pixel: y-";
  snprintf(info, 26, "Pixel y-%i x-%i", pixel.y, pixel.x);
  addstr(info);
}

void print_pixels_info(Pixel* pixels, size_t size){
  int i = 0;
  for ( i; i < size; i++){
    move(i,40);
    char nr[15];
    sprintf(nr, "Snake size: %i, %i: ", (int)size, i);
    addstr(nr);
    print_pixel_info(pixels[i]);
  }
}

void steer(Pixel* pixel, int command){
  switch(command){
    case KEY_UP: { pixel->y--; break;}
    case KEY_DOWN: { pixel->y++; break;}
    case KEY_LEFT: { pixel->x--; break;}
    case KEY_RIGHT: { pixel->x++; break;}
    if (pixel->y < 0){ pixel->y = 0;}
    if (pixel->x < 0){ pixel->x = 0;}
  }
}

void clean(){
  endwin();
  exit(0);
}

static void finish(){
  endwin();
  exit(0);
}

void change_segment(Snake *snake, Pixel pixel, int n){
  snake->segment[n] = pixel;
  if(snake->size < MAX_SNAKE_SIZE){ snake->size++;}
}

void main_loop(){
  int posy = 5;
  int posx = 5;
  int i_current_segment = 0;
  int frame = 0;

  Pixel current_pixel;
  current_pixel = (Pixel){posy, posx, 'b'};
  Snake snake;
  snake.segment[0] = current_pixel;
  snake.size = 1;
  
  print_pixel_info(current_pixel);
  refresh();

  while(true){
    frame++;
    int command = getch();
    if((frame == SKIP_FRAME) || (command != NO_INPUT)){
     steer(&current_pixel, command);
     clear();
     move(2,2);
     char nr[15];
     sprintf(nr, "%i", command);
     addstr(nr);
     if(command != NO_INPUT){
       change_segment(&snake, current_pixel, i_current_segment++);
     }
     draw_snake(snake);
     print_pixels_info(snake.segment, snake.size);
     refresh();
     i_current_segment %= MAX_SNAKE_SIZE;
     frame = 0;
   }
 }
}