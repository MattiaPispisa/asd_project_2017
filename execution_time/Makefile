out: executionTime.o treeChar.o
	clang executionTime.o treeChar.o -o time -lm
executionTime.o: treeChar.h executionTime.c
	clang -c executionTime.c
treeChar.o: treeChar.h treeChar.c
	clang -c treeChar.c
