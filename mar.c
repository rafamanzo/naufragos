#include "bib/tipos.h"
#include "bib/mar.h"
#include "bib/desloc.h"
#include "bib/colisao.h"
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



lista_pessoas geraPessoas(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b, int numPessoas, int l_max, int c_max)
{
	int cont;
	pessoa p;

	for(cont = 0; cont < numPessoas; cont++)
	{
		p.atr.vel.x = (rand()%(int)((velocidade_maxima + 1 - velocidade_minima))) + velocidade_minima;
		p.atr.vel.y = (rand()%(int)((velocidade_maxima + 1 - velocidade_minima))) + velocidade_minima;

		p.raio = R_PESS;		
		
		switch (rand()%4)
		{
			case 0:
				p.atr.pos.x = p.raio;
				p.atr.pos.y = rand()%l_max - p.raio;
				break;
			case 1:
				p.atr.pos.x = c_max;
				p.atr.pos.y = rand()%l_max - p.raio;
				break;
			case 2:
				p.atr.pos.x = rand()%c_max - p.raio;
				p.atr.pos.y = p.raio;
				break;
			case 3:
				p.atr.pos.x = rand()%c_max - p.raio;
				p.atr.pos.y = l_max;
				break;
		}

		p.atr.atualizada = 0;

		if( validaPos(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b, &p, NULL, NULL) ) 
			lista_p = inserePessoa(lista_p, p);

      		else cont--;
	}

	return lista_p;

}

lista_estaticos geraAsimov(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b, int l_max, int c_max)
{
	estatico asimov;

	asimov.pos.x = rand()%c_max;
	asimov.pos.y = rand()%l_max;
	asimov.raio = R_ASIMOV;
	asimov.tipo = 'a';

  	while( !validaPos(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b, NULL, &asimov, NULL) )
	{
	  asimov.pos.x = rand()%c_max;
	  asimov.pos.y = rand()%l_max;
  	}

	lista_e = insereObjeto(lista_e, asimov);

	return lista_e;

}


lista_estaticos geraRecifes(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b, int numRecifes, int l_max, int c_max)
{
	int cont, decideTam, raioMedio;
	estatico r;

	raioMedio = sqrt(2*D)/2;

	for(cont = 0; cont < numRecifes; cont++)
	{
		r.atr.pos.x = rand()%c_max;
		r.atr.pos.y = rand()%l_max;
		r.tipo = 'r';

		decideTam = rand()%3; 

		if( decideTam == 0 ) 	 /* RECIFES MEDIOS */
			r.raio = raioMedio;

		else if( decideTam == 1) /* RECIFES PEQUENOS */
			while( (r.raio = rand()%raioMedio) < 5 ); /* Garante que o raio não sera 0 ou muito pequeno */

		else			 /* RECIFES GRANDES */
			r.raio = raioMedio + rand()%raioMedio;/* No maximo será do dobro do tamanho do medio */

						    
		if( validaPos(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b, NULL, &r, NULL) ) 
			lista_e = insereObjeto(lista_e, r);

    		else 
			cont--;
	}

	return lista_e;
}

lista_botes geraBotes(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b, int l_max, int c_max, int vidas_max)
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


void boteBorda(fila naufragos, item *bote, int l_max, int c_max)
{

	int novaBorda;

	bote->vel.x = (rand()%(int)((velocidade_maxima + 1 - velocidade_minima))) + velocidade_minima;
	bote->vel.y = (rand()%(int)((velocidade_maxima + 1 - velocidade_minima))) + velocidade_minima;

	while(1)
	{
		novaBorda = rand()%4;
		if(novaBorda == 0) /* Canto superior esquerdo */
		{
			bote->pos.x = bote->raio;
			bote->pos.y = bote->raio;
		}
		else if(novaBorda == 1)  /* Canto superior direito */
		{
			bote->pos.x = c_max - bote->raio;
			bote->pos.y = bote->raio;
		}
		else if(novaBorda == 2) /* Canto inferior direito */
		{
			bote->pos.x = c_max - bote->raio;
			bote->pos.y = l_max - bote->raio;
		}
		else if(novaBorda == 3) /* Canto inferior esquerdo */
		{
			bote->pos.x = bote->raio;
			bote->pos.y = l_max - bote->raio;
		}

		if(validaPos(naufragos, bote))
			break;
	}
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

