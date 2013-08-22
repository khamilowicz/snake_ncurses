
#include "engine.c"
#include <ncurses.h>

#define _ENGINE_ 1




void prepare_screen();
static void finish();
void clean();
void steer(Pixel*, int command);
void draw_pixel(Pixel pixel);
void print_pixel_info(Pixel pixel);
void put_in_random_place(Pixel *pixel);
void move_in_direction(Pixel *pixel, Direction direction);
bool check_colision(Pixel *pixel, size_t size);


