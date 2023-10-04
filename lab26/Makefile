CC = gcc
DEGUGGER = gdb
CFLAGS = -std=c17
FILE_OUT = lab
SOURCES = mystack.c main.c

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(FILE_OUT)

debug:
	$(CC) $(CFLAGS) -g $(SOURCES) -o $(FILE_OUT)
	$(DEGUGGER) $(FILE_OUT)

run:
	./$(FILE_OUT)
