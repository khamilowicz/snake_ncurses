#include <stdlib.h>
#include <signal.h>

#include "snake.h"

int main(int argc, char const *argv[])
{
  (void) signal(SIGINT, finish);
  prepare_screen();
  main_loop();
  clean();
  return 0;
}
