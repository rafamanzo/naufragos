#include "bib/tipos.h"
#include "bib/mar.h"
#include "bib/desloc.h"
#include "bib/colisao.h"
#include "entidades/botes.h"
#include "entidades/pessoas.h"
#include "entidades/estaticos.h"
#include "configurador/configs.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <allegro.h>

#define VERCOLISAO if(COLISAO) circle(buffer, proximo->p.pos.x,proximo->p.pos.y ,proximo->p.raio, VERMELHO);
#define COLISAO 0 /* Se quiser ver os circulos da colisao setar 1 */

int validaPos(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b, pessoa * p, estatico * e, bote * b)
{
/*
Essa função recebe as listas de elementos do mar e apenas um tipo de estrutura apontada (pessoa, bote ou estatico). Os tipos que não forem o desejado serão passados como NULL.
A função verificará a possibilidade de criação da estrutura desejada em determinado lugar do mar, vendo se há outras estruturas lá.
OBS: se a estrutura for um bote, a existencia de pessoas não impossibilita a sua criação (recolhe as pessoas).
*/


	lista_pessoas aux_p;
	lista_estaticos aux_e;
	lista_botes aux_b;
	char tipo;

	aux_p = lista_p;
	aux_e = lista_e;
	aux_b = lista_b;

	if(p != NULL)
		tipo = 'p';
	if(e != NULL)
		tipo = 'e';
	if(b != NULL)
		tipo = 'b';

	/*Percorrendo a lista de pessoas (se não for bote!)*/

	if(tipo != 'b')
	{
		while(aux_p != NULL)
		{
			if(tipo == 'p')
			{

				if((aux_p->pss.atr.raio + p->atr.raio) >= distancia(aux_p->pss.atr.pos, p->atr.pos))
				{ 	
					/*Verifica se a pessoa a inserir não eh a mesma que está no meio do caminho na lista.*/
					if(p != &aux_p->pss)
						return 0;
				}
				aux_p = aux_p->prox;
			}

			else if(tipo == 'e')
			{
				
				if((aux_p->pss.atr.raio + e->raio) >= distancia(aux_p->pss.atr.pos, e->pos))
					return 0;

				aux_p = aux_p->prox;
			}
		}
	}

	/*Percorrendo a lista de estaticos*/

	while(aux_e != NULL)
	{
		if(tipo == 'p')
		{
			if((aux_e->stc.raio + p->atr.raio) >= distancia(aux_e->stc.pos, p->atr.pos))
				return 0;

			aux_e = aux_e->prox;
		}

		else if(tipo == 'e')
		{
			
			if((aux_e->stc.raio + e->raio) >= distancia(aux_e->stc.pos, e->pos))
			{
				/*Verifica se o estatico a inserir não eh o mesmo que está no meio do caminho na lista.*/

				if(e != &aux_e->stc)
					return 0;

				aux_e = aux_e->prox;
			}

		}

		else if(tipo == 'b')
		{
			if((aux_e->stc.raio + b->atr.raio) >= distancia(aux_e->stc.pos, b->atr.pos))
				return 0;

			aux_e = aux_e->prox;
		}

	}


	/*Percorrendo a lista de botes*/

	while(aux_b != NULL)
	{
		if(tipo == 'p')
		{

			if((aux_b->bt.atr.raio + p->atr.raio) >= distancia(aux_b->bt.atr.pos, p->atr.pos))
				return 0;

			aux_b = aux_b->prox;
		}

		else if(tipo == 'e')
		{
			
			if((aux_b->bt.atr.raio + e->raio) >= distancia(aux_b->bt.atr.pos, e->pos))
				return 0;
				
			aux_b = aux_b->prox;
		}

		else if(tipo == 'b')
		{
			if((aux_b->bt.atr.raio + b->atr.raio) >= distancia(aux_b->bt.atr.pos, b->atr.pos))
			{
				/*Verifica se o bote a inserir não eh o mesmo que está no meio do caminho na lista.*/
				if(b != &aux_b->bt)
					return 0;

				aux_b = aux_b->prox;
			}
		}
	}

	return 1;

}



fila atualizaMar(fila naufragos, int l_max, int c_max, double deltaT, int mkv)
{
	fila proximo = naufragos;
	
	/* Ver se não estão sendo gerados no mesmo lugar */

	while(proximo!=NULL) 
	{
		proximo->p.atualizada=0; 
		proximo = proximo->prox;
	} 
	
	naufragos = detectaColisao( naufragos, deltaT);		
	proximo = naufragos;
	
	while( proximo != NULL)
	{
		if(!proximo->p.atualizada)
		{
			if(mkv)
			{
				markov(&proximo->p,deltaT);
        			proximo->p.atualizada = 1;
			}				
			else
				movePessoa(&proximo->p,deltaT);

			/*Se for 0 eh o topo. 1 eh o chao. 2 eh a parede esquerda e 3 eh a parede direita.*/
			if( (proximo->p.pos.y - proximo->p.raio) < 0)
				colideComBorda(naufragos, &proximo->p, 0, 768, 1024);				
			else if( (proximo->p.pos.y + proximo->p.raio) > l_max)
				colideComBorda(naufragos, &proximo->p, 1, 768, 1024);
			else if( (proximo->p.pos.x - proximo->p.raio) < 0)
				colideComBorda(naufragos, &proximo->p, 2, 768, 1024);
			else if( (proximo->p.pos.x + proximo->p.raio) > c_max )
				colideComBorda(naufragos, &proximo->p, 3, 768, 1024);		
		}
		
		proximo = proximo -> prox;

	}
	
	return naufragos;
}

void imprimeMar(fila naufragos)
{
	fila proximo;
	BITMAP *buffer;

	buffer = create_bitmap(screen->w, screen->h);
  
	clear_to_color(buffer, AZUL);

	for(proximo = naufragos; proximo != NULL; proximo = proximo -> prox)
	{
		if( proximo->p.categoria == 'p' )
		{	
			circlefill(buffer, proximo->p.pos.x,proximo->p.pos.y ,proximo->p.raio, PRETO);                          
			/*line( buffer , proximo->p.pos.x , proximo->p.pos.y , proximo->p.pos.x+proximo->p.vel.x , proximo->p.pos.y-proximo->p.vel.y , VERMELHO ); Vetor velocidade */	
		}
		else if( proximo->p.categoria == 'r' )
		{	
      circlefill(buffer, proximo->p.pos.x,proximo->p.pos.y ,proximo->p.raio, MARROM);
			/*rectfill(buffer, (proximo->p.pos.x)-proximo->p.raio/sqrt(2),(proximo->p.pos.y)+proximo->p.raio/sqrt(2),(proximo->p.pos.x)+proximo->p.raio/sqrt(2),(proximo->p.pos.y)-proximo->p.raio/sqrt(2), MARROM);*/
			VERCOLISAO	
		}
		else if( proximo->p.categoria == 'a')
		{
      circlefill(buffer, proximo->p.pos.x,proximo->p.pos.y ,proximo->p.raio, VERDE);
			/*rectfill(buffer, (proximo->p.pos.x)-65, (proximo->p.pos.y)+60, (proximo->p.pos.x)+65, (proximo->p.pos.y) - 60, VERDE);*/
			VERCOLISAO	
		}
		else if( proximo->p.categoria == '1' )
		{
			triangle(buffer, (proximo->p.pos.x-15), (proximo->p.pos.y-17), (proximo->p.pos.x), (proximo->p.pos.y+20), (proximo->p.pos.x+15), (proximo->p.pos.y-17),LARANJA);
			VERCOLISAO		
		}

		else if( proximo->p.categoria == '2' )
		{
			triangle(buffer, (proximo->p.pos.x)-15, (proximo->p.pos.y)-17, (proximo->p.pos.x), (proximo->p.pos.y)+20, (proximo->p.pos.x)+15, (proximo->p.pos.y)-17,BRANCO);
			VERCOLISAO			
		}
	}
	
	blit(buffer, screen, 0, 0, 0, 0, screen->w, screen->h);  
	destroy_bitmap(buffer);

}

void liberaMar(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b)
{
	lista_pessoas aux_p;
	lista_estaticos aux_e;
	lista_botes aux_b;	


	while(lista_p != NULL)
	{
		aux_p = lista_p;
		lista_p = lista_p->prox;		
		free(aux_p);
	}

	while(lista_e != NULL)
	{
		aux_e = lista_e;
		lista_e = lista_e->prox;		
		free(aux_e);
	}

	while(lista_b != NULL)
	{
		aux_b = lista_b;
		lista_b = lista_b->prox;		
		free(aux_b);
	}
}

