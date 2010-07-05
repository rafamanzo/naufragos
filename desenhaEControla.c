#include <allegro.h>
#include "bib/tipos.h"
#include "bib/desloc.h"
#include "bib/desenhaEControla.h"
#include "entidades/botes.h"

#define ACELERACAO 10
#define FREIO 20

void imprimeMar(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b, double deltaT)
{
	BITMAP *buffer, *fundo;

	buffer = create_bitmap(screen->w, screen->h);
 
	/* Imprime o fundo */
	fundo = load_bitmap("imagens/mar.bmp",desktop_palette);	 
	blit(fundo, buffer,0,0,0,0, 1024, 768);	/* alterar o tamanho da imagem com o da tela */
	
	/* Imprime as pessoas */
	imprimePessoas(buffer, lista_p);

	/* Imprime os estaticos */
	imprimeEstaticos(buffer, lista_e);

	/* Imprime e controla os botes */
	controlaBote1(buffer, &lista_b -> bt, deltaT);
	controlaBote2(buffer, &lista_b -> prox -> bt, deltaT);

	/* Imprime Cabecalho */
	imprimeCabecalho(buffer, lista_b);

	blit(buffer, screen, 0, 0, 0, 0, screen->w, screen->h);  
	destroy_bitmap(fundo);
	destroy_bitmap(buffer);

}

void controlaBote1(BITMAP *buffer, bote *boat, double deltaT)
{
 int dir = direcao(boat->atr.vel.x, boat->atr.vel.y);
 double ang;

	if( boat->ancora == '0')
	{
		if (key[KEY_LEFT])
		{
			if( (dir += 1) > 7 )
				dir = 0;
			
			ang = rotacaoBote(dir);
			moveBote(dir,0,boat,deltaT);
			rotate_sprite(buffer, boat->atr.desenho, boat->atr.pos.x, boat->atr.pos.y, ang);
		}
		else if (key[KEY_RIGHT])
		{
			if( (dir -= 1) < 0 )
				dir = 7;
			
			ang = rotacaoBote(dir);
			moveBote(dir,0,boat,deltaT);
			rotate_sprite(buffer, boat->atr.desenho, boat->atr.pos.x, boat->atr.pos.y, ang);
		}
		else if (key[KEY_UP])/*propulsao*/
		{
			ang = rotacaoBote(dir);
			moveBote(dir, ACELERACAO,boat, deltaT);
			rotate_sprite(buffer, boat->atr.desenho, boat->atr.pos.x, boat->atr.pos.y, ang);	
		}
		else if (key[KEY_DOWN])/*freio*/
		{
			if( (modulo(boat->atr.vel)-FREIO) > 0 )
				moveBote(dir,((-1)*FREIO),boat, deltaT);
			else
				moveBote(dir,(-1)*modulo(boat->atr.vel),boat, deltaT);

			ang = rotacaoBote(dir);
			rotate_sprite(buffer, boat->atr.desenho, boat->atr.pos.x, boat->atr.pos.y, ang);
		}
		else if (key[KEY_ENTER])
		{
			ang = rotacaoBote(dir);
			boat->ancora = '1';
			moveBote(dir,(-1)*modulo(boat->atr.vel),boat, deltaT);				
			rotate_sprite(buffer, boat->atr.desenho, boat->atr.pos.x, boat->atr.pos.y, ang);	
		}
		else  
		{
			ang = rotacaoBote(dir);
			moveBote(dir,0,boat, deltaT);
			rotate_sprite(buffer, boat->atr.desenho, boat->atr.pos.x, boat->atr.pos.y, ang);
		}
	}
	else
	{
		if (key[KEY_ENTER])
			boat->ancora = '0';
		
		ang = rotacaoBote(dir);
		rotate_sprite(buffer, boat->atr.desenho, boat->atr.pos.x, boat->atr.pos.y, ang);	
	}
	circle(buffer, boat->atr.pos.x,boat->atr.pos.y ,boat->atr.raio,makecol(255, 0, 0));
}

void controlaBote2(BITMAP *buffer, bote *boat, double deltaT)
{
 int dir = direcao(boat->atr.vel.x, boat->atr.vel.y);
 double ang;

	if( boat->ancora == '0')
	{
		if (key[KEY_A])
		{
			if( (dir += 1) > 7 )
				dir = 0;
			
			ang = rotacaoBote(dir);
			moveBote(dir,0,boat,deltaT);
			rotate_sprite(buffer, boat->atr.desenho, boat->atr.pos.x, boat->atr.pos.y, ang);
		}
		else if (key[KEY_D])
		{
			if( (dir -= 1) < 0 )
				dir = 7;
			
			ang = rotacaoBote(dir);
			moveBote(dir,0,boat,deltaT);
			rotate_sprite(buffer, boat->atr.desenho, boat->atr.pos.x, boat->atr.pos.y, ang);
		}
		else if (key[KEY_W])/*propulsao*/
		{
			ang = rotacaoBote(dir);
			moveBote(dir,ACELERACAO,boat,deltaT);
			rotate_sprite(buffer, boat->atr.desenho, boat->atr.pos.x, boat->atr.pos.y, ang);	
		}
		else if (key[KEY_S])/*freio*/
		{
			if( (modulo(boat->atr.vel)-FREIO) > 0 )
					moveBote(dir,((-1)*FREIO),boat,deltaT);
			else
				moveBote(dir,(-1)*modulo(boat->atr.vel),boat, deltaT);

			ang = rotacaoBote(dir);
			rotate_sprite(buffer, boat->atr.desenho, boat->atr.pos.x, boat->atr.pos.y, ang);
		}
		else if (key[KEY_SPACE])
		{
			ang = rotacaoBote(dir);
			boat->ancora = '1';
			moveBote(dir,(-1)*modulo(boat->atr.vel),boat, deltaT);				
			rotate_sprite(buffer, boat->atr.desenho, boat->atr.pos.x, boat->atr.pos.y, ang);	
		}
		else  
		{
			ang = rotacaoBote(dir);
			moveBote(dir,0,boat,deltaT);
			rotate_sprite(buffer, boat->atr.desenho, boat->atr.pos.x, boat->atr.pos.y, ang);
		}
	}
	else
	{
		if (key[KEY_SPACE]) 
			boat->ancora = '0';
		
		ang = rotacaoBote(dir);
		rotate_sprite(buffer, boat->atr.desenho, boat->atr.pos.x, boat->atr.pos.y, ang);	
	}
	circle(buffer, boat->atr.pos.x,boat->atr.pos.y ,boat->atr.raio,makecol(255, 0, 0));
}

void imprimePessoas(BITMAP *buffer, lista_pessoas pessoas)
{
 lista_pessoas aux = pessoas;


	while( aux != NULL)
	{
		draw_sprite(buffer, aux -> pss.atr.desenho, aux -> pss.atr.pos.x, aux -> pss.atr.pos.y);
		circle(buffer, aux->pss.atr.pos.x,aux->pss.atr.pos.y ,aux->pss.atr.raio,makecol(255, 0, 0));
		aux = aux -> prox;
	}

}

void imprimeEstaticos(BITMAP *buffer, lista_estaticos estat)
{
 lista_estaticos aux = estat;


	while( aux != NULL)
	{
		if( aux -> stc.tipo == 'r' )
			draw_sprite(buffer, aux->stc.desenho, aux->stc.pos.x, aux->stc.pos.y);
		else
			draw_sprite(buffer, aux->stc.desenho, aux->stc.pos.x-132, aux->stc.pos.y-66);

	 circle(buffer, aux->stc.pos.x,aux->stc.pos.y ,aux->stc.raio,makecol(255, 0, 0));
	 aux = aux -> prox;
		
	}
}




void imprimeCabecalho(BITMAP *buffer, lista_botes botes)
{
	BITMAP *coracao, *pessoa, *ancora;


	/* NOME DOS JOGADORES */
	textout_ex(buffer, font, "Jogador1", 30, 20, makecol(0, 0, 255), -1);
	textout_ex(buffer, font, "Jogador2", 930, 20, makecol(255, 0, 0), -1);

	/* VIDAS */
	coracao = load_bitmap("imagens/coracao.bmp",desktop_palette);
	
	textprintf_ex(buffer, font, 120, 20, makecol(0, 0, 255), -1, "%u x", botes -> prox -> bt.vidas);
	draw_sprite(buffer, coracao, 150, 10);
	
	textprintf_ex(buffer, font, 780, 20, makecol(255, 0, 0), -1, "%u x", botes ->  bt.vidas);
	draw_sprite(buffer, coracao, 810, 10);

	/* CARGA */
	pessoa = load_bitmap("imagens/pessoa2.bmp",desktop_palette);
	
	textprintf_ex(buffer, font, 190, 20, makecol(0, 0, 255), -1, "%u x", botes -> prox -> bt.carga);
	draw_sprite(buffer, pessoa, 220, 15);
	
	textprintf_ex(buffer, font, 850, 20, makecol(255, 0, 0), -1, "%u x", botes -> bt.carga);
	draw_sprite(buffer, pessoa, 880, 15);


	/* PONTOS */
	textprintf_ex(buffer, font, 260, 20, makecol(0, 0, 255), -1, "%d", botes -> prox -> bt.pontos);
	textprintf_ex(buffer, font, 720, 20, makecol(255, 0, 0), -1, "%d", botes -> bt.pontos);

	/* ANCORAS */
	if( botes -> prox -> bt.ancora == '1')
	{
		ancora = load_bitmap("imagens/ancora1.bmp",desktop_palette);
		draw_sprite(buffer, ancora, 320, 10);
		destroy_bitmap(ancora);
	}
	if( botes -> bt.ancora == '1')
	{
		ancora = load_bitmap("imagens/ancora2.bmp",desktop_palette);
		draw_sprite(buffer, ancora, 670, 10);
		destroy_bitmap(ancora);
	}
	
	destroy_bitmap(coracao);
	destroy_bitmap(pessoa);
}

