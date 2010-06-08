#include "bib/tipos.h"
#include "bib/colisao.h"
#include "bib/desloc.h"
#include "bib/mar.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

fila detectaColisao(fila pessoas, double deltaT)
{
	fila principal, aux;
	double max_dist;

	if(quantidade(pessoas) > 1)
	{  
		principal = aux = pessoas;

		while(principal != NULL)
		{
			while(aux != NULL)
			{
			  if(aux != principal)
				{
					max_dist = principal->p.raio + aux->p.raio;

					if(max_dist >= distancia(principal->p.pos, aux->p.pos))
          {
                if((principal->p.categoria == '1' || principal->p.categoria == '2') && (aux->p.categoria == 'r')){
	
		/* Encalha com 66% de chance */
		if( rand()%3 < 2 )
			boteBorda(&principal->p, 768, 1024);/* Setamos 1024x768, caso o tamanho mude é necessário mudar aqui tambem */
		/* Colide elasticamente */
		else
                  colideCoral(aux->p, &principal->p, deltaT);
                }
		else if((principal->p.categoria == '1' || principal->p.categoria == '2') && (aux->p.categoria == 'a')){
                  colideEsfera(aux->p, &principal->p, deltaT);
                }else if(principal->p.categoria == '1' && aux->p.categoria == '2'){
                  colide(&principal->p, &aux->p, deltaT);
                  principal->p.atualizada = aux->p.atualizada = 0;
                }else if((principal->p.categoria == '1' || principal->p.categoria == '2') && aux->p.categoria == 'p'){
                  pessoas = aux = principal = recolhePessoa(pessoas, aux);
                }else if((principal->p.categoria == 'r' || principal->p.categoria == 'a') && aux->p.categoria == 'p'){
                  colideEsfera(principal->p, &aux->p, deltaT);
                }else if(principal->p.categoria == 'p' && aux->p.categoria == 'p'){
					        colide(&principal->p, &aux->p, deltaT);
                }
          }
        }

		    if(aux != NULL) aux = aux->prox;
      }
      		
			aux = pessoas;
      if(principal != NULL) principal = principal->prox;
    }
	}
  return pessoas;
}

fila recolhePessoa(fila pessoas, fila p)
{
  fila aux, ant;
  
  ant = NULL;
  aux = pessoas;

  while(aux != NULL)
  {
    if(aux == p)
    {
      if(ant == NULL)
      {
        ant = aux->prox;
        free(aux);
        return(ant);
      }
      else
      {
        ant->prox = aux->prox;
        free(aux);
        return(pessoas);
      }      
    }
    ant = aux;
    aux = aux->prox;
  }
  return(NULL);
}

void movePessoa(item *p, double deltaT)
{
	int dir;
	double vel;

	vel = modulo(p->vel);
  	dir = direcao(p->vel.x, p->vel.y);

  	switch(dir)
	{
    	case L:
      		p->pos.x += (int) vel*deltaT;
      		break;
    	case NE:
      		p->pos.x += (int) vel*cos(M_PI/4)*deltaT;
      		p->pos.y += (int) vel*sin(M_PI/4)*deltaT;
      		break;
    	case N:
      		p->pos.y += (int) vel*deltaT;
      		break;
    	case NO:
      		p->pos.x += (int) vel*cos(M_PI/4)*(-1)*deltaT;
      		p->pos.y += (int) vel*sin(M_PI/4)*deltaT;
      		break;
    	case O:
      		p->pos.x += (int) vel*(-1)*deltaT;
      		break;
    	case SO:
      		p->pos.x += (int) vel*cos(M_PI/4)*(-1)*deltaT;
      		p->pos.y += (int) vel*sin(M_PI/4)*(-1)*deltaT;
     		break;
    	case S:
      		p->pos.y += (int) vel*(-1)*deltaT;
      		break;
    	case SE:
      		p->pos.x += (int) vel*cos(M_PI/4)*deltaT;
      		p->pos.y += (int) vel*sin(M_PI/4)*(-1)*deltaT;
      		break;
  	}
}

void colideEsfera(item estatico, item *movel, double deltaT){
  movel->vel.x *= -1;
  movel->vel.y *= -1;

  movePessoa(movel, deltaT);
  movel->atualizada = 1;
}

void colideEstatico(item estatico, item *movel, double deltaT){
  int dir;
  item aux;

  aux.raio = movel->raio;
  aux.pos.x = movel->pos.x;
  aux.pos.y = movel->pos.y;
  aux.vel.x = movel->vel.x;
  aux.vel.y = movel->vel.y;

  dir = direcao(aux.vel.x, aux.vel.y);

  switch(dir){
    /*casos bons!*/
    case N:
      movel->vel.y *= -1;
      movel->pos.y -= movel->raio;
      if(movel->pos.x - estatico.pos.x > 0)
        movel->pos.x += movel->raio;
      else
        movel->pos.x -= movel->raio; 
      break;
    case S:
      movel->vel.y *= -1;
      movel->pos.y += movel->raio;
      if(movel->pos.x - estatico.pos.x > 0)
        movel->pos.x += movel->raio;
      else
        movel->pos.x -= movel->raio;
      break;
    case L:
      movel->vel.x *= -1;
      movel->pos.x -= movel->raio;
      if(movel->pos.y - estatico.pos.y > 0)
        movel->pos.y += movel->raio;
      else
        movel->pos.y -= movel->raio;
      break;
    case O:
      movel->vel.x *= -1;
      movel->pos.x += movel->raio;
      if(movel->pos.y - estatico.pos.y > 0)
        movel->pos.y += movel->raio;
      else
        movel->pos.y -= movel->raio;
      break;
    /*casos ruins!*/
    default:
      /*printf("\nDefault");*/
      aux.vel.y *= -1;
      movePessoa(&aux, deltaT);
      if(distancia(aux.pos, estatico.pos) < (aux.raio + estatico.raio)){
        aux.raio = movel->raio;
        aux.pos.x = movel->pos.x;
        aux.pos.y = movel->pos.y;
        aux.vel.x = movel->vel.x;
        aux.vel.y = movel->vel.y;
        
        if(aux.vel.x > 0){
          aux.pos.x += aux.raio;
        }else{
          aux.pos.x -= aux.raio;
        }
        if(aux.pos.x > 0){
          aux.pos.y += aux.raio;
        }else{
          aux.pos.y -= aux.raio;
        }
        aux.vel.x *= -1;
        /*while(distancia(aux.pos, estatico.pos) < (aux.raio + estatico.raio)) movePessoa(&aux, deltaT);*/ 
      }
      break;
  }

  while(distancia(aux.pos, estatico.pos) < (aux.raio + estatico.raio)) movePessoa(&aux, deltaT);

  movel->raio = aux.raio;
  movel->pos.x = aux.pos.x;
  movel->pos.y = aux.pos.y;
  movel->vel.x = aux.vel.x;
  movel->vel.y = aux.vel.y;

  movel->atualizada=1;
}

void colideCoral(item coral, item *p, double deltaT){
  int dir;
  double dif;

  dif = (angulo(p->vel.x, p->vel.y) - angulo(coral.pos.x - p->pos.x, coral.pos.y - p->pos.y));
  
  dir = direcao(p->vel.x, p->vel.y);

  switch(dir){
    /*casos bons!*/
    case N:
      p->vel.y *= -1;
      p->pos.y -= p->raio;
      if(p->pos.x - coral.pos.x > 0)
        p->pos.x += p->raio;
      else
        p->pos.x -= p->raio; 
      break;
    case S:
      p->vel.y *= -1;
      p->pos.y += p->raio;
      if(p->pos.x - coral.pos.x > 0)
        p->pos.x += p->raio;
      else
        p->pos.x -= p->raio;
      break;
    case L:
      p->vel.x *= -1;
      p->pos.x -= p->raio;
      if(p->pos.y - coral.pos.y > 0)
        p->pos.y += p->raio;
      else
        p->pos.y -= p->raio;
      break;
    case O:
      p->vel.x *= -1;
      p->pos.x += p->raio;
      if(p->pos.y - coral.pos.y > 0)
        p->pos.y += p->raio;
      else
        p->pos.y -= p->raio;
      break;
    /*casos ruins!*/
    case NE:
      if(dif == 0){
        p->vel.y *= -1;
        p->vel.x *= -1;
        p->pos.x -= p->raio;
        p->pos.y -= p->raio;
      }else if(dif < 0){
        p->vel.y *= -1;
        p->pos.x += p->raio;
        p->pos.y -= p->raio;
      }else if(dif > 0){
        p->vel.x *= -1;
        p->pos.x -= p->raio;
        p->pos.y += p->raio;
      }
      break;
    case NO:
       if(dif == 0){
        p->vel.y *= -1;
        p->vel.x *= -1;
        p->pos.x += p->raio;
        p->pos.y -= p->raio;
      }else if(dif < 0){
        p->vel.y *= -1;
        p->pos.x -= p->raio;
        p->pos.y -= p->raio;
      }else if(dif > 0){
        p->vel.x *= -1;
        p->pos.x += p->raio;
        p->pos.y += p->raio;
      }
      break;
    case SE:
      if(dif == 0){
        p->vel.y *= -1;
        p->vel.x *= -1;
        p->pos.x -= p->raio;
        p->pos.y += p->raio;
      }else if(dif < 0){
        p->vel.x *= -1;
        p->pos.x -= p->raio;
        p->pos.y -= p->raio;
      }else if(dif > 0){
        p->vel.y *= -1;
        p->pos.x += p->raio;
        p->pos.y += p->raio;
      }
      break;
    case SO:
      if(dif == 0){
        p->vel.y *= -1;
        p->vel.x *= -1;
        p->pos.x += p->raio;
        p->pos.y += p->raio;
      }else if(dif < 0){
        p->vel.x *= -1;
        p->pos.x += p->raio;
        p->pos.y -= p->raio;
      }else if(dif > 0){
        p->vel.y *= -1;
        p->pos.x -= p->raio;
        p->pos.y += p->raio;
      }
      break;
  }
  while(distancia(p->pos, coral.pos) < (p->raio + coral.raio)) movePessoa(p, deltaT);
  p->atualizada = 1;
}

void colide(item *p1, item *p2, double deltaT)
{
/*Colisao perfeitamente elastica entre objetos de mesma massa, suas direcoes e velocidades se invertem.*/
    
	vetor aux_vel;

	aux_vel = p1->vel; 
	p1->vel = p2->vel;
	p2->vel = aux_vel;

	movePessoa(p1,deltaT);
	movePessoa(p2,deltaT);

	if(distancia(p1->pos, p2->pos) > 5){
	  p1->atualizada = 1;
	  p2->atualizada = 1;
  }
  
}

void colideComBorda( fila naufragos, item *p, int borda, int l_max, int c_max)
{
 int novaBorda;
 item aux;
 /* 0  -- borda superior
    1  -- borda inferior
    2  -- borda esquerda
    3  -- borda direita. */

	/* Pessoa sai pela borda */
	if( p->categoria == 'p')
	{
		/* Sorteia uma borda ate que ela seja diferente da atual */
		

		while( 1 )
		{
			while( (novaBorda = rand()%4 ) == borda);

			if( novaBorda == 0 )
			{
				p->pos.x = p->raio + 20;
				p->pos.y = rand()%l_max;
			}
			else if( novaBorda == 1 )
			{
				p->pos.x = c_max - p->raio - 20;
				p->pos.y = rand()%l_max;
			}
			else if( novaBorda == 2 )
			{
				p->pos.x = rand()%c_max;
				p->pos.y = p->raio + 20;
			}
			else if( novaBorda == 3 )
			{
				p->pos.x = rand()%c_max;
				p->pos.y = l_max - p->raio - 20;
			}
			
			if(validaPos(naufragos, p)){
				break;}
			
		}
	}

	/* Bote colide com a borda */
	else if( p->categoria == '1' || p->categoria == '2' )
	{
		switch(borda)
		{
			case 0:
				p->vel.y *= -1;
				p->pos.y += p->raio;
				break;
			case 1:
				p->vel.y *= -1;
				p->pos.y -= p->raio;
				break;
			case 2:
				p->vel.x *= -1;
				p->pos.x += p->raio;
				break;
			case 3:
				p->vel.x *= -1;
				p->pos.x -= p->raio;
				break;
		}			
	}
}
