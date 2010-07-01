%{
  #include <string.h>
  #include <stdio.h>
  #include "../bib/configs.h"
  #include "../bib/highscores.h"
  #include "autoconf.h"
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
    | tt atribuicao NUM NUM separador { tela.comprimento = atoi($2); tela.altura = atoi($3); }
    | nj atribuicao NUM separador { jogadores = atoi($2); }
    | hg atribuicao STR NUM separador { strcpy(highscores[colocacao].nome, $2); highscores[colocacao++].pontuacao = atoi($3); }
    | nv atribuicao NUM separador { vidas_iniciais = atoi($2); }
    | vmax atribuicao NUM separador { velocidade_maxima = atoi($3); printf("\nAtribuiu vmax\n"); }
    | vmin atribuicao NUM separador { velocidade_minima = atoi($2); }
    | fcp atribuicao NUM separador { frequencia_criacao_pessoas = atoi($2); }
    | vcp atribuicao NUM separador { velocidade_criacao_pessoas = atoi($2); }
    | nr atribuicao NUM separador { numero_recifes = atoi($2); }
    | NUM line { }
    | STR line { }
    | separador exp { }
%%
yyerror(char *s) {
}

int main(){
  colocacao = 0;
  
  yyparse();

  printf("\nvmax %d", &velocidade_maxima);
  printf("\nvmax %d", &velocidade_maxima);
}
