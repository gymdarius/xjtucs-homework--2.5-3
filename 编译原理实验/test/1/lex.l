%{
    int wordCounter = 0;
    int charCounter=0;
    int column =0,line=1;
    void addLine(int);
    void addColumn(int);
    void clearColumn();
    void addChar(int);
    void addWord(int);
%}

line_comment           (\/\/.*\n)

char                   '[^']'
string                 \"[^\"]*\"
letter                 [A-Za-z_]
digit                  [0-9]
identifier             {letter}({letter}|{digit})*
reserveword            "break"|"main"|"continue"|"else"|"float"|"for"|"if"|"int"|"return"|"void"|"while"
int                    {digit}+
float                  {digit}*(\.{digit}+)?(e|E[+\-]?{digit}+)?
operator               "-"|"+"|"="|"=="|"*"|"/"|"<="|">="
delimiters             "("|")"|"{"|"}"|";"
il_char                \'[^']{4}
il_string              \"[^"]{30}
il_identifier          ({digit}|{digit}*(\.{digit}+)?(e|E[+\-]?{digit}+)?)({letter}|{digit})*{letter}({letter}|{digit})*


%%

{line_comment}  {
    printf("Line=%3d,Column=%3d : 这是一个注释 %s",line,column,yytext);
    addChar(yyleng);
    clearColumn();
    addLine(1);
}
{char}  {
    printf("Line=%3d,Column=%3d : 这是一个char型 %s\n",line,column,yytext);
    addChar(yyleng);
    addColumn(yyleng);
}
{string}    {
    printf("Line=%3d,Column=%3d : 这是一个string类型 %s\n",line,column,yytext);
    addColumn(yyleng);
    addChar(yyleng);
}
{reserveword} {
    printf("Line=%3d,Column=%3d : 这是关键字 %s\n",line,column,yytext);
    addChar(yyleng);
    addColumn(yyleng);
    addWord(1);
}
{identifier}    {
    printf("Line=%3d,Column=%3d : 这是一个标识符 %s\n",line,column,yytext);
    addChar(yyleng);
    addColumn(yyleng);
    addWord(1);
}

{int}   {
    addChar(yyleng);
    addColumn(yyleng);
    printf("Line=%3d,Column=%3d : 这是一个int型 %s\n",line,column,yytext);
}
{float} {
    addChar(yyleng);
    addColumn(yyleng);
    printf("Line=%3d,Column=%3d : 这是一个float型 %s\n",line,column,yytext);
}
{operator}  {
    addColumn(1);
    addChar(1);
    printf("Line=%3d,Column=%3d : 这是一个操作符 %s\n",line,column,yytext);
}

{delimiters} {
    addColumn(1);
    addChar(1);
    printf("Line=%3d,Column=%3d : 这是一个界符 %s\n",line,column,yytext);
}
{il_string} {
    addChar(yyleng);
    addColumn(yyleng);
    printf("错误(Line=%3d,Column=%3d): 错误的string型: %s\n",line,column,yytext);
}
{il_identifier} {
    addChar(yyleng);
    addColumn(yyleng);
    printf("错误(Line=%3d,Column=%3d): 错误的标识符: %s\n",line,column,yytext);
}
{il_char}   {
    addChar(yyleng);
    addColumn(yyleng);
    printf("错误(Line=%3d,Column=%3d): 错误的char型: %s\n",line,column,yytext);
}
.       {
    addChar(1);
    addColumn(1);
}

\n      {
    addChar(1);
    addLine(1);
    clearColumn();
}


%%
int main(void)
{
    puts("******************************************");
    puts("                词法分析器                  ");
    puts("******************************************");
    yylex();
    puts("******************************************");
    puts("计数");
    printf("字符数:%5d\n",charCounter);
    printf("行数:%5d\n",line);
    printf("字数:%5d\n",wordCounter);
    puts("******************************************");
    return 0;
}
int yywrap()    {
    return 1;
}

void addLine(int cnt)   {
    line += cnt;
}
void addColumn(int cnt) {
    column += cnt;
}
void clearColumn()  {
    column = 0;
}
void addChar(int leng)  {
    charCounter += leng;
}
void addWord(int cnt)   {
    wordCounter += cnt;
}

