all: DSSimul

DSSimul: main.o algorithms.o
	g++ -Wall -o  DSSimul main.o  algorithms.o 

main.o: main.c algorithms.h
	g++ -Wall -o main.o -c main.c
	

algorithms.o:  algorithms.c  algorithms.h 
	g++ -Wall -o  algorithms.o  -c  algorithms.c
	
clean:
	rm -f  main.o algorithms.o DSSimul
