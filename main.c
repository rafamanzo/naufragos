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
	int framesPorSegundo,tempoMaximo;
	double deltaT;

	clock_t inicio, anterior, var;
	fila naufragos = NULL;

	srand(time(NULL));
	
	if( argc != 3 )
	{
		printf("Faltou parametros!\n");
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
	naufragos = geraPessoas(naufragos, 200, 768, 1024);
	naufragos = geraRecifes(naufragos, 40, 768, 1024);
	naufragos = geraBotes(naufragos, 768, 1024);
	
        
        inicio = clock();
        anterior = 0;
        
        framesPorSegundo = atoi(argv[1]);
        tempoMaximo = atoi(argv[2]);

	/*while( !key[KEY_ESC] );*/

        while( clock() - inicio < tempoMaximo*CLOCKS_PER_SEC) 
        {
               var = clock() - anterior;

                if( var > CLOCKS_PER_SEC/ framesPorSegundo )
                {  
                        deltaT = (double)var/(double)CLOCKS_PER_SEC; 
      
			                  naufragos = atualizaMar(naufragos, 768, 1024, deltaT);
			                  imprimeMar(naufragos);
                        anterior = clock();
                } 
    

        }
 	liberaMar(naufragos);
	allegro_exit();
 	exit(0);
}
