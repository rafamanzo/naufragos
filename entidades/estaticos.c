#include <stdlib.h>
#include <math.h>
#include <allegro.h>
#include "../bib/tipos.h"
#include "../bib/colisao.h"
#include "../bib/desloc.h"
#include "../bib/mar.h"
#include "pessoas.h"
#include "botes.h"
#include "../configurador/configs.h"
#include "estaticos.h"

lista_estaticos geraAsimov(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b)
{
	estatico asimov;

	asimov.desenho = load_bitmap("../imagens/asimov.bmp",desktop_palette);
	asimov.pos.x = rand()%/*tela.comprimento*/1025; /* MUDAR AQUI!!!!!!! #### ## ## #*/
	asimov.pos.y = rand()%/*tela.altura*/768;
	asimov.raio = R_ASIMOV;
	asimov.tipo = 'a';

  while( !validaPos(lista_p, lista_e, lista_b, NULL, &asimov, NULL) )
	{
	  asimov.pos.x = rand()%tela.comprimento;
	  asimov.pos.y = rand()%tela.altura;
  }

	lista_e = insereObjeto(lista_e, asimov);

	return lista_e;

}

lista_estaticos geraRecifes(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b, int numRecifes)
{
	int cont, decideTam, raioMedio;
	estatico r;

	raioMedio = sqrt(2*D)/2;

	for(cont = 0; cont < numRecifes; cont++)
	{
		r.desenho = load_bitmap("../imagens/recife.bmp",desktop_palette);
		r.pos.x = rand()%tela.comprimento;
		r.pos.y = rand()%tela.altura;
		r.tipo = 'r';

		decideTam = rand()%3; 

		if( decideTam == 0 ) 	 /* RECIFES MEDIOS */
			r.raio = raioMedio;

		else if( decideTam == 1) /* RECIFES PEQUENOS */
			while( (r.raio = rand()%raioMedio) < 5 ); /* Garante que o raio não sera 0 ou muito pequeno */

		else			 /* RECIFES GRANDES */
			r.raio = raioMedio + rand()%raioMedio;/* No maximo será do dobro do tamanho do medio */

						    
		if( validaPos(lista_p, lista_e, lista_b, NULL, &r, NULL) ) 
			lista_e = insereObjeto(lista_e, r);

    		else 
			cont--;
	}

	return lista_e;
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
		dif  = diferencaAngulos(imovel, b->atr.pos, b->atr.vel, NE);
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
		dif  = diferencaAngulos(imovel, b->atr.pos, b->atr.vel, NO);
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
		dif  = diferencaAngulos(imovel, b->atr.pos, b->atr.vel, SE);
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
		dif  = diferencaAngulos(imovel, b->atr.pos, b->atr.vel, SO);
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

	  while(distancia(b->atr.pos, imovel.pos) < (b->atr.raio + imovel.raio)) 
		moveBote(dir,0,b, deltaT);

	  b->atr.atualizada = 1;
}
