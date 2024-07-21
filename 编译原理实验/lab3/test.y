%token NUMBER
%left '+' '-' '*' '/'

%{
    #include <stdio.h>
    #include <math.h>
    void yyerror(char *s);
    int yylex();    
%}

%%
    
    prog: 
        | prog expr '\n' { printf("%d\n", $2); };
    expr:
        expr '+' term { $$ = $1 + $3; }
        | expr '-' term { $$ = $1 - $3; }
        | term
    term:
        | term '*' factor { $$ = $1 * $3; }
        | term '/' factor { $$ = $1 / $3; }        
        | factor
        ;
    factor:
        NUMBER {};
        | '(' expr ')' { $$ = $2; }
        ;
%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

int main() {
    yyparse();
    return 0;
}