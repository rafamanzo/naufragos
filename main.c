#include "bib/tipos.h"
#include "bib/colisao.h"
#include "bib/desloc.h"
#include "bib/mar.h"
#include "configurador/bison.h"
#include "configurador/configs.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>


int main(int argc, char *argv[])
{
/*O main contara principalmente com a implementacao de um manual para caso o cliente nao digite os argumentos necessarios,
	iniciará as estruturas do mar (botes, asimov e recifes) e as pessoas serão geradas de acordo com uma frequencia e velocidades determinadas
		nos argumentos.*/
	int framesPorSegundo,tempoMaximo, velMedia, numeroDeRecifes; 
	double freqPessoas;
	double deltaT, acumulador;

	clock_t inicio, anterior, var;
	fila naufragos = NULL;

	srand(time(NULL));
	
	if( argc == 1 )
	{
		printf("Executando com valores padrao.\n");
		framesPorSegundo = 30; 
		tempoMaximo = 30;
		freqPessoas = 1; 
		velMedia = 3;
		numeroDeRecifes = 20;
	}

	else if( argc == 6 )
	{
		if( (framesPorSegundo = atoi(argv[1])) <= 0 )
		{
			printf("ERRO: arg1 - Frames por Segundo deve ser maior que 0.\n");
			exit(-1);
		}
		if( (tempoMaximo = atoi(argv[2])) <= 0 )
		{
			printf("ERRO: arg2 - Tempo de Execucao do Programa deve ser maior que 0.\n");
			exit(-1);
		}  
        	if( (freqPessoas = atof(argv[3])) <= 0.0 )
		{
			printf("ERRO: arg3 - Frequencia de Criacao de Pessoas deve ser maior que 0.\n");
			exit(-1);
		}
		if( (velMedia = atoi(argv[4])) <= 0 )
		{
			printf("ERRO: arg4 - Velocidade Media de Criacao de Pessoas deve ser maior que 0.\n");
			exit(-1);
		}
		if( (numeroDeRecifes = atoi(argv[5])) < 0 )
		{
			printf("ERRO: arg5 - Numero de Recifes deve ser maior ou igual a 0.\n");
			exit(-1);
		}
	}
	else 
	{
		printf("\nComo executar:\n./Naufragos para executar com valores padrao ou\n./Naufragos arg1 arg2 arg3 arg4 arg5, no qual \n\targ 1 - Frames por Segundo\n\targ 2 - Tempo de Execucao do Programa em Segundos\n\targ 3 - Frequencia de Criacao de Pessoas\n\targ 4 - Velocidade Media de Criacao de Pessoas\n\targ 5 - Numero de Recifes\nExemplo: ./Naufragos ou ./Naufragos 20 10 1 4 10\n\n");
		exit(-1);
	}

  inicConfigurador();
  yyparse();

	allegro_init();

	install_keyboard();

	set_color_depth(32);

	if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, tela.comprimento, tela.altura, 0, 0) < 0)
	{
		printf("Erro ao inicializar o modo grafico.\n");
		exit(-1);
	}

	set_palette(desktop_palette);

	naufragos = geraAsimov(naufragos, tela.altura, tela.comprimento);
	naufragos = geraRecifes(naufragos, numero_recifes, tela.altura, tela.comprimento);
	naufragos = geraBotes(naufragos, tela.altura, tela.comprimento);

        inicio = clock();
        anterior = 0;
	acumulador = 0.0;
        
        while( clock() - inicio < tempoMaximo*CLOCKS_PER_SEC) 
        {
               var = clock() - anterior;

                if( var > CLOCKS_PER_SEC/ framesPorSegundo )
                {  
                        deltaT = (double)var/(double)CLOCKS_PER_SEC; 
      
			if( acumulador >= 1.0 )
				naufragos = atualizaMar(naufragos, tela.altura, tela.comprimento, deltaT, 1);
			else
				naufragos = atualizaMar(naufragos, tela.altura, tela.comprimento, deltaT, 0);

	                imprimeMar(naufragos);
			
			if( acumulador >= frequencia_criacao_pessoas )
			{
				naufragos = geraPessoas(naufragos, (int) (velocidade_criacao_pessoas*frequencia_criacao_pessoas), tela.altura, tela.comprimento);				
				acumulador = 0.0;
			}
			acumulador += deltaT;	
                        anterior = clock();
                } 
    

        }
 	liberaMar(naufragos);
	allegro_exit();
 	exit(0);
}
