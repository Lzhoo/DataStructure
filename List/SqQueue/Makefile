main: main.o Queue_Sq.o
	clang main.o Queue_Sq.o -o main.out
main.o: main.c
	clang -c main.c
Queue_Sq.o: Queue_Sq.c
	clang -c Queue_Sq.c
clean:
	rm main.o Queue_Sq.o main.out