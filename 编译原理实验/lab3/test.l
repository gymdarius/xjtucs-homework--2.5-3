%{
    #include<stdlib.h>
    void yyerror(char*);
    #include "calc.tab.h"  
%}

%%
[0-9]+      {yylval=atoi(yytext); return NUMBER;}
[-+*/()\n]   {return *yytext;}
[ \t]       ;

.    	    yyerror("Error");

%%
int yywrap(void)
{
  return 1;
}