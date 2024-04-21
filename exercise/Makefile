out: Progetto.o treeChar.o
	clang Progetto.o treeChar.o -o algorithm
Progetto.o: treeChar.h Progetto.c
	clang -c Progetto.c
treeChar.o: treeChar.h treeChar.c
	clang -c treeChar.c
