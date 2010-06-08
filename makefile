Naufragos: tipos.o colisao.o desloc.o main.o mar.o 
	gcc -g colisao.o desloc.o main.o mar.o tipos.o `allegro-config --cflags --libs` -lm  -o Naufragos -ansi -pedantic -Wall

# Executavel gerado para testes
testes: tipos.o colisao.o desloc.o mainTestes.o mar.o 
	gcc -g colisao.o desloc.o mainTestes.o mar.o tipos.o  -lm -o testes -ansi -pedantic -Wall

tipos.o:  tipos.c  bib/tipos.h
	gcc -g -c tipos.c -ansi  -pedantic -Wall

colisao.o: colisao.c bib/tipos.h bib/colisao.h
	gcc -g -c colisao.c -lm  -ansi -pedantic -Wall

desloc.o: desloc.c bib/tipos.h bib/desloc.h
	gcc -g -c desloc.c -lm  -ansi -pedantic -Wall

main.o: main.c bib/tipos.h bib/colisao.h bib/desloc.h bib/mar.h
	gcc -g -c main.c `allegro-config --cflags --libs` -ansi  -pedantic -Wall

mainTestes.o: mainTestes.c bib/tipos.h bib/colisao.h bib/desloc.h bib/mar.h
	gcc -g -c mainTestes.c  -ansi -pedantic -Wall

mar.o: mar.c bib/tipos.h bib/mar.h bib/desloc.h bib/colisao.h
	gcc -g -c mar.c `allegro-config --cflags --libs` -ansi  -pedantic -Wall

# Limpeza

.PHONY: clean clean-temp real-clean
clean:
	rm *.o
clean-temp:
	rm *~
# Cuidado ao usar o make real-clean, pois ele removera TODO o conteudo da pasta!
real-clean:
	rm -r *
