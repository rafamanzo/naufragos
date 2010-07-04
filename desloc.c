#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "bib/tipos.h"
#include "bib/desloc.h"


double distancia(vetor pos1, vetor pos2)
{
	/*Devolve a distancia entre dois pontos*/
	return sqrt((pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y));

}

double angulo(double x, double y)
{
	/*Baseando-se nas componentes da velocidade, acha o angulo formado pelo vetor velocidade.*/	

	double ang;

	ang = atan2(y,x);
	if(ang < 0) 
		ang+=2*M_PI;
	ang*=180/M_PI;

	return ang;
}

int direcao(int x, int y)
{
	/*Baseando-se nas componentes da velocidade, define a direção.*/

	double ang;

	ang = angulo(x, y);

	while(ang > 360.0)
	{
		ang-=360.0;
	}

	if(ang >= 337.5 || ang < 22.5)
		return L;

	else if(ang >= 22.5 && ang < 67.5 )
		return NE;

	else if(ang >= 67.5 && ang < 112.5)
		return N;

	else if(ang >= 112.5 && ang < 157.5)
		return NO;

	else if(ang >= 157.5 && ang < 202.5)
    		return O;

	else if(ang >= 202.5 && ang < 247.5)
		return SO;

	else if(ang >= 247.5 && ang < 292.5)
    		return S;

	else if(ang >= 292.5 && ang < 337.5)
		return SE;
	

  	return -1;
}

double modulo(vetor v)
{
	return sqrt((v.x*v.x) + (v.y*v.y));
}

/* gera uma "matriz de cadeia de markov" (adapatada para trabalhar bem com a funcao rand)
   atualiza a pessoa de acordo com a cadeia, MAS NÃO O MAR */

void markov(pessoa *p, double deltaT)
{
	/*A funcao markov ira determinar uma probabilidade de 65% de chance de continuar na mesma direção e 5% para cada outra direção.*/

	int mkv[8];
	double vel;
	int i, sort, dir;

	dir = direcao(p->atr.vel.x, p->atr.vel.y);
	vel = modulo(p->atr.vel);

	for(i = 0; i < 8; i++)
		if(i == dir) 
			mkv[i] = 65;

        else if(i > dir) 
		  mkv[i] = 65 + (i)*5;

        else if(i < dir) 
		  mkv[i] = 65 + (i + 1)*5;

  	sort = rand() % 100;

  	if(sort >= 65)
		for(i = 0; i < 8; i++)
		{
		  	if(i != dir)
			{
				if(sort < mkv[i])
				{
					dir = i; i = 8; 
				}
			}
		}

  	switch(dir)
	{
    	case L:
      		p->atr.vel.x = (int) vel;
      		p->atr.vel.y = 0;
      		p->atr.pos.x += (int) vel*deltaT;
      		break;
    	case NE:
      		p->atr.vel.x = vel*cos(M_PI/4);
      		p->atr.vel.y = vel*sin(M_PI/4);
      		p->atr.pos.x += (int) vel*cos(M_PI/4)*deltaT;
      		p->atr.pos.y -= (int) vel*sin(M_PI/4)*deltaT;
      		break;
    	case N:
      		p->atr.vel.x = 0;
      		p->atr.vel.y = vel;
      		p->atr.pos.y -= (int) vel*deltaT;
      		break;
    	case NO:
      		p->atr.vel.x = vel*cos(M_PI/4)*(-1);
      		p->atr.vel.y = vel*sin(M_PI/4);
      		p->atr.pos.x += (int) vel*cos(M_PI/4)*(-1)*deltaT;
      		p->atr.pos.y -= (int) vel*sin(M_PI/4)*deltaT;
      		break;
    	case O:
      		p->atr.vel.x = vel*(-1);
      		p->atr.vel.y = 0;
      		p->atr.pos.x -= (int) vel*deltaT;
      		break;
    	case SO:
      		p->atr.vel.x = vel*cos(M_PI/4)*(-1);
      		p->atr.vel.y = vel*sin(M_PI/4)*(-1);
      		p->atr.pos.x += (int) vel*cos(M_PI/4)*(-1)*deltaT;
      		p->atr.pos.y -= (int) vel*sin(M_PI/4)*(-1)*deltaT;
     		break;
    	case S:
      		p->atr.vel.x = 0;
      		p->atr.vel.y = vel*(-1);
      		p->atr.pos.y -= (int) vel*(-1)*deltaT;
      		break;
    	case SE:
      		p->atr.vel.x = vel*cos(M_PI/4);
      		p->atr.vel.y = vel*sin(M_PI/4)*(-1);
      		p->atr.pos.x += (int) vel*cos(M_PI/4)*deltaT;
      		p->atr.pos.y -= (int) vel*sin(M_PI/4)*(-1)*deltaT;
      		break;
  	}

}
