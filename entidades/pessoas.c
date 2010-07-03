#include <stdlib.h>
#include <math.h>
#include "../bib/tipos.h"
#include "../configurador/configs.h"
#include "pessoas.h"

lista_pessoas geraPessoas(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b, int numPessoas)
{
	int cont;
	pessoa p;

	for(cont = 0; cont < numPessoas; cont++)
	{
		p.atr.vel.x = (rand()%(int)((velocidade_maxima + 1 - velocidade_minima))) + velocidade_minima;
		p.atr.vel.y = (rand()%(int)((velocidade_maxima + 1 - velocidade_minima))) + velocidade_minima;

		p.atr.raio = R_PESS;		
		
		switch (rand()%4)
		{
			case 0:
				p.atr.pos.x = p.atr.raio;
				p.atr.pos.y = rand()%tela.altura - p.atr.raio;
				break;
			case 1:
				p.atr.pos.x = tela.comprimento;
				p.atr.pos.y = rand()%tela.altura - p.atr.raio;
				break;
			case 2:
				p.atr.pos.x = rand()%tela.comprimento - p.atr.raio;
				p.atr.pos.y = p.raio;
				break;
			case 3:
				p.atr.pos.x = rand()%tela.comprimento - p.atr.raio;
				p.atr.pos.y = tela.altura;
				break;
		}

		p.atr.atualizada = 0;

		if( validaPos(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b, &p, NULL, NULL) ) 
			lista_p = inserePessoa(lista_p, p);
    else
      cont--;
	}

	return lista_p;

}

void movePessoa(pessoa *p, double deltaT)
{
	int dir;
	double vel;

	vel = modulo(p->atr.vel);
  	dir = direcao(p->atr.vel.x, p->atr.vel.y);

  	switch(dir)
	{
    	case L:
      		p->atr.pos.x += (int) vel*deltaT;
      		break;
    	case NE:
      		p->atr.pos.x += (int) vel*cos(M_PI/4)*deltaT;
      		p->atr.pos.y += (int) vel*sin(M_PI/4)*(-1)*deltaT;
      		break;
    	case N:
      		p->atr.pos.y += (int) vel*(-1)*deltaT;
      		break;
    	case NO:
      		p->atr.pos.x += (int) vel*cos(M_PI/4)*(-1)*deltaT;
      		p->atr.pos.y += (int) vel*sin(M_PI/4)*(-1)*deltaT;
      		break;
    	case O:
      		p->atr.pos.x += (int) vel*(-1)*deltaT;
      		break;
    	case SO:
      		p->atr.pos.x += (int) vel*cos(M_PI/4)*(-1)*deltaT;
      		p->atr.pos.y += (int) vel*sin(M_PI/4)*deltaT;
     		break;
    	case S:
      		p->atr.pos.y += (int) vel*deltaT;
      		break;
    	case SE:
      		p->atr.pos.x += (int) vel*cos(M_PI/4)*deltaT;
      		p->atr.pos.y += (int) vel*sin(M_PI/4)*deltaT;
      		break;
  	}
}

void colidePessoas(pessoa *p1, pessoa *p2, double deltaT)
{
/*Colisao perfeitamente elastica entre objetos de mesma massa, suas direcoes e velocidades se invertem.*/
    
	vetor aux_vel;

	aux_vel = p1->atr.vel; 
	p1->atr.vel = p2->atr.vel;
	p2->atr.vel = aux_vel;

	movePessoa(p1,deltaT);
	movePessoa(p2,deltaT);

	if(distancia(p1->atr.pos, p2->atr.pos) > 5)
	{
  	p1->atr.atualizada = 1;
  	p2->atr.atualizada = 1;
	}
  
}

