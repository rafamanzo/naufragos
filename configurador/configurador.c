#include <stdlib.h>
#include "configs.h"
#include "highscores.h"
#include "configurador.h"

int inicConfigurador(){
  inicFlex();

  colocacao = 0;
  pessoas.jogador1=NULL;
  pessoas.jogador2=NULL;
  tela.comprimento=800;
  tela.altura=600;
  vidas_iniciais=5;
  velocidade_maxima=10;
  velocidade_minima=5;
  frequencia_criacao_pessoas=1;
  velocidade_criacao_pessoas=2;
  numero_recifes=10;

  return 1;
}
