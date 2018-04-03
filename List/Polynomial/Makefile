main: main.o Polynomial.o
	clang main.o Polynomial.o -o main
main.o: main.c Status.h Polynomial.h
	clang -c main.c
Polynomial.o: Polynomial.c Polynomial.h Status.h
	clang -c Polynomial.c
clean:
	rm main.o Polynomial.o main
