main: main.o ALGraph.o VexQueue.o
	clang main.o ALGraph.o VexQueue.o -o main.out
main.o: main.c
	clang -c main.c
ALGraph.o: ALGraph.c 
	clang -c ALGraph.c
VexQueue.o: VexQueue.c
	clang -c VexQueue.c
clean:
	rm main.o ALGraph.o VexQueue.o main.out
