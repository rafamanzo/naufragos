#include <stdlib.h>
#include <math.h>
#include <allegro.h>
#include <stdio.h>
#include "../bib/tipos.h"
#include "../bib/desloc.h"
#include "../bib/mar.h"
#include "../configurador/configs.h"
#include "botes.h"

lista_botes geraBotes(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b)
{
	bote b1,b2;

	b1.atr.desenho = load_bitmap("imagens/bote1.bmp",desktop_palette);
  if(b1.atr.desenho == NULL){
    printf("1 Nao foi possivel carregar a imagem do bote...\n");
    exit(-1);
  }
	b1.atr.atualizada = 0;
	b1.atr.raio = R_BOTE;
	b1.atr.pos.x = rand()%tela.comprimento; 
	b1.atr.pos.y = rand()%tela.altura;
	b1.jogador = '1';
	b1.vidas = vidas_iniciais;
	b1.carga = 0;
	b1.pontos = 0;
	b1.ancora = '0';

	boteBorda(lista_p, lista_e, lista_b, &b1);

	lista_b = insereBote(lista_b, b1);
	printf("Inseriu o primeiro bote.\n");

	b2.atr.desenho = load_bitmap("imagens/bote2.bmp",desktop_palette);
  if(b2.atr.desenho == NULL){
    printf("Nao foi possivel carregar a imagem do bote...\n");
    exit(-1);
  }
	b2.atr.atualizada = 0;
	b2.atr.raio = R_BOTE;
	b2.atr.pos.x = rand()%tela.comprimento; /* MUDAR AQUI*/ 
	b2.atr.pos.y = rand()%tela.altura;
	b2.jogador = '2';
	b2.vidas = vidas_iniciais;
	b2.carga = 0;
	b2.pontos = 0;
	b2.ancora = '0';

 	boteBorda(lista_p, lista_e, lista_b, &b2);

	lista_b = insereBote(lista_b, b2);
	printf("Inseriu o segundo bote.\n");
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
			b->atr.pos.x = tela.comprimento - b->atr.raio;
			b->atr.pos.y = b->atr.raio;
		}
		else if(novaBorda == 2) /* Canto inferior direito */
		{
			b->atr.pos.x = tela.comprimento - b->atr.raio;
			b->atr.pos.y = tela.altura - b->atr.raio;
		}
		else if(novaBorda == 3) /* Canto inferior esquerdo */
		{
			b->atr.pos.x = b->atr.raio;
			b->atr.pos.y = tela.altura - b->atr.raio;
		}
	}
}


void colideBotes(bote *b1, bote *b2, double deltaT)
{
/*Colisao perfeitamente elastica entre objetos de mesma massa, suas direcoes e velocidades se invertem.*/
    
	vetor aux_vel;

	aux_vel = b1->atr.vel; 
	b1->atr.vel = b2->atr.vel;
	b2->atr.vel = aux_vel;

	moveBote(direcao(b1->atr.vel.x, b1->atr.vel.y),0,b1,deltaT);
	moveBote(direcao(b2->atr.vel.x, b2->atr.vel.y),0,b2,deltaT);

	if(distancia(b1->atr.pos, b2->atr.pos) > (b1->atr.raio + b2->atr.raio))
	{
	  	b1->atr.atualizada = 1;
	  	b2->atr.atualizada = 1;
 	}
  
}

void moveBote(int dir, double aceleracao, bote *boat, double deltaT)
{
 double vel;

	vel = (modulo(boat->atr.vel)+aceleracao);

  	switch(dir)
	{
    	case L:
      		boat->atr.vel.x = (int) vel;
      		boat->atr.vel.y = 0;
      		boat->atr.pos.x += (int) vel*deltaT;
      		break;
    	case NE:
      		boat->atr.vel.x = vel*cos(M_PI/4);
      		boat->atr.vel.y = vel*sin(M_PI/4);
      		boat->atr.pos.x += (int) vel*cos(M_PI/4)*deltaT;
      		boat->atr.pos.y -= (int) vel*sin(M_PI/4)*deltaT;
      		break;
    	case N:
      		boat->atr.vel.x = 0;
      		boat->atr.vel.y = vel;
      		boat->atr.pos.y -= (int) vel*deltaT;
      		break;
    	case NO:
      		boat->atr.vel.x = vel*cos(M_PI/4)*(-1);
      		boat->atr.vel.y = vel*sin(M_PI/4);
      		boat->atr.pos.x += (int) vel*cos(M_PI/4)*(-1)*deltaT;
      		boat->atr.pos.y -= (int) vel*sin(M_PI/4)*deltaT;
      		break;
    	case O:
      		boat->atr.vel.x = vel*(-1);
      		boat->atr.vel.y = 0;
      		boat->atr.pos.x -= (int) vel*deltaT;
      		break;
    	case SO:
      		boat->atr.vel.x = vel*cos(M_PI/4)*(-1);
      		boat->atr.vel.y = vel*sin(M_PI/4)*(-1);
      		boat->atr.pos.x += (int) vel*cos(M_PI/4)*(-1)*deltaT;
      		boat->atr.pos.y -= (int) vel*sin(M_PI/4)*(-1)*deltaT;
     		break;
    	case S:
      		boat->atr.vel.x = 0;
      		boat->atr.vel.y = vel*(-1);
      		boat->atr.pos.y -= (int) vel*(-1)*deltaT;
      		break;
    	case SE:
      		boat->atr.vel.x = vel*cos(M_PI/4);
      		boat->atr.vel.y = vel*sin(M_PI/4)*(-1);
      		boat->atr.pos.x += (int) vel*cos(M_PI/4)*deltaT;
      		boat->atr.pos.y -= (int) vel*sin(M_PI/4)*(-1)*deltaT;
      		break;
  	}
}

double rotacaoBote(int dir)
{
  	switch(dir)
	{
    	case L:
		return itofix(64);
    	case NE:
		return itofix(32);
    	case N:
		return itofix(0);
     	case NO:
		return itofix(-32);
    	case O:
		return itofix(-64); 		
    	case SO:
      		return itofix(-96);
    	case S:
   		return itofix(128);
    	case SE:
      		return itofix(96); 
   	}

 return 0.0;
}
