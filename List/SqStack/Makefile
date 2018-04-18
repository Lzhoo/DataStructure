editor: editor.o Stack_Sq.o
	clang editor.o Stack_Sq.o -o editor.out
main: main.o Stack_Sq.o
	clang main.o Stack_Sq.o -o main.out
editor.o: editor.c
	clang -c editor.c
main.o: main.c
	clang -c main.c
Stack_Sq.o: Stack_Sq.c
	clang -c Stack_Sq.c
clean:
	rm main.o Stack_Sq.o main.out
