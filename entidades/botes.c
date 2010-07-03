#include <stdlib.h>
#include <math.h>
#include "../bib/tipos.h"
#include "../bib/mar.h"
#include "../configurador/configs.h"
#include "botes.h"

lista_botes geraBotes(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b)
{
	bote b1,b2;

	b1.atr.atualizada = 0;
	b1.atr.raio = R_BOTE;
	b1.jogador = 1;
	b1.vidas = vidas_max;
	b1.carga = 0;

	boteBorda(lista_p, lista_e, lista_b, &b1);

	lista_b = insereBote(lista_b, b1);

	b2.atr.atualizada = 0;
	b2.atr.raio = R_BOTE;
	b2.jogador = 2;
	b2.vidas = vidas_max;
	b2.carga = 0;

 	boteBorda(lista_p, lista_e, lista_b, &b2);

	lista_b = insereBote(lista_b, b2);

	return lista_b;
}

void boteBorda(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b, bote *b)
{

	int novaBorda;

	b->atr.vel.x = (rand()%(int)((velocidade_maxima + 1 - velocidade_minima))) + velocidade_minima;
	b->atr.vel.y = (rand()%(int)((velocidade_maxima + 1 - velocidade_minima))) + velocidade_minima;

	while(!validaPos(lista_p, lista_e, lista_b, NULL, NULL, b))
	{
		novaBorda = rand()%4;
		if(novaBorda == 0) /* Canto superior esquerdo */
		{
			b->atr.pos.x = b->atr.raio;
			b->atr.pos.y = b->atr.raio;
		}
		else if(novaBorda == 1)  /* Canto superior direito */
		{
			bote->atr.pos.x = tela.comprimento - b->atr.raio;
			bote->atr.pos.y = b->atr.raio;
		}
		else if(novaBorda == 2) /* Canto inferior direito */
		{
			bote->atr.pos.x = tela.comprimento - b->atr.raio;
			bote->atr.pos.y = tela.altura - b->atr.raio;
		}
		else if(novaBorda == 3) /* Canto inferior esquerdo */
		{
			bote->atr.pos.x = bote->atr.raio;
			bote->atr.pos.y = tela.altura - b->atr.raio;
		}
	}
}

void moveBote(bote *b, double deltaT)
{
	int dir;
	double vel;

	vel = modulo(b->atr.vel);
  dir = direcao(b->atr.vel.x, b->atr.vel.y);

  	switch(dir)
	{
    	case L:
      		b->atr.pos.x += (int) vel*deltaT;
      		break;
    	case NE:
      		b->atr.pos.x += (int) vel*cos(M_PI/4)*deltaT;
      		b->atr.pos.y += (int) vel*sin(M_PI/4)*(-1)*deltaT;
      		break;
    	case N:
      		b->atr.pos.y += (int) vel*(-1)*deltaT;
      		break;
    	case NO:
      		b->atr.pos.x += (int) vel*cos(M_PI/4)*(-1)*deltaT;
      		b->atr.pos.y += (int) vel*sin(M_PI/4)*(-1)*deltaT;
      		break;
    	case O:
      		b->atr.pos.x += (int) vel*(-1)*deltaT;
      		break;
    	case SO:
      		b->atr.pos.x += (int) vel*cos(M_PI/4)*(-1)*deltaT;
      		b->atr.pos.y += (int) vel*sin(M_PI/4)*deltaT;
     		break;
    	case S:
      		b->atr.pos.y += (int) vel*deltaT;
      		break;
    	case SE:
      		b->atr.pos.x += (int) vel*cos(M_PI/4)*deltaT;
      		b->atr.pos.y += (int) vel*sin(M_PI/4)*deltaT;
      		break;
  	}
}


void colideBotes(bote *b1, bote *b2, double deltaT)
{
/*Colisao perfeitamente elastica entre objetos de mesma massa, suas direcoes e velocidades se invertem.*/
    
	vetor aux_vel;

	aux_vel = p1->atr.vel; 
	b1->atr.vel = p2->atr.vel;
	b2->atr.vel = aux_vel;

	moveBote(b1,deltaT);
	moveBote(b2,deltaT);

	if(distancia(b1->atr.pos, b2->atr.pos) > (b1->atr.raio + b2->atr.raio))
	{
	  	b1->atr.atualizada = 1;
	  	b2->atr.atualizada = 1;
 	}
  
}
