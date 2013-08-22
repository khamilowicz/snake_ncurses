#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <math.h>

#include "engine.h"

#define MAX_SNAKE_SIZE 100
#define SKIP_FRAME 35000
#define NO_INPUT -1

typedef struct Snake{
  size_t size;
  Pixel segment[MAX_SNAKE_SIZE];
} Snake;

// void change_snake_size(Snake *snake, int n);

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

void draw_snake(Snake snake){
  int i;
  for (i = 0; i < snake.size; i++){
    draw_pixel(snake.segment[i]);
  }
}

void change_snake_size(Snake *snake, int n){
  if((snake->size < MAX_SNAKE_SIZE) && (snake->size + 1 == n)){ snake->size++;}
}

void change_segment(Snake *snake, Pixel pixel, int n){
  change_snake_size(snake, n);
  snake->segment[n] = pixel;
}

void main_loop(){
  int posy = 5;
  int posx = 5;
  int i_current_segment = 0;
  int frame = 0;
  current_direction = &down;

  Pixel current_pixel;
  current_pixel = (Pixel){posy, posx, 'b'};
  Pixel fruit;
  fruit.ch = '@';
  put_in_random_place(&fruit);
  Snake snake;
  snake.segment[0] = current_pixel;
  snake.size = 1;

  print_pixel_info(current_pixel);
  refresh();

  bool pause = false;
  bool collision = false;

  while(true){
    frame++;
    int command = getch();
    if(command == 'p'){ pause = !pause; }
    if(!pause && ((frame == SKIP_FRAME) || (command != NO_INPUT))){
      steer(&current_pixel, command);
      move_in_direction(&current_pixel, *current_direction);
      if(command == 'a'){ change_snake_size(&snake, snake.size+1); }
      if(command == 'q'){ game_over(); }


      clear();
      change_segment(&snake, current_pixel, i_current_segment++);
      if(check_colision(snake.segment, snake.size)){ game_over(); }
      draw_snake(snake);
      draw_pixel(fruit);
      // print_pixels_info(snake.segment, snake.size);
      int i;
      while(!collision && (i < snake.size)){
        if (collision_pixels(fruit, snake.segment[i])){collision = true;}
        i++;
      }
      i = 0;
     
      if(collision){
        put_in_random_place(&fruit);
        change_snake_size(&snake, snake.size+1);
        collision = !collision;
      }

     move(20,10);
      print_pixel_info(fruit);
      move(21,10);
      print_pixel_info(snake.segment[0]);

      refresh();
      i_current_segment %= snake.size;
      frame = 0;
    }
  }
}