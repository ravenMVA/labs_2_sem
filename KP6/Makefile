CC = gcc
DEGUGGER = gdb
CFLAGS = -std=c17
FILE_OUT = lab
SOURCES = data.c main.c

all:
	$(CC) $(CFLAGS) data.c rand.c -o rand.out
	$(CC) $(CFLAGS) data.c tobin.c -o tobin.out
	$(CC) $(CFLAGS) $(SOURCES) -o $(FILE_OUT)

rand:
	$(CC) $(CFLAGS) data.c rand.c -o rand.out

tobin:
	$(CC) $(CFLAGS) data.c tobin.c -o tobin.out

debug:
	$(CC) $(CFLAGS) -g $(SOURCES) -o $(FILE_OUT)
	$(DEGUGGER) $(FILE_OUT)

run:
	./$(FILE_OUT)