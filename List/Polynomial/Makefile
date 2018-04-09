main: main.o Polynomial.o
	clang main.o Polynomial.o -o main.out
main.o: main.c
	clang -c main.c
Polynomial.o: Polynomial.c
	clang -c Polynomial.c
clean:
	rm main.o Polynomial.o main.out
