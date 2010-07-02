configurador: flex.o bison.o
	gcc flex.o bison.o -lfl -o configurador

flex.o: flex.c bison.c
	gcc -c flex.c

bison.o: bison.c
	gcc -c bison.c

flex.c: configurador.l
	flex -oflex.c configurador.l

bison.c: configurador.y
	bison -d -obison.c configurador.y

