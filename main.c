#include "bib/tipos.h"
#include "bib/colisao.h"
#include "bib/desloc.h"
#include "bib/mar.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>


int main(int argc, char *argv[])
{
	int framesPorSegundo,tempoMaximo, velMedia; 
	double freqPessoas;
	double deltaT, acumulador;

	clock_t inicio, anterior, var;
	fila naufragos = NULL;

	srand(time(NULL));
	
	if( argc == 1 )
	{
		printf("Executando com valores padrao.\n");
		framesPorSegundo = 20; 
		tempoMaximo = 30;
		freqPessoas = 1; 
		velMedia = 3;
	}

	else if( argc == 5 )
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
	}
	else 
	{
		printf("\nComo executar:\n./Naufragos para executar com valores padrao ou\n./Naufragos arg1 arg2 arg3 arg4, no qual \n\targ 1 - Frames por Segundo\n\targ 2 - Tempo de Execucao do Programa em Segundos\n\targ 3 - Frequencia de Criacao de Pessoas\n\targ 4 - Velocidade Media de Criacao de Pessoas\nExemplo: ./Naufragos ou ./Naufragos 10 10 0.25 4\n\n");
		exit(-1);
	}

	allegro_init();

	install_keyboard();

	set_color_depth(32);

	if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024, 768, 0, 0) < 0)
	{
		printf("Erro ao inicializar o modo grafico.\n");
		exit(-1);
	}

	set_palette(desktop_palette);

	naufragos = geraAsimov(naufragos, 768, 1024);
	naufragos = geraRecifes(naufragos, 20, 768, 1024);
	naufragos = geraBotes(naufragos, 768, 1024);

        inicio = clock();
        anterior = 0;
	acumulador = 0.0;
        
        while( clock() - inicio < tempoMaximo*CLOCKS_PER_SEC) 
        {
               var = clock() - anterior;

                if( var > CLOCKS_PER_SEC/ framesPorSegundo )
                {  
                        deltaT = (double)var/(double)CLOCKS_PER_SEC; 
      
			                  naufragos = atualizaMar(naufragos, 768, 1024, deltaT);
			                  imprimeMar(naufragos);
			
			if( acumulador >= freqPessoas )
			{
				naufragos = geraPessoas(naufragos, (int) (velMedia*freqPessoas), 768, 1024);				
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
