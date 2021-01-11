FLAGS = -Wall -g 
CC = gcc

all: frequency 

frequency: main.o
	$(CC) $(FLAGS) main.o -o frequency
			
main.o: main.c
	$(CC) $(FLAGS) -c main.c -o main.o
		
.PHONY: clean all

clean:
	rm frequency main.o