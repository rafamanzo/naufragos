#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "bib/tipos.h"
#include "bib/colisao.h"
#include "bib/desloc.h"
#include "bib/mar.h"
#include "bib/desenhaEControla.h"
#include "entidades/pessoas.h"
#include "entidades/estaticos.h"
#include "entidades/botes.h"
#include "configurador/configurador.h"
#include "configurador/configs.h"


int main(int argc, char *argv[])
{
/*O main contara principalmente com a implementacao de um manual para caso o cliente nao digite os argumentos necessarios,
	iniciará as estruturas do mar (botes, asimov e recifes) e as pessoas serão geradas de acordo com uma frequencia e velocidades determinadas
		nos argumentos.*/
	int tempoMaximo, framesPorSegundo; 
	double deltaT, acumulador;

	clock_t inicio, anterior, var;
	lista_pessoas lista_p = NULL;
  	lista_estaticos lista_e = NULL;
  	lista_botes lista_b = NULL;

	srand(time(NULL));
	
	/*if( argc == 1 )
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
	}*/

  inicConfigurador(); /*inicializa a interface entre o configurador e jogo com valores padrao*/
 	yyparse(); /*faz a leitura do arquivo de entrada*/

  /*mudar isto depois!!!*/
  framesPorSegundo=20;
  tempoMaximo=60;  	
	
  allegro_init();

	install_keyboard();

	set_color_depth(32);

	if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, tela.comprimento, tela.altura, 0, 0) < 0)
	{
		printf("Erro ao inicializar o modo grafico.\n");
		exit(-1);
	}

	set_palette(desktop_palette);

	lista_e = geraAsimov(lista_p, lista_e, lista_b);
	printf("Gerou o Asimov com sucesso.\n");
	lista_e = geraRecifes(lista_p, lista_e, lista_b, numero_recifes);
	printf("Gerou os recifes com sucesso.\n");
	lista_b = geraBotes(lista_p, lista_e, lista_b);
	printf("Gerou os botes com sucesso.\n");

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
				lista_p = atualizaMar(lista_p, lista_e, lista_b, deltaT, 1);
			else
				lista_p = atualizaMar(lista_p, lista_e, lista_b, deltaT, 0);

      			imprimeMar(lista_p, lista_e, lista_b,deltaT);

			if( acumulador >= frequencia_criacao_pessoas )
			{
				lista_p = geraPessoas(lista_p, lista_e, lista_b, (int) (velocidade_criacao_pessoas*frequencia_criacao_pessoas));				
				acumulador = 0.0;
			}
			acumulador += deltaT;	
     			anterior = clock();
    		} 
    

  	}

 	liberaMar(lista_p, lista_e, lista_b);
	allegro_exit();
 	exit(0);

}
