CC = gcc
CFLAGS = -g -Wall
GTKFLAGS = `pkg-config --cflags --libs gtk+-2.0`
EXES = $(basename $(wildcard *.c))

all:
	$(MAKE) $(EXES)

%: %.c
	$(CC) $(CFLAGS) $(GTKFLAGS) $@.c -o $@

clean:
	rm -f $(EXES) *.o
