%{
  #include <string.h>
  #include <stdlib.h>
  #include <stdio.h>
  #include "configurador.h"
  #include "bison.h"
%}

%%

"tt" { return  tt; }
"nj" { return nj; }
"hg" { return hg; }
"di" { return di; }
"nv" { return nv; }
"vmax" { return vmax; }
"vmin" { return vmin; }
"fcp" { return fcp; }
"vcp" { return vcp; }
"nr" { return nr; }
"=" { return atribuicao;}
";" { return separador;}
[0-9]+ { 
         yylval = malloc(strlen(yytext)*sizeof(char));
         strcpy(yylval, yytext);
         return NUM;
       }
[A-Za-z]+ {
            yylval = malloc(strlen(yytext)*sizeof(char));
            strcpy(yylval, yytext);
            return STR;
          }
.|\n      {return yytext[0];}

%%

int inicFlex(){
  yyin = fopen("configurador/config.sys", "r");
  if(yyin == NULL){
    printf("Arquivo de configuracao nao pode ser aberto!\n");
    exit(-1);
  }
}
