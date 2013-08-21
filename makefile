LIBS = -lncurses

all:
	gcc snake.c -o snake $(LIBS)