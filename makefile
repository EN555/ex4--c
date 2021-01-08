FLAGS = -Wall -g 
CC = gcc

all: frequency 

frequency: fd.o
	$(CC) $(FLAGS) fd.o -o frequency
			
fd.o: fd.c
	$(CC) $(FLAGS) -c fd.c -o fd.o
		
.PHONY: clean all

clean:
	rm frequency fd.o