#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 200
#define MAX_TOKEN 10

enum Token {
    TOKEN_BEGIN, IFTK, TOKEN_THEN, WHILETK, TOKEN_DO, TOKEN_END,
    IDENFR, INTCON, PLUS, MINU, MULT, DIV,
    ASSIGN, LSS, GRE, 
    TOKEN_SEMICOLON, TOKEN_LPAREN, TOKEN_RPAREN, TOKEN_EOF, TOKEN_ERROR,MAINTK,
    CONSTTK,ELSETK,GETINTTK,PRINTFTK,RETURNTK,VOIDTK,INTTK,BREAKTK,CONTINUETK,
    MOD,AND,OR,NOT,COMMA,LBRACK,RBRACK,LBRACE,RBRACE,EQL,NEQ
};

char input[MAX_INPUT];  // 存放输入字符串
int p = 0;              // input[]下标
int tokenLength = 0;    // 记号长度
char token[MAX_TOKEN];  // 存放构成单词符号的字符串
int num;                // 存放整形值
int line_count = 0;     // 存放当前行数
enum Token scanner() {
    char ch;
    int m = 0;

    // 清空token[]
    memset(token, 0, sizeof(token));

    // 跳过空白和注释
    while ((ch = input[p]) && (isspace(ch) || ch == '/' || ch == '*')) {
        if (ch == '/') {
            if (input[p + 1] == '/') {
                // 单行注释，跳过整行
                line_count++; // 递增行号计数
                while (input[p] && input[p] != '\n') {
                    p++;
                }
            } else if (input[p + 1] == '*') {
                // 多行注释，跳过直到遇到"*/"
                p += 2; // 跳过"/*"
                while (input[p] && !(input[p] == '*' && input[p + 1] == '/')) {
                    if (input[p] == '\n') {
                        line_count++; // 递增行号计数
                        //printf("\n%d\n",line_count);
                    }
                    p++;
                }
                p += 2; // 跳过"*/"
            } else {
                // 不是注释，返回'/'
                token[m++] = ch;
                return DIV;
            }
        } else {
            p++;
        }
    }
    //处理换行符号
    if (ch == '\n') {
        line_count++;
    }

    // 判断输入是否结束
    if (ch == '\0') {
        return TOKEN_EOF;
    }

    // 处理标识符和关键字
    if (isalpha(ch)) {
        while (isalnum(ch)) {
            token[m++] = ch;
            ch = input[++p];
        }
        token[m] = '\0';
        p--; // 回退一个字符
        // 检查是否为关键字
        if (strcmp(token, "main") == 0) return MAINTK;
        if (strcmp(token, "begin") == 0) return TOKEN_BEGIN;
        if (strcmp(token, "if") == 0) return IFTK;
        if (strcmp(token, "then") == 0) return TOKEN_THEN;
        if (strcmp(token, "while") == 0) return WHILETK;
        if (strcmp(token, "do") == 0) return TOKEN_DO;
        if (strcmp(token, "end") == 0) return TOKEN_END;
        if (strcmp(token, "const") == 0) return CONSTTK;
        if (strcmp(token, "int") == 0) return INTTK;
        if (strcmp(token, "break") == 0) return BREAKTK;
        if (strcmp(token, "continue") == 0) return CONTINUETK;
        if (strcmp(token, "else") == 0) return ELSETK;
        if (strcmp(token, "getint") == 0) return GETINTTK;
        if (strcmp(token, "printf") == 0) return PRINTFTK;
        if (strcmp(token, "return") == 0) return RETURNTK;
        if (strcmp(token, "void") == 0) return VOIDTK;
        return IDENFR;
    }

    // 处理数字
    if (isdigit(ch)) {
        num = 0;
        while (isdigit(ch)) {
            num = num * 10 + (ch - '0');
            token[m++] = ch;
            ch = input[++p];
        }
        token[m] = '\0';
        p--; // 回退一个字符
        return INTCON;
    }

    // 处理运算符和分隔符
    switch (ch) {
        case '+': token[m++] = ch; return PLUS;
        case '-': token[m++] = ch; return MINU;
        case '*': token[m++] = ch; return MULT;
        case '%': token[m++] = ch; return MOD;
        

        case '&': 
            token[m++] = ch;
            if (input[p + 1] == '&') {
                p++;
                token[m++] = input[p];
                return AND;
            }
        case '|': 
            token[m++] = ch;
            if (input[p + 1] == '|') {
                p++;
                token[m++] = input[p];
                return OR;
            }


        case '!': 
            token[m++] = ch;
            if (input[p + 1] == '=') {
                p++;
                token[m++] = input[p];
                return NEQ;
            }
            return NOT;
        case '=': 
            token[m++] = ch;
            if (input[p + 1] == '=') {
                p++;
                token[m++] = input[p];
                return EQL;
            }
            return ASSIGN;
        case '<':
            token[m++] = ch;
            if (input[p + 1] == '=') {
                p++;
                token[m++] = input[p];
                return LSS;
            }
            return LSS;
        case '>':
            token[m++] = ch;
            if (input[p + 1] == '=') {
                p++;
                token[m++] = input[p];
                return GRE;
            }
            return GRE;
        case ';': token[m++] = ch;return TOKEN_SEMICOLON;
        case ',': token[m++] = ch;return COMMA;
        case '(': token[m++] = ch;return TOKEN_LPAREN;
        case ')': token[m++] = ch;return TOKEN_RPAREN;
        case '[': token[m++] = ch;return LBRACK;
        case ']': token[m++] = ch;return RBRACK;
        case '{': token[m++] = ch;return LBRACE;
        case '}': token[m++] = ch;return RBRACE;
        case '\0':token[m++] = ch;return TOKEN_EOF;
        default: return TOKEN_ERROR;
    }
}
// 辅助函数：将枚举类型转换为字符串
const char *enumToString(enum Token token) {
    static const char *strings[] = {
        "TOKEN_BEGIN", "IFTK", "TOKEN_THEN", "WHILETK", "TOKEN_DO", "TOKEN_END",
        "IDENFR", "INTCON", "PLUS", "MINU", "MULT", "DIV",
        "ASSIGN", "LSS", "GRE", "TOKEN_NOTEQUAL",
        "TOKEN_SEMICOLON", "TOKEN_LPAREN", "TOKEN_RPAREN", "TOKEN_EOF", "TOKEN_ERROR","MAINTK",
        "CONSTTK","ELSETK","GETINTTK","PRINTFTK","RETURNTK","VOIDTK","INTTK","BREAKTK","CONTINUETK",
        "MOD","AND","OR","NOT","COMMA","LBRACK","RBRACK","LBRACE","RBRACE","EQL","NEQ"
    };
    return strings[token];
}
int main() {
    // 测试代码
    strcpy(input, "//this should be ignore\n/*this\n also\n should\n be\n ignore\n*/ aaa begin if then while do end 123 + - * / = <= >= <> ; ( ) @");
    enum Token tok;
    while ((tok = scanner()) != TOKEN_EOF) {
        printf("Token: %s, Value: %s, Line: %d\n", enumToString(tok), token,line_count);
        p++; // Move to the next character
    }
    return 0;
}