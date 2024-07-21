%{
	#include <stdio.h>
	#include <string.h>
    int lineon = 1;
    int line=1;
    int nchar,nword;
	char  token_name[50][20];
	typedef enum {
		head,
		NCHAR,
		letter,
		digit,
		IDENFR,
		INTCON,
		STRCON,
		MAINTK,
		CONSTTK,
		INTTK,
		BREAKTK,
		CONTINUETK,
		IFTK,
		ELSETK,
		WHILETK,
		GETINTTK,
		PRINTFTK,
		RETURNTK,
		PLUS,
		MINU,
		VOIDTK,
		NOT,
		AND,
		OR,
		MULT,
		DIV,
		MOD,
		LSS,
		LEQ,
		GRE,
		GEQ,
		EQL,
		NEQ,
		ASSIGN,
		SEMICN,
		COMMA,
		LPARENT,
		RPARENT,
		LBRACK,
		RBRACK,
		LBRACE,
		RBRACE,
		FLOAT,
		il_identifier
	} TokenType;

	typedef struct Token{
		TokenType type;
		char * value;
		int line;
		struct Token *next;
	} Token;
	Token * head_node;
	Token * last_node;

	Token* token_new(TokenType type, char* value, int line,Token* node);
	void token_free(Token* token);
	void token_print(Token* token);
    void addLine(int);
%}

line_comment    (\/\/.*\n)

char  	'[^']'
letter  [A-Za-z_]
digit   [0-9]
IDENFR	{letter}({letter}|{digit})*
INTCON	{digit}+
STRCON   \"[^\"]*\"
MAINTK	"main"
CONSTTK	"const"
INTTK 	"int"
BREAKTK	"break"
CONTINUETK "continue"
IFTK	"if"
ELSETK	"else"
WHILETK	"while"
GETINTTK	"getint"
PRINTFTK	"printf"
RETURNTK "return"
PLUS	"+"
MINU	"-"
VOIDTK	"void"
NOT	"!"
AND	"&&"
OR	"||"
MULT	"*"
DIV	"/"
MOD	"%"
LSS	"<"
LEQ	"<="
GRE	">"
GEQ	">="
EQL	"=="
NEQ	"!="
ASSIGN	"="
SEMICN	";"
COMMA	","
LPARENT	"("
RPARENT	")"
LBRACK	"["
RBRACK	"]"
LBRACE	"{"
RBRACE	"}"
FLOAT                 {digit}*(\.{digit}+)?(e|E[+\-]?{digit}+)?
il_identifier          ({digit}|{digit}*(\.{digit}+)?(e|E[+\-]?{digit}+)?)({letter}|{digit})*{letter}({letter}|{digit})*


%%

{line_comment}  {
    if(lineon) printf("Line=%3d ",line);
    printf("line_comment %s",yytext);
    addLine(1);
}
{char}  {
	Token* Tnode =token_new(NCHAR,yytext,line,NULL);
	last_node->next = Tnode;
	last_node = Tnode;
	token_print(Tnode);
	nchar+=yyleng;
	nword++;
}
{STRCON}  {
	Token* Tnode =token_new(STRCON,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{MAINTK}   {
	Token* Tnode =token_new(MAINTK,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{CONSTTK}   {
	Token* Tnode =token_new(CONSTTK,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{INTTK}   {
	Token* Tnode =token_new(INTTK,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{BREAKTK}   {
	Token* Tnode =token_new(BREAKTK,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{CONTINUETK}   {
	Token* Tnode =token_new(CONTINUETK,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{IFTK}   {
	Token* Tnode =token_new(IFTK,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{ELSETK}   {
	Token* Tnode =token_new(ELSETK,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{WHILETK}   {
	Token* Tnode =token_new(WHILETK,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{GETINTTK}   {
	Token* Tnode =token_new(GETINTTK,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{PRINTFTK}   {
	Token* Tnode =token_new(PRINTFTK,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{RETURNTK}   {
	Token* Tnode =token_new(RETURNTK,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{VOIDTK}   {
	Token* Tnode =token_new(VOIDTK,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{IDENFR}    {
	Token* Tnode =token_new(IDENFR,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}

{INTCON}   {
	Token* Tnode =token_new(INTCON,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{FLOAT}   {
	Token* Tnode =token_new(FLOAT,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{NOT}   {
	Token* Tnode =token_new(NOT,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{AND}   {
	Token* Tnode =token_new(AND,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{OR}   {
	Token* Tnode =token_new(OR,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{PLUS}   {
	Token* Tnode =token_new(PLUS,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{MINU}   {
	Token* Tnode =token_new(MINU,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{MULT}   {
	Token* Tnode =token_new(MULT,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{DIV}   {
	Token* Tnode =token_new(DIV,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{MOD}   {
	Token* Tnode =token_new(MOD,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{LSS}   {
	Token* Tnode =token_new(LSS,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{LEQ}   {
	Token* Tnode =token_new(LEQ,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{GRE}   {
	Token* Tnode =token_new(GRE,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{GEQ}   {
	Token* Tnode =token_new(GEQ,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{EQL}   {
	Token* Tnode =token_new(EQL,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{NEQ}   {
	Token* Tnode =token_new(NEQ,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{ASSIGN}   {
	Token* Tnode =token_new(ASSIGN,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{SEMICN}   {
	Token* Tnode =token_new(SEMICN,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{COMMA}   {
	Token* Tnode =token_new(COMMA,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{LPARENT}   {
	Token* Tnode =token_new(LPARENT,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{RPARENT}   {
	Token* Tnode =token_new(RPARENT,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{LBRACK}   {
	Token* Tnode =token_new(LBRACK,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{RBRACK}   {
	Token* Tnode =token_new(RBRACK,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{LBRACE}   {
	Token* Tnode =token_new(LBRACE,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{RBRACE}   {
	Token* Tnode =token_new(RBRACE,yytext,line,NULL);
	token_print(Tnode);
	last_node->next = Tnode;
	last_node = Tnode;
	nchar+=yyleng;
	nword++;
}
{il_identifier} {
	if(lineon) printf("Line=%3d ",line);
    printf("错误: 错误的标识符: %s\n",yytext);
}
\n      {
    addLine(1);
}
. {
if(lineon) printf("Line=%3d ",line);
    printf("错误: 不可识别的输入: %s\n",yytext);
}


%%
int main(void)
{	
	head_node = token_new(head,"begin",0,NULL);
	last_node = head_node;

	strcpy(token_name[0], "head");
    strcpy(token_name[1], "NCHAR");
    strcpy(token_name[2], "letter");
    strcpy(token_name[3], "digit");
    strcpy(token_name[4], "IDENFR");
    strcpy(token_name[5], "INTCON");
    strcpy(token_name[6], "STRCON");
    strcpy(token_name[7], "MAINTK");
    strcpy(token_name[8], "CONSTTK");
    strcpy(token_name[9], "INTTK");
    strcpy(token_name[10], "BREAKTK");
    strcpy(token_name[11], "CONTINUETK");
    strcpy(token_name[12], "IFTK");
    strcpy(token_name[13], "ELSETK");
    strcpy(token_name[14], "WHILETK");
    strcpy(token_name[15], "GETINTTK");
    strcpy(token_name[16], "PRINTFTK");
    strcpy(token_name[17], "RETURNTK");
    strcpy(token_name[18], "PLUS");
    strcpy(token_name[19], "MINU");
    strcpy(token_name[20], "VOIDTK");
    strcpy(token_name[21], "NOT");
    strcpy(token_name[22], "AND");
    strcpy(token_name[23], "OR");
    strcpy(token_name[24], "MULT");
    strcpy(token_name[25], "DIV");
    strcpy(token_name[26], "MOD");
    strcpy(token_name[27], "LSS");
    strcpy(token_name[28], "LEQ");
    strcpy(token_name[29], "GRE");
    strcpy(token_name[30], "GEQ");
    strcpy(token_name[31], "EQL");
    strcpy(token_name[32], "NEQ");
    strcpy(token_name[33], "ASSIGN");
    strcpy(token_name[34], "SEMICN");
    strcpy(token_name[35], "COMMA");
    strcpy(token_name[36], "LPARENT");
    strcpy(token_name[37], "RPARENT");
    strcpy(token_name[38], "LBRACK");
    strcpy(token_name[39], "RBRACK");
	strcpy(token_name[40], "LBRACE");
    strcpy(token_name[41], "RBRACE");
    strcpy(token_name[42], "FLOAT");
    strcpy(token_name[43], "il_identifier");

    yylex();
    printf("nchar=%d, nword=%d, nline=%d\n",nchar, nword, line);
    return 0;
}
int yywrap()    {
    return 1;
}

void addLine(int cnt)   {
    line += cnt;
}

Token* token_new(TokenType type, char* value, int line,Token* node) {
    Token* token = (Token*)malloc(sizeof(Token));
    token->type = type;
    token->value = strdup(value); // 使用strdup分配内存并复制字符串
    token->line = line;
	token->next = node;
    return token;
}

void token_free(Token* token) {
    if (token != NULL) {
        free(token->value);
        free(token);
    }
}

void token_print(Token* token) {
    if (token != NULL) {
		if(lineon) printf("Line=%3d ",token->line);
        printf("%s %s\n",
               token_name[token->type], token->value);
    }
}


