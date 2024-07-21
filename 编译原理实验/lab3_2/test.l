%option yylineno
 
%{
    #include "y.tab.h"
    #define UNEXPECTED 0
%}
 
INT                 int
VOID                void
CONST               const
IF                  if
ELSE                else
WHILE               while
BREAK               break
CONTINUE            continue
RETURN              return
MULDIVSUR           "*"|"/"|"%"
ADDSUB              "+"|"-"
CMP                 "<"|">"|"<="|">="
EQNEQ               "=="|"!="
ASSIGN              "="
NONZERO             [1-9]
DIGIT               [0-9]
LETTER              [A-Za-z]
OCTAL_DIGIT         [0-7]
OCTAL_CONST         0{OCTAL_DIGIT}*
ILLEGAL_OCTAL_CONST 0[0-9a-wy-zA-WY-Z]({LETTER}|{DIGIT})*
HEX_PREFIX          0x|0X
HEX_DIGIT           [0-9a-fA-F]
HEX_CONST           {HEX_PREFIX}{HEX_DIGIT}+
ILLEGAL_HEX_CONST   {HEX_PREFIX}({LETTER}|{DIGIT})*
NONDIGIT            {LETTER}|"_"
ID                  {NONDIGIT}({DIGIT}|{NONDIGIT})*
DEC_CONST           {NONZERO}{DIGIT}*  
COMMENT1            "/*"[^*]*"*"+([^*/][^*]*"*"+)*"/"
COMMENT2            "//".*                                                                                
 
%%
 
{INT}                   { yylval.str=strdup(yytext); return INT; }
{VOID}                  { yylval.str=strdup(yytext); return VOID; }
{OCTAL_CONST}           { yylval.str=strdup(yytext); return OCTAL_CONST; }
{ILLEGAL_OCTAL_CONST}   { yylval.str=strdup(yytext); return HEX_CONST; }
{HEX_CONST}             { yylval.str=strdup(yytext); return HEX_CONST; }
{ILLEGAL_HEX_CONST}     { yylval.str=strdup(yytext); return DEC_CONST; }
{DEC_CONST}             { yylval.str=strdup(yytext); return DEC_CONST; }
{CONST}                 { yylval.str=strdup(yytext); return CONST; }
{IF}                    { yylval.str=strdup(yytext); return IF; }
{ELSE}                  { yylval.str=strdup(yytext); return ELSE; }
{WHILE}                 { yylval.str=strdup(yytext); return WHILE; }
{BREAK}                 { yylval.str=strdup(yytext); return BREAK; }
{CONTINUE}              { yylval.str=strdup(yytext); return CONTINUE; }
{RETURN}                { yylval.str=strdup(yytext); return RETURN; }
{MULDIVSUR}             { yylval.str=strdup(yytext); return MULDIVSUR; } 
{ADDSUB}                { yylval.str=strdup(yytext); return ADDSUB; } 
{CMP}                   { yylval.str=strdup(yytext); return CMP; } 
{EQNEQ}                 { yylval.str=strdup(yytext); return EQNEQ; } 
{ASSIGN}                { yylval.str=strdup(yytext); return ASSIGN; }
{ID}                    { yylval.str=strdup(yytext); return ID; }
"("                     { yylval.str=strdup(yytext); return yytext[0]; }
")"                     { yylval.str=strdup(yytext); return yytext[0]; }
"["                     { yylval.str=strdup(yytext); return yytext[0]; }
"]"                     { yylval.str=strdup(yytext); return yytext[0]; }
"{"                     { yylval.str=strdup(yytext); return yytext[0]; }
"}"                     { yylval.str=strdup(yytext); return yytext[0]; }
";"                     { yylval.str=strdup(yytext); return yytext[0]; }
","                     { yylval.str=strdup(yytext); return yytext[0]; }
"&&"                    { yylval.str=strdup(yytext); return AND; }
"||"                    { yylval.str=strdup(yytext); return OR; }
{COMMENT1}|{COMMENT2}   { }
[ \t\n]                 { }
.                       { yylval.str=strdup(yytext); return UNEXPECTED; }
%%
 
int yywrap(void) 
{ 
    return 1;
}