CC = gcc
CFLAGS = -Wall -Wextra

ifdef OS
   RM = del /Q
   EXT = .exe
else
   RM = rm -f
   EXT =
endif

all: todo

todo: main.c
	$(CC) $(CFLAGS) -o todo$(EXT) main.c

clean:
	$(RM) todo$(EXT)