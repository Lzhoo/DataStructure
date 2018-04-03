main: main.o Polynomial.o
	clang++ main.o Polynomial.o -o main
main.o: main.cpp Status.h Polynomial.h
	clang++ -c main.cpp
Polynomial.o: Polynomial.cpp Polynomial.h Status.h
	clang++ -c Polynomial.cpp
clean:
	rm main.o Polynomial.o main
