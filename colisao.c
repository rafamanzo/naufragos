#include <allegro.h>
#include "configurador/configs.h"
#include "bib/tipos.h"
#include "bib/colisao.h"
#include "bib/desloc.h"
#include "bib/mar.h"
#include "entidades/pessoas.h"
#include "entidades/estaticos.h"
#include "entidades/botes.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define CAP_BOTE 10

void detectaColisao(lista_pessoas *lista_p, lista_estaticos *lista_e, lista_botes *lista_b, double deltaT)
{
  	lista_pessoas atual_p, ant_p, aux_p;
  	lista_botes atual_b, ant_b, aux_b;
  	lista_estaticos aux_e;

  /*colisoes de pessoas com outras entidades*/

  	ant_p = *lista_p;


  	while(ant_p != NULL)
	{    
    		/*colisoes com outras pessoas*/  
    		atual_p = aux_p = ant_p->prox;
  
    		while(aux_p != NULL)
		{
      			if(distancia(ant_p->pss.atr.pos, aux_p->pss.atr.pos) < (ant_p->pss.atr.raio + aux_p->pss.atr.raio))
			{
        			colidePessoas(&ant_p->pss, &aux_p->pss, deltaT);
        			ant_p->pss.atr.atualizada = aux_p->pss.atr.atualizada = 1;
      			}

      			aux_p = aux_p->prox;
    		}

    		/*colisoes com estaticos*/
    		aux_e = *lista_e;

    		while(aux_e != NULL)
		{
      			if(distancia(ant_p->pss.atr.pos, aux_e->stc.pos) < (ant_p->pss.atr.raio + aux_e->stc.raio))
			{
        			colidePessoaEstatico(aux_e->stc, &ant_p->pss, deltaT);
        			ant_p->pss.atr.atualizada = 1;
      			}

      			aux_e = aux_e->prox;
    		}

    		/*colisoes com botes*/
    		aux_b = *lista_b;

    		while(aux_b != NULL)
		{
      			if(distancia(ant_p->pss.atr.pos, aux_b->bt.atr.pos) < (ant_p->pss.atr.raio + aux_b->bt.atr.raio))
			{
        			if(aux_b->bt.carga < CAP_BOTE)
				{
          				*lista_p = removePessoa(*lista_p, ant_p);
          				aux_b->bt.carga++;
					aux_b->bt.pontos += 10;
					if(aux_b->bt.pontos%500 == 0)
						aux_b->bt.vidas++;
          				ant_p = *lista_p; /* como retirei uma pessoa da lista, recomeco a checagem com a nova lista de pessoas*/
          				break;
        			}
				else
				{
          				colidePessoaBote(&ant_p->pss, deltaT);
          				ant_p->pss.atr.atualizada = 1;
        			}
      			}
      			aux_b = aux_b->prox;
    		}
  
        	if(ant_p->pss.atr.pos.y < ant_p->pss.atr.raio)
          		colidePessoaComBorda(*lista_p, *lista_e, *lista_b, 0, &ant_p->pss);
        	else if(ant_p->pss.atr.pos.y > (tela.altura - ant_p->pss.atr.raio))
          		colidePessoaComBorda(*lista_p, *lista_e, *lista_b, 1, &ant_p->pss);
        	else if(ant_p->pss.atr.pos.x < ant_p->pss.atr.raio)
          		colidePessoaComBorda(*lista_p, *lista_e, *lista_b, 2, &ant_p->pss);
        	else if(ant_p->pss.atr.pos.x > (tela.comprimento - ant_p->pss.atr.raio))
          		colidePessoaComBorda(*lista_p, *lista_e, *lista_b, 3, &ant_p->pss); 
         
    		ant_p = atual_p;
  	}

  	/*colisoes de um bote com outra entidade que nao seja pessoa*/

  	ant_b = *lista_b;

  	while(ant_b != NULL)
	{
    		atual_b = aux_b = ant_b->prox;

    		/*colisao bote com bote*/
    		while(aux_b != NULL)
		{
      			if(distancia(ant_b->bt.atr.pos, aux_b->bt.atr.pos) < (ant_b->bt.atr.raio + aux_b->bt.atr.raio))
			{
        			colideBotes(&ant_b->bt, &aux_b->bt, deltaT);
      			}
      			aux_b = aux_b->prox;
    		}

    		/*colisao bote com estaticos*/
    		aux_e = *lista_e;

    		while(aux_e != NULL)
		{
      			if(distancia(ant_b->bt.atr.pos, aux_e->stc.pos) < (ant_b->bt.atr.raio + aux_e->stc.raio))
			{
        			/*colisao com recife*/
        			if(aux_e->stc.tipo == 'r')
				{
          				boteBorda(*lista_p, *lista_e, *lista_b, &ant_b->bt);
            				*lista_p = geraPessoas(*lista_p, *lista_e, *lista_b, ant_b->bt.carga);
            				ant_b->bt.carga = 0;
					ant_b->bt.vidas--;

					if(ant_b->bt.vidas == 0)
						*lista_b = removeBote(*lista_b, ant_b);
          				
        			}
				else
				{
          				colideBoteEstatico(aux_e->stc, &ant_b->bt, deltaT);
        			}
      			}
			

			else if( distancia( ant_b->bt.atr.pos, aux_e->stc.pos ) < (ant_b->bt.atr.raio + aux_e->stc.raio + 35) ) 
			{
				/*aqui tem que vir a descarga de pessoas se o bote estiver ancorado*/
				if(ant_b->bt.ancora == '1')
					descarregaPessoas(&ant_b->bt);		

			}
      			aux_e = aux_e->prox;

    		} 
        if(ant_b->bt.atr.pos.y < ant_b->bt.atr.raio)
          colideBoteComBorda(&ant_b->bt, 0);
        else if(ant_b->bt.atr.pos.y > (tela.altura - ant_b->bt.atr.raio))
          colideBoteComBorda(&ant_b->bt, 1);
        else if(ant_b->bt.atr.pos.x < ant_b->bt.atr.raio)
          colideBoteComBorda(&ant_b->bt, 2);
        else if(ant_b->bt.atr.pos.x > (tela.comprimento - ant_b->bt.atr.raio))
          colideBoteComBorda(&ant_b->bt, 3);

    		ant_b = atual_b;
  	}  
}

double diferencaAngulos(estatico imovel, vetor movel_pos, vetor movel_vel, int dir)
{
	if( dir == NO || dir == SO )
		 return (angulo(imovel.pos.x - movel_pos.x, (movel_pos.y - imovel.pos.y))-angulo(movel_vel.x, movel_vel.y));
	else if ( dir == NE || dir == SE )
		 return (angulo(movel_vel.x, movel_vel.y) - angulo(imovel.pos.x - movel_pos.x, (movel_pos.y - imovel.pos.y)));
	return 0;
}

void colidePessoaComBorda(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b, int borda, pessoa *p)
{

	int novaBorda;

 	/* 
		0  -- borda superior
	    	1  -- borda inferior
	    	2  -- borda esquerda
	    	3  -- borda direita. 
	*/

	/* Pessoa sai pela borda */

		/* Sorteia uma borda ate que ela seja diferente da atual */
		

	do
	{
		while( (novaBorda = rand()%4 ) == borda);

		if( novaBorda == 0 )
		{
			p->atr.pos.x = p->atr.raio + 20;
			p->atr.pos.y = rand()%tela.altura;
		}
		else if( novaBorda == 1 )
		{
			p->atr.pos.x = tela.comprimento - p->atr.raio - 20;
			p->atr.pos.y = rand()%tela.altura;
		}
		else if( novaBorda == 2 )
		{
			p->atr.pos.x = rand()%tela.comprimento;
			p->atr.pos.y = p->atr.raio + 20;
		}
		else if( novaBorda == 3 )
		{
			p->atr.pos.x = rand()%tela.comprimento;
			p->atr.pos.y = tela.altura - p->atr.raio - 20;
		}
				
	}while(validaPos(lista_p, lista_e, lista_b, p, NULL, NULL));

}


void colideBoteComBorda(bote * b, int borda)
{
	switch(borda)
	{
		case 0:
			b->atr.vel.y *= -1;
			b->atr.pos.y += 5;
			break;
		case 1:
			b->atr.vel.y *= -1;
			b->atr.pos.y -= 5;
			break;
		case 2:
			b->atr.vel.x *= -1;
			b->atr.pos.x += 5;
			break;
		case 3:
			b->atr.vel.x *= -1;
			b->atr.pos.x -= 5;
			break;	
	}			
}
