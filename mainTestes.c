#include "bib/tipos.h"
#include "bib/colisao.h"
#include "bib/desloc.h"
#include "bib/mar.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void robustez(int framesPorSegundo, int tempoMaximo, int numeroDePessoas)
{
	double deltaT;
	clock_t inicio, anterior, var;
	celula **mar;
	srand(time(NULL));

	mar = iniciaMar(30, 120);
	mar = gera_pessoas(mar, numeroDePessoas, 0, 30, 120);
	imprimeMar(mar, 30, 120);

        inicio = clock();
        anterior = 0;

        while( clock() - inicio < tempoMaximo*CLOCKS_PER_SEC) 
        {
               var = clock() - anterior;

                if( var > CLOCKS_PER_SEC/framesPorSegundo )
                {  
                        deltaT = (double)var/(double)CLOCKS_PER_SEC; 
      
        	        atualizaMar(mar, 30, 120, deltaT);
                        system("clear");
        	        imprimeMar(mar, 30, 120);
                        anterior = clock();
                } 
	}  
     
  	liberaMar(mar, 30, 120);

	printf("Sobreviveu para %d\n",numeroDePessoas);
}

void variacoes(int framesPorSegundo, int tempoMaximo, int numeroDePessoas)
{
	int linha, coluna, cont = 0;
	double veloc, vMIN = 10, vMAX = 0, vMedia = 0,deltaT;
	char tipo;
	vetor v;
	celula ** mar;
	clock_t inicio, anterior, var;
	srand(time(NULL));
	
	mar = iniciaMar(30, 120);
	mar = gera_pessoas(mar, 40, 0, 30, 120);

        inicio = clock();
        anterior = 0;
        
        while(clock() - inicio < tempoMaximo*CLOCKS_PER_SEC) 
        {
               var = clock() - anterior;

                if(var > CLOCKS_PER_SEC/framesPorSegundo )
                {  
                        deltaT = (double)var/(double)CLOCKS_PER_SEC; 
      
        	        atualizaMar(mar, 30, 120, deltaT);
			for( linha = 0; linha < 30; linha++)
			{
				for(coluna = 0; coluna < 120 ; coluna++)
				{
					tipo = mar[linha][coluna].categoria;
				
					if(tipo == 'p')
                		        {
                		               v = mar[linha][coluna].f->p.vel;
                		               veloc = modulo(v);  

					       if(veloc < vMIN)
							vMIN = veloc;
					       else if(veloc > vMAX)
							vMAX = veloc;				
					 
					 vMedia += veloc;
						 cont++;
                		        }
	
				}
			}
	                anterior = clock();
                }        

        }
	vMedia = vMedia/cont;
	printf("\nt: %d Vmax: %f, Vmin: %f, Vmedia: %f\n\n", tempoMaximo,vMAX,vMIN,vMedia);
 	liberaMar(mar, 30, 120);
}

void corretude(int framesPorSegundo, int tempoMaximo, int numeroDePessoas )
{

	celula **mar;
	double deltaT;
	clock_t inicio, anterior, var;

	mar = iniciaMar(4, 16);

	mar = gera_pessoas(mar, numeroDePessoas, 0, 4, 16);

	imprimeMar(mar, 4, 16);
 	
 	srand(time(NULL));

	inicio = clock();
	anterior = 0;

        while( clock() - inicio < tempoMaximo*CLOCKS_PER_SEC) 
        {
               var = clock() - anterior;

                if( var > CLOCKS_PER_SEC/framesPorSegundo )
                {  
                        deltaT = (double)var/(double)CLOCKS_PER_SEC; 
      
        	        atualizaMar(mar, 4, 16, deltaT);
                        system("clear");
        	        imprimeMar(mar, 4, 16);
                        anterior = clock();
                }        

        }

	liberaMar(mar, 4, 16);
}




int main(int argc, char *argv[])
{
	int opcao, fps, numeroDePessoas, tempoMaximo;

	while(1)
	{
		printf("Digite 1 para testar robustez, 2 para testar corretude, 3 para variacoes, 0 para sair.\n");
		scanf(" %d",&opcao);  	
		
		switch(opcao)
		{
			case(1):
			{
				printf("Robustez - Digite fps,tempoMaximo,numeroDePessoas:\n");
				scanf(" %d,%d,%d",&fps, &tempoMaximo, &numeroDePessoas);
				robustez(fps, tempoMaximo, numeroDePessoas);
				break;
			}
			case(2):
			{
				printf("Robustez - Digite fps,tempoMaximo,numeroDePessoas:\n");
				scanf(" %d,%d,%d",&fps, &tempoMaximo, &numeroDePessoas);
				corretude(fps, tempoMaximo, numeroDePessoas);
				break;
			}
			case(3):
			{
				printf("Robustez - Digite fps,tempoMaximo,numeroDePessoas:\n");
				scanf(" %d,%d,%d",&fps, &tempoMaximo, &numeroDePessoas);
				variacoes(fps, tempoMaximo, numeroDePessoas);
				break;
			}
			case(0):
				exit(0);
			default:
				printf("Opcao invalida!\n");
				break;
		}
	}
			
 return 0;
}






