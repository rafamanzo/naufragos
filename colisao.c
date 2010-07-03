#include <allegro.h>
#include "bib/tipos.h"
#include "bib/colisao.h"
#include "bib/desloc.h"
#include "bib/mar.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

fila detectaColisao(fila naufragos, double deltaT)
{
	fila principal, aux;
	double max_dist;

	if(quantidade(naufragos) > 1)
	{  
		principal = aux = naufragos;

		while(principal != NULL)
		{
			while(aux != NULL)
			{
				if(aux != principal)
				{
					max_dist = principal->p.raio + aux->p.raio;

					if(max_dist >= distancia(principal->p.pos, aux->p.pos))
          				{
				                if((principal->p.categoria == '1' || principal->p.categoria == '2') && (aux->p.categoria == 'r'))
						{
								/* Encalha com 66% de chance */
							if( rand()%3 < 2 )
								boteBorda(naufragos,&principal->p, 768, 1024);/* Setamos 1024x768, caso o tamanho mude 	é necessário mudar aqui tambem */
							/* Colide elasticamente */
							else
						                colideEstatico(aux->p, &principal->p, deltaT);
	               				}
						else if((principal->p.categoria == '1' || principal->p.categoria == '2') && (aux->p.categoria == 'a'))
						{
					                colideEstatico(aux->p, &principal->p, deltaT);
	        	        		}
						else if(principal->p.categoria == '1' && aux->p.categoria == '2')
						{
					                colide(&principal->p, &aux->p, deltaT);
	        	          			principal->p.atr.atualizada = aux->p.atr.atualizada = 0;
	        	        		}
						else if((principal->p.categoria == '1' || principal->p.categoria == '2') && aux->p.categoria == 'p')
						{
					                naufragos = aux = principal = recolhePessoa(naufragos, aux);
	        	        		}
						else if((principal->p.categoria == 'r' || principal->p.categoria == 'a') && aux->p.categoria == 'p')
						{
					                colideEstatico(principal->p, &aux->p, deltaT);
	        	        		}
						else if(principal->p.categoria == 'p' && aux->p.categoria == 'p')
						{
						        colide(&principal->p, &aux->p, deltaT);
				                }
					}
		        	}

				if(aux != NULL) 
					aux = aux->prox;
			}
      		
			aux = naufragos;
			if(principal != NULL) 
				principal = principal->prox;
		}
	}

	return naufragos;
}

double diferencaAngulos(estatico imovel, vetor movel_pos, vetor movel_vel, int dir)
{
	if( dir == NO || dir == SO )
		 return (angulo(imovel.pos.x - movel_pos.x, (movel_pos.y - imovel.pos.y))-angulo(movel_vel.x, movel_vel.y));
	else if ( dir == NE || dir == SE )
		 return (angulo(movel_vel.x, movel_vel.y) - angulo(imovel.pos.x - movel_pos.x, (movel_pos.y - imovel.pos.y)));
	return 0;
}

void colidePessoaComBorda(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b, pessoa *p, int borda, int l_max, int c_max)
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
		

	while( 1 )
	{
		while( (novaBorda = rand()%4 ) == borda);

		if( novaBorda == 0 )
		{
			p->atr->pos.x = p->atr->raio + 20;
			p->atr->pos.y = rand()%l_max;
		}
		else if( novaBorda == 1 )
		{
			p->atr->pos.x = c_max - p->atr->raio - 20;
			p->atr->pos.y = rand()%l_max;
		}
		else if( novaBorda == 2 )
		{
			p->atr->pos.x = rand()%c_max;
			p->atr->pos.y = p->atr->raio + 20;
		}
		else if( novaBorda == 3 )
		{
			p->atr->pos.x = rand()%c_max;
			p->atr->pos.y = l_max - p->atr->raio - 20;
		}
		
		if( validaPos(lista_p, lista_e, lista_b, p, NULL, NULL) )
			break;
		
	}

}


void colideBoteComBorda(bote * b, int borda, int l_max, int c_max)
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
