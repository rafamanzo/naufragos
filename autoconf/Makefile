autoconf: flex.o bison.o
	gcc flex.o bison.o -lfl -o autoconf -lm

flex.o: flex.c bison.c
	gcc -c flex.c

bison.o: bison.c
	gcc -c bison.c

flex.c: autoconf.l
	flex -oflex.c autoconf.l

bison.c: autoconf.y
	bison -d -obison.c autoconf.y

