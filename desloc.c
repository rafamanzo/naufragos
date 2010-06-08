#include "bib/tipos.h"
#include "bib/desloc.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

double distancia(vetor pos1, vetor pos2)
{

	return sqrt((pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y));

}

double angulo(double x, double y){
  double ang;

  ang = atan2(y,x);
	if(ang < 0) ang+=2*M_PI;
	ang*=180/M_PI;

  return ang;
}

int direcao(int x, int y)
{
	double ang;

	ang = atan2(y,x);

	if(ang < 0) ang+=2*M_PI;
  
	ang*=180/M_PI;

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

void markov(item *p, double deltaT)
{

	int mkv[8];
	double vel;
	int i, sort, dir;

	dir = direcao(p->vel.x, p->vel.y);
	vel = modulo(p->vel);

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
      		p->vel.x = (int) vel;
      		p->vel.y = 0;
      		p->pos.x += (int) vel*deltaT;
      		break;
    	case NE:
      		p->vel.x = vel*cos(M_PI/4);
      		p->vel.y = vel*sin(M_PI/4);
      		p->pos.x += (int) vel*cos(M_PI/4)*deltaT;
      		p->pos.y += (int) vel*sin(M_PI/4)*deltaT;
      		break;
    	case N:
      		p->vel.x = 0;
      		p->vel.y = vel;
      		p->pos.y += (int) vel*deltaT;
      		break;
    	case NO:
      		p->vel.x = vel*cos(M_PI/4)*(-1);
      		p->vel.y = vel*sin(M_PI/4);
      		p->pos.x += (int) vel*cos(M_PI/4)*(-1)*deltaT;
      		p->pos.y += (int) vel*sin(M_PI/4)*deltaT;
      		break;
    	case O:
      		p->vel.x = vel*(-1);
      		p->vel.y = 0;
      		p->pos.x += (int) vel*(-1)*deltaT;
      		break;
    	case SO:
      		p->vel.x = vel*cos(M_PI/4)*(-1);
      		p->vel.y = vel*sin(M_PI/4)*(-1);
      		p->pos.x += (int) vel*cos(M_PI/4)*(-1)*deltaT;
      		p->pos.y += (int) vel*sin(M_PI/4)*(-1)*deltaT;
     		break;
    	case S:
      		p->vel.x = 0;
      		p->vel.y = vel*(-1);
      		p->pos.y += (int) vel*(-1)*deltaT;
      		break;
    	case SE:
      		p->vel.x = vel*cos(M_PI/4);
      		p->vel.y = vel*sin(M_PI/4)*(-1);
      		p->pos.x += (int) vel*cos(M_PI/4)*deltaT;
      		p->pos.y += (int) vel*sin(M_PI/4)*(-1)*deltaT;
      		break;
  	}

}
