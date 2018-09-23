main: main.o BiTree.o BiTreeQueue.o
	clang main.o BiTree.o BiTreeQueue.o -o main.out
main.o: main.c
	clang -c main.c
BiTree.o: BiTree.c
	clang -c BiTree.c
BiTreeQueue.o: BiTreeQueue.c
	clang -c BiTreeQueue.c
clean:
	rm main.o BiTree.o BiTreeQueue.o main.out