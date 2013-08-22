#include <stdlib.h>
#include <signal.h>

#include "snake.h"

#ifndef _ENGINE_
#include "engine.h"
#endif

int main(int argc, char const *argv[])
{
  (void) signal(SIGINT, finish);
  prepare_screen();
  main_loop();
  clean();
  return 0;
}
