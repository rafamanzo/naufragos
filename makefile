#argumentos de compilacao
CFLAGS = -ansi -pedantic -Wall -g
ALLEGRO = `allegro-config --cflags --libs`

#headers
ENTIDADES_H = entidades/pessoas.h entidades/estaticos.h entidades/botes.h

Naufragos: tipos.o colisao.o desloc.o main.o mar.o botes.o pessoas.o estaticos.o configurador.o bison.o flex.o 
	gcc colisao.o desloc.o main.o mar.o tipos.o pessoas.o estaticos.o botes.o bison.o flex.o configurador.o $(ALLEGRO) -lm -lfl -o Naufragos $(CFLAGS)

# Executavel gerado para testes
#testes: tipos.o colisao.o desloc.o mainTestes.o mar.o 
#	gcc -g colisao.o desloc.o mainTestes.o mar.o tipos.o  -lm -o testes -ansi -pedantic -Wall

tipos.o:  tipos.c  bib/tipos.h
	gcc -c tipos.c $(ALLEGRO) $(CFLAGS)

colisao.o: colisao.c bib/colisao.h bib/tipos.h bib/mar.h bib/desloc.h $(ENTIDADES_H) configurador/configs.h
	gcc -c colisao.c -lm $(CFLAGS)

desloc.o: desloc.c bib/tipos.h bib/desloc.h
	gcc -c desloc.c -lm $(ALLEGRO) $(CFLAGS)

main.o: main.c bib/tipos.h bib/colisao.h bib/desloc.h bib/mar.h $(ENTIDADES_H) configurador/configs.h
	gcc -c main.c $(ALLEGRO) $(CFLAGS)

#mainTestes.o: mainTestes.c bib/tipos.h bib/colisao.h bib/desloc.h bib/mar.h
#	gcc -c mainTestes.c $(CFLAGS)

mar.o: mar.c bib/mar.h bib/tipos.h bib/desloc.h bib/colisao.h $(ENTIDADES_H) configurador/configs.h
	gcc -c mar.c $(ALLEGRO) $(CFLAGS)

pessoas.o: entidades/pessoas.c bib/tipos.h entidades/pessoas.h bib/mar.h bib/desloc.h
	gcc -c entidades/pessoas.c $(ALLEGRO) $(CFLAGS) -lm

estaticos.o: entidades/estaticos.c bib/tipos.h bib/colisao.h entidades/estaticos.h configurador/configs.h
	gcc -c entidades/estaticos.c $(CFLAGS) -lm

botes.o: entidades/botes.c bib/tipos.h bib/mar.h entidades/botes.h configurador/configs.h
	gcc -c entidades/botes.c $(CFLAGS) -lm

configurador.o: configurador/configurador.c configurador/configurador.h configurador/configs.h
	gcc -c configurador/configurador.c -o configurador.o

flex.o: configurador/flex.c configurador/bison.c
	gcc -c configurador/flex.c -o flex.o

bison.o: configurador/bison.c configurador/configurador.h configurador/configs.h configurador/highscores.h
	gcc -c configurador/bison.c -o bison.o

configurador/flex.c: configurador/configurador.l configurador/configurador.h
	flex -oconfigurador/flex.c configurador/configurador.l

configurador/bison.c: configurador/configurador.y
	bison -d -oconfigurador/bison.c configurador/configurador.y


# Limpeza

.PHONY: clean clean-temp real-clean
clean:
	rm *.o
	rm configurador/bison.*
	rm configurador/flex.*
clean-temp:
	rm *~
# Cuidado ao usar o make real-clean, pois ele removera TODO o conteudo da pasta!
real-clean:
	rm -r *
