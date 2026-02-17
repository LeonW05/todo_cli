CC = gcc
CFLAGS = -Wall -Wextra

all: todo

todo: main.c
	$(CC) $(CFLAGS) -o todo main.c

clean:
	rm -f main.o todo