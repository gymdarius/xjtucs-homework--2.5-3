//AST的构建、输出、释放。
//8进制、16进制转十进制函数 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
 
//flex中自带的三个变量，在Bison中会用到 
extern int yylineno;
extern char* yytext;
extern int yylex();
 
typedef enum {NUM,TEXT} TYPE;

//Bison无法规约时会调用的报错函数。 
void yyerror(const char* msg)
{
    printf("\033[1;31m%s at line %d\033[0m: %s\n",msg,yylineno,yytext);
}
 
int OCT2DEC(char* text)
{
    int sum=0;
    for(int i=1;i<strlen(text);++i)
        sum=sum*8+(text[i]-'0');
    return sum;
}
 
int HEX2DEC(char* text)
{
    int sum=0;
    for(int i=2;i<strlen(text);++i)
    {
        if(text[i]>='0'&&text[i]<='9')
            sum=sum*16+(text[i]-'0');
        else if(text[i]>='a'&&text[i]<='f')
            sum=sum*16+(text[i]-'a'+10);
        else
            sum=sum*16+(text[i]-'A'+10);
    }
    return sum;
}
 
typedef struct ASTnode
{
    TYPE type;	//可以存字符串也可以存整型 
    char* text;
    int num;
    struct ASTnode* next;
    struct ASTnode* child;
}ASTnode;
 
ASTnode* ASThead=NULL;
 
//generate new node
ASTnode* newASTnode(TYPE type, char* text, int num, ASTnode* nxt, ASTnode* child)
{
    ASTnode* node=(ASTnode*)malloc(sizeof(ASTnode)); //不是sizeof(ASTnode*)!!!
    node->type=type;
    if(type==TEXT)
        node->text=strdup(text);
    else
        node->num=num;
    node->next=nxt;
    node->child=child;
    return node;
}
 
//connect sibling nodes
void connectASTnode(int num,...)
{
    va_list valist;
    va_start(valist,num);
    ASTnode* node=va_arg(valist,ASTnode*);
    for(int i=1;i<num;++i)
    {
        ASTnode* next=va_arg(valist,ASTnode*);
        node->next=next;
        node=next;
    }
    node->next=NULL;
    va_end(valist);
}
 
void outputAST(ASTnode* head,int tab)
{
    switch (head->type)
    {
        case NUM:
            printf("\033[1;35m%d\033[0m\n",head->num);
            break;
        case TEXT:
            if(head->child!=NULL)
                printf("\033[1;32m%s\033[0m\n",head->text);
            else
                printf("\033[1;34m%s\033[0m\n",head->text);
            break;
    }
    ASTnode* node=head->child;
    while(node!=NULL)
    {
        for(int i=0;i<tab;++i)
            printf("|");
        printf(">--");
        outputAST(node,tab+1);
        node=node->next;
    }
}
 
void freeAST(ASTnode *head)
{
    ASTnode *node=head->child;
    while (node!=NULL)
    {
        freeAST(node);
        node=node->next;
    }
    if(head->type==TEXT)
        free(head->text);
    free(head);
}
