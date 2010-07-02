%{
  #include <string.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include "configs.h"
  #include "highscores.h"
  #include "configurador.h"
%}

%token NUM
%token STR
%token tt
%token nj
%token hg
%token di
%token nv
%token vmax
%token vmin
%token fcp
%token vcp
%token nr
%token atribuicao
%token separador

%%

input : 
      | input line ;

line : '\n' { ; }
     | exp '\n' { ; }

exp : di exp line { }
    | tt atribuicao NUM separador NUM separador { tela.comprimento = atoi($3); tela.altura = atoi($5); }
    | nj atribuicao STR separador {
                                    if(pessoas.jogador1==NULL){
                                      pessoas.jogador1 = malloc(strlen($3)*sizeof(char));
                                      strcpy(pessoas.jogador1, $3);
                                    }else if(pessoas.jogador2==NULL){
                                      pessoas.jogador2 = malloc(strlen($3)*sizeof(char));
                                      strcpy(pessoas.jogador2, $3);
                                    }
                                  }
    | hg atribuicao STR separador NUM separador { if(colocacao < 10){
                                                    highscores[colocacao].nome = malloc(strlen($3)*sizeof(char));
                                                    strcpy(highscores[colocacao].nome, $3);
                                                    highscores[colocacao++].pontuacao = atoi($5);
                                                  }
                                                }
    | nv atribuicao NUM separador { vidas_iniciais = atoi($3); }
    | vmax atribuicao NUM separador { velocidade_maxima = atoi($3); }
    | vmin atribuicao NUM separador { velocidade_minima = atoi($3); }
    | fcp atribuicao NUM separador { frequencia_criacao_pessoas = atoi($3); }
    | vcp atribuicao NUM separador { velocidade_criacao_pessoas = atoi($3); }
    | nr atribuicao NUM separador { numero_recifes = atoi($3); }
    | NUM line { }
    | STR line { }
    | separador exp { }
%%
yyerror(char *s) {
}

int inicConfigurador(){
  colocacao = 0;
  pessoas.jogador1=NULL;
  pessoas.jogador2=NULL;
}

/*int main(){
  colocacao = 0;
  pessoas.jogador1=NULL;
  pessoas.jogador2=NULL;
  
  yyparse();

  printf("\nTela %dx%d", tela.comprimento, tela.altura);
  printf("\nJogador 1 %s", pessoas.jogador1);
  printf("\nJogador 2 %s", pessoas.jogador2);
  printf("\nHighscore %s: %d", highscores[0].nome, highscores[0].pontuacao);
  printf("\nVidas iniciais %d", vidas_iniciais);
  printf("\nVmax %d", velocidade_maxima);
  printf("\nvmin %d", velocidade_minima);
  printf("\nfcp %d", frequencia_criacao_pessoas);
  printf("\nvcp %d", velocidade_criacao_pessoas);
  printf("\nNumero recifes %d", numero_recifes);
}*/
