clean:
	rm -rf *.o scanner

build_lab scanner:
	gcc -c -o error.o error.c
	gcc -c -o node.o node.c
	gcc -c -o graph.o graph.c
	flex lab_1.l
	bison -d -t lab_1.y
	echo '#include "node.h"' | cat - lab_1.tab.h > temp && mv temp lab_1.tab.h
	gcc -c -o lex.yy.o lex.yy.c
	gcc -c -o main_lab_2.o main_lab_2.c
	gcc -c -o lab_1.tab.o lab_1.tab.c
	gcc main_lab_2.o lab_1.tab.o lex.yy.o node.o error.o graph.o -o scanner && chmod +x scanner

run: scanner
	./scanner testscan.txt testscan_2.txt
