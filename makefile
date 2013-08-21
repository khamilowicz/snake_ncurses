LIBS = -lncurses

all:
	gcc snake.c -o snake $(LIBS)
	gcc snake_test.c -o snake_test $(LIBS)