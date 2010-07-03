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


double diferencaAngulos(estatico imovel, vetor movel_pos, vetor movel_vel, int dir)
{
	if( dir == NO || dir == SO )
		 return (angulo(imovel.pos.x - movel_pos.x, (movel_pos.y - imovel.pos.y))-angulo(movel_vel.x, movel_vel.y));
	else if ( dir == NE || dir == SE )
		 return (angulo(movel_vel.x, movel_vel.y) - angulo(imovel.pos.x - movel_pos.x, (movel_pos.y - imovel.pos.y)));
	return 0;
}


void colidePessoaEstatico(estatico imovel, pessoa *p, double deltaT)
{
	int dir = -1;
	double dif = 0;

	dir = direcao((int)p->atr.vel.x, (int)p->atr.vel.y);

	switch(dir)
	{
	    /*casos bons!!!*/
	    case N:
	    	p->atr.vel.y *= -1;
	    	p->atr.pos.y += p->atr.raio;
	    	if( (p->atr.pos.x - imovel.pos.x) > 0)
			p->atr.pos.x += p->atr.raio;
	    	else
			p->atr.pos.x -= p->atr.raio; 
	    	break;
	    case S:
	      	p->atr.vel.y *= -1;
	      	p->atr.pos.y -= p->atr.raio;
	      	if((p->atr.pos.x - imovel.pos.x) > 0)
			p->atr.pos.x += p->atr.raio;
	      	else
			p->atr.pos.x -= p->atr.raio;
	      	break;
	    case L:
	      	p->atr.vel.x *= -1;
	      	p->atr.pos.x -= p->atr.raio;
	      	if((p->atr.pos.y - imovel.pos.y) > 0)
			p->atr.pos.y -= p->atr.raio;
	      	else
			p->atr.pos.y += p->atr.raio;
	      	break;
	    case O:
	      	p->atr.vel.x *= -1;
	      	p->atr.pos.x += p->atr.raio;
	      	if((p->atr.pos.y - imovel.pos.y) > 0)
			p->atr.pos.y += p->atr.raio;
	      	else
			p->atr.pos.y += p->atr.raio;
	      	break;
	   	/*casos ruins*/
	    case NE:
		dif  = diferencaAngulos(imovel, p->atr.pos, p->atr.vel, NE);
	      	if(dif == 0)
		{
			p->atr.vel.y *= -1;
			p->atr.vel.x *= -1;
			p->atr.pos.x -= p->atr.raio;
			p->atr.pos.y += p->atr.raio;
	      	}
		/* Caso a diferenca de angulos(dif) for menor que -180 graus, significa que o y do que esta se movendo eh menor do que y do que esta parado, assim a colisao ocorre de forma diferente para que o movel nao passe o imovel sem colidir*/
		else if(dif < 0 && dif > -180)
		{
			p->atr.vel.y *= -1;
			p->atr.pos.x += p->atr.raio;
			p->atr.pos.y += p->atr.raio;
	      	}
		else if(dif > 0 || dif <= -180)
		{
			p->atr.vel.x *= -1;
			p->atr.pos.x -= p->atr.raio;
			p->atr.pos.y -= p->atr.raio;
	      	}
	      	break;
	    case NO:
		dif  = diferencaAngulos(imovel, p->atr.pos, p->atr.vel, NO);
	       	if(dif == 0)
		{
			p->atr.vel.y *= -1;
			p->atr.vel.x *= -1;
			p->atr.pos.x += p->atr.raio;
			p->atr.pos.y -= p->atr.raio;
	      	}
		else if(dif < 0)
		{
			p->atr.vel.y *= -1;
			p->atr.pos.x -= p->atr.raio;
			p->atr.pos.y -= p->atr.raio;
	      	}
		else if(dif > 0)
		{
			p->atr.vel.x *= -1;
			p->atr.pos.x += p->atr.raio;
			p->atr.pos.y += p->atr.raio;
	      	}
	      	break;
	    case SE:
		dif  = diferencaAngulos(imovel, p->atr.pos, p->atr.vel, SE);
	      	if(dif == 0)
		{
			p->atr.vel.y *= -1;
			p->atr.vel.x *= -1;
			p->atr.pos.x -= p->atr.raio;
			p->atr.pos.y += p->atr.raio;
	      	}
		else if(dif > 0 || dif <= 180)
		{
			p->atr.vel.x *= -1;
			p->atr.pos.x -= p->atr.raio;
			p->atr.pos.y -= p->atr.raio;
	      	}
		else if(dif < 0 && dif > 180)
		{
			p->atr.vel.y *= -1;
			p->atr.pos.x += p->atr.raio;
			p->atr.pos.y += p->atr.raio;
	      	}	
	      	break;
	    case SO:
		dif  = diferencaAngulos(imovel, p->atr.pos, p->atr.vel, SO);
	      	if(dif == 0)
		{
			p->atr.vel.y *= -1;
			p->atr.vel.x *= -1;
			p->atr.pos.x += p->atr.raio;
			p->atr.pos.y += p->atr.raio;
	      	}
		else if(dif < 0)
		{
			p->atr.vel.x *= -1;
			p->atr.pos.x += p->atr.raio;
			p->atr.pos.y -= p->atr.raio;
	      	}
		else if(dif > 0)
		{
			p->atr.vel.y *= -1;
			p->atr.pos.x -= p->atr.raio;
			p->atr.pos.y += p->atr.raio;
	      	}
	      	break;
	  }

	  while(distancia(p->atr.pos, imovel.pos) < (p->atr.raio + imovel.raio)) 
		movePessoa(p, deltaT);

	  p->atr.atualizada = 1;
}


void colideBoteEstatico(estatico imovel, bote *b, double deltaT)
{
	int dir = -1;
	double dif = 0;

	dir = direcao((int)b->atr.vel.x, (int)b->atr.vel.y);

	switch(dir)
	{
	    /*casos bons!!!*/
	    case N:
	    	b->atr.vel.y *= -1;
	    	b->atr.pos.y += b->atr.raio;
	    	if( (b->atr.pos.x - imovel.pos.x) > 0)
			b->atr.pos.x += b->atr.raio;
	    	else
			b->atr.pos.x -= b->atr.raio; 
	    	break;
	    case S:
	      	b->atr.vel.y *= -1;
	      	b->atr.pos.y -= b->atr.raio;
	      	if((b->atr.pos.x - imovel.pos.x) > 0)
			b->atr.pos.x += b->atr.raio;
	      	else
			b->atr.pos.x -= b->atr.raio;
	      	break;
	    case L:
	      	b->atr.vel.x *= -1;
	      	b->atr.pos.x -= b->atr.raio;
	      	if((b->atr.pos.y - imovel.pos.y) > 0)
			b->atr.pos.y -= b->atr.raio;
	      	else
			b->atr.pos.y += b->atr.raio;
	      	break;
	    case O:
	      	b->atr.vel.x *= -1;
	      	b->atr.pos.x += b->atr.raio;
	      	if((b->atr.pos.y - imovel.pos.y) > 0)
			b->atr.pos.y += b->atr.raio;
	      	else
			b->atr.pos.y += b->atr.raio;
	      	break;
	   	/*casos ruins*/
	    case NE:
		dif  = diferencaAngulos(imovel, b->atr->pos, b->atr->vel, NE);
	      	if(dif == 0)
		{
			b->atr.vel.y *= -1;
			b->atr.vel.x *= -1;
			b->atr.pos.x -= b->atr.raio;
			b->atr.pos.y += b->atr.raio;
	      	}
		/* Caso a diferenca de angulos(dif) for menor que -180 graus, significa que o y do que esta se movendo eh menor do que y do que esta parado, assim a colisao ocorre de forma diferente para que o movel nao passe o imovel sem colidir*/
		else if(dif < 0 && dif > -180)
		{
			b->atr.vel.y *= -1;
			b->atr.pos.x += b->atr.raio;
			b->atr.pos.y += b->atr.raio;
	      	}
		else if(dif > 0 || dif <= -180)
		{
			b->atr.vel.x *= -1;
			b->atr.pos.x -= b->atr.raio;
			b->atr.pos.y -= b->atr.raio;
	      	}
	      	break;
	    case NO:
		dif  = diferencaAngulos(imovel, b->atr->pos, b->atr->vel, NO);
	       	if(dif == 0)
		{
			b->atr.vel.y *= -1;
			b->atr.vel.x *= -1;
			b->atr.pos.x += b->atr.raio;
			b->atr.pos.y -= b->atr.raio;
	      	}
		else if(dif < 0)
		{
			b->atr.vel.y *= -1;
			b->atr.pos.x -= b->atr.raio;
			b->atr.pos.y -= b->atr.raio;
	      	}
		else if(dif > 0)
		{
			b->atr.vel.x *= -1;
			b->atr.pos.x += b->atr.raio;
			b->atr.pos.y += b->atr.raio;
	      	}
	      	break;
	    case SE:
		dif  = diferencaAngulos(imovel, b->atr->pos, b->atr->vel, SE);
	      	if(dif == 0)
		{
			b->atr.vel.y *= -1;
			b->atr.vel.x *= -1;
			b->atr.pos.x -= b->atr.raio;
			b->atr.pos.y += b->atr.raio;
	      	}
		else if(dif > 0 || dif <= 180)
		{
			b->atr.vel.x *= -1;
			b->atr.pos.x -= b->atr.raio;
			b->atr.pos.y -= b->atr.raio;
	      	}
		else if(dif < 0 && dif > 180)
		{
			b->atr.vel.y *= -1;
			b->atr.pos.x += b->atr.raio;
			b->atr.pos.y += b->atr.raio;
	      	}	
	      	break;
	    case SO:
		dif  = diferencaAngulos(imovel, b->atr->pos, b->atr->vel, SO);
	      	if(dif == 0)
		{
			b->atr.vel.y *= -1;
			b->atr.vel.x *= -1;
			b->atr.pos.x += b->atr.raio;
			b->atr.pos.y += b->atr.raio;
	      	}
		else if(dif < 0)
		{
			b->atr.vel.x *= -1;
			b->atr.pos.x += b->atr.raio;
			b->atr.pos.y -= b->atr.raio;
	      	}
		else if(dif > 0)
		{
			b->atr.vel.y *= -1;
			b->atr.pos.x -= b->atr.raio;
			b->atr.pos.y += b->atr.raio;
	      	}
	      	break;
	  }
/*
	  while(distancia(b->atr.pos, imovel.pos) < (b->atr.raio + imovel.raio)) 
		movePessoa(b, deltaT);
*/
	  b->atr.atualizada = 1;
}



void colide(pessoa *p1, pessoa *p2, double deltaT)
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
