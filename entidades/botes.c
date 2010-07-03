#include <stdlib.h>
#include <math.h>
#include "../bib/tipos.h"
#include "../bib/mar.h"
#include "../configurador/configs.h"

lista_botes geraBotes(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b)
{
	bote b1,b2;

	b1.atr.atualizada = 0;
	b1.atr.raio = R_BOTE;
	b1.jogador = 1;
	b1.vidas = vidas_max;
	b1.carga = 0;
/**
  	boteBorda(naufragos, &b1,l_max,c_max);
**/

	lista_b = insereBote(lista_b, b1);

	b2.atr.atualizada = 0;
	b2.atr.raio = R_BOTE;
	b2.jogador = 2;
	b2.vidas = vidas_max;
	b2.carga = 0;
/**
  	boteBorda(naufragos, &b2,l_max,c_max);
**/

	lista_b = insereBote(lista_b, b2);

	return lista_b;
}

void boteBorda(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b, lista_botes bote)
{

	int novaBorda;

	bote->atr.vel.x = (rand()%(int)((velocidade_maxima + 1 - velocidade_minima))) + velocidade_minima;
	bote->atr.vel.y = (rand()%(int)((velocidade_maxima + 1 - velocidade_minima))) + velocidade_minima;

	while(1)
	{
		novaBorda = rand()%4;
		if(novaBorda == 0) /* Canto superior esquerdo */
		{
			bote->atr.pos.x = bote->atr.raio;
			bote->atr.pos.y = bote->atr.raio;
		}
		else if(novaBorda == 1)  /* Canto superior direito */
		{
			bote->atr.pos.x = tela.comprimento - bote->atr.raio;
			bote->atr.pos.y = bote->atr.raio;
		}
		else if(novaBorda == 2) /* Canto inferior direito */
		{
			bote->atr.pos.x = tela.comprimento - bote->atr.raio;
			bote->atr.pos.y = tela.altura - bote->atr.raio;
		}
		else if(novaBorda == 3) /* Canto inferior esquerdo */
		{
			bote->atr.pos.x = bote->atr.raio;
			bote->atr.pos.y = tela.altura - bote->atr.raio;
		}

		if(validaPos(lista_p, lista_e, lista_b, NULL, NULL bote))
			break;
	}
}

