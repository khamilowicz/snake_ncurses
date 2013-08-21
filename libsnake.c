#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

typedef struct{
  unsigned char y;
  unsigned char x;
  char ch;
}Pixel;

typedef struct{
  size_t size;
  Pixel segment[10];
}Snake;

void steer(Pixel*);

void prepare_screen()
{
  (void) initscr();
  (void) cbreak();       /* take input chars one at a time, no wait for \n */
keypad(stdscr, TRUE);  /* enable keyboard mapping */
  (void) nonl();    
}

void draw_snake(Snake snake){
  int i;
  for (i = 0; i < snake.size; i++)
  {
   move(snake.segment[i].y, snake.segment[i].x);
   addch(snake.segment[i].ch); 
 }
}

void print_pixel(Pixel pixel)
{
  char buffer[20];
  char info[26] = "Pixel: y-";
  snprintf(info, 26, "Pixel y-%i x-%i", pixel.y, pixel.x);
  addstr(info);
}

void print_pixels(Pixel* pixels, size_t size)
{
  int i = 0;
  for ( i; i < size; i++)
  {
    move(i,40);
    char nr[15];
    sprintf(nr, "Snake size: %i, %i: ", (int)size, i);
    addstr(nr);
    print_pixel(pixels[i]);
  }
}

void main_loop()
{
  int posy = 5;
  int posx = 5;

  Pixel current_pixel;
  current_pixel = (Pixel){posy, posx, 'b'};
  print_pixel(current_pixel);
  refresh();
  Snake snake;
  int i_current_segment = 0;
  int i = 0;
  // for (i; i < 10; i++) { snake.segment[i] = current_pixel;}
  //   snake.size = 10;
  snake.segment[0] = current_pixel;
  snake.size = 1;

  while(true){
    steer(&current_pixel);
    clear();
    snake.segment[i_current_segment++] = current_pixel;
    if(snake.size < 10){ snake.size++;}
    draw_snake(snake);
    print_pixels(snake.segment, snake.size);
    refresh();
    if(i_current_segment == snake.size){i_current_segment = 0;}
  }
}

void steer(Pixel* pixel){
  switch(getch()){
    case KEY_UP: { pixel->y--; break;}
    case KEY_DOWN: { pixel->y++; break;}
    case KEY_LEFT: { pixel->x--; break;}
    case KEY_RIGHT: { pixel->x++; break;}
    if (pixel->y < 0){ pixel->y = 0;}
    if (pixel->x < 0){ pixel->x = 0;}
  }
}

void clean()
{
  endwin();
  exit(0);
}

static void finish()
{
  endwin();
  exit(0);
}
