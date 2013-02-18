CFLAGS = -ggdb
LDFLAGS = 
LIBS = -lc
CC = gcc
LD = gcc

OBJECTS = lexer.o main.o parser.o code_gen.o symbol_table.o

all: compiler

$(OBJECTS): %.o : %.c parse_table.h
	$(CC) -c $(CFLAGS) $< -o $@

compiler: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) $(LIBS) -o compiler

grammer.o: grammer.c 
	$(CC) -c $(CFLAGS) grammer.c -o grammer.o

grammer: grammer.o
	$(LD) $(LDFLAGS) grammer.o $(LIBS) -o grammer

parse_table.h: grammer
	./grammer > states.txt
clean:
	rm grammer.o $(OBJECTS) grammer compiler
