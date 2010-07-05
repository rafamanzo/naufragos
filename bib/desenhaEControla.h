#include <allegro.h>

void imprimeMar(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b, double deltaT);
void controlaBote1(BITMAP *buffer, bote *boat, double deltaT);
void controlaBote2(BITMAP *buffer, bote *boat, double deltaT);
void imprimePessoas(BITMAP *buffer, lista_pessoas pessoas);
void imprimeEstaticos(BITMAP *buffer, lista_estaticos estat);
void imprimeCabecalho(BITMAP *buffer, lista_botes botes);
