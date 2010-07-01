%{
  #include <string.h>
  #include "autoconf.h"
  #include "bison.h"
%}

%%

"tt" { return  tt; }
"nj" { return nj; }
"hg" { return hg; }
"di" { return di; }
"nv" { return nv; }
"vmax" { printf("\nEncontrado vmax"); return vmax; }
"vmin" { return vmin; }
"fcp" { return fcp; }
"vcp" { return vcp; }
"nr" { return nr; }
"=" {printf("\nEncontrado atr\n");return atribuicao;}
";" {printf("\nEncontrado sep\n");return separador;}
[0-9]+ { printf("\nEncontrado NUM\n");
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
