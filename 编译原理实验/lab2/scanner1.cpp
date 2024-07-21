// 添加头文件
#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>

// 变量声明
FILE *fp;
char ch; // 记录当前字符
int line = 0;
char category[10];
char value[10];

const char *key[13] = {"main", "int", "if", "else", "while", "break", "continue", "float", "void", "const", "printf", "getint", "return"}; // 1.加入其他关键字
const char *key_name[13] = {"MAINTK", "INTCON", "IFTK", "ELSETK", "WHILETK", "BREAKTK", "CONTINUETK", "FLOATCON", "VOIDTK", "CONSTTK", "PRINTFTK", "GETINTTK", "RETURNTK"};
const char *other_table[11] = {",", ";", "(", ")", "[", "]", "{", "}", "!", "||", "&&"}; // 其他字符
const char *other_name[11] = {"COMMA", "SEMICN", "LPARENT", "RPARENT", "LBRACK", "RBRACK", "LBRACE", "RBRACE", "NOT", "OR", "AND"};
const char *maths_calcu_table[4] = {"+", "-", "*", "/"}; // 3.加入运算符
const char *maths_calcu_name[4] = {"PLUS", "MINU", "MULT", "DIV"};
const char *relation_calcu_table[7] = {"<", "<=", ">", ">=", "=", "!=", "=="}; // 4.加入关系符
const char *relation_calcu_name[7] = {"LSS", "LEQ", "GRE", "GEQ", "ASSIGN", "NEQ", "EQL"};

// 函数声明
char alphaprocess(char buffer);
int search(char searchchar[]);
char numberprocess(char buffer);
char otherprocess(char buffer);
char relation_calcuProcess(char buffer);
char maths_calcuProcess(char buffer);
char stringprocess(char buffer);

bool isrelation_calcu(char buffer);
bool ismaths_calcu(char buffer);
bool isnumber(char buffer);
bool isalpha(char buffer);
bool isstring(char buffer);
bool isother(char buffer);

void output();
void ERROR(char *s);

// void 改int
int main()
{
    if ((fp = fopen("test.txt", "r")) == NULL)
        printf("error");
    else
    {
        ch = fgetc(fp); // 从指定的文件流中读取一个字符
        while (ch != EOF)
        {
            if (ch == ' ' || ch == '\n' || ch == '\t')
            { // 5.忽略空格、制表符(新加)和换行符
                if (ch == '\n')
                    line++;
                ch = fgetc(fp);
            }
            else if (isstring(ch)) // 处理字符串
                ch = stringprocess(ch);
            else if (isalpha(ch)) // 处理标识符和关键字
                ch = alphaprocess(ch);
            else if (isnumber(ch)) // 处理常数
                ch = numberprocess(ch);
            else if (isother(ch))
                ch = otherprocess(ch);
            else if (isrelation_calcu(ch)) // 处理关系运算符
                ch = relation_calcuProcess(ch);
            else if (ismaths_calcu(ch)) // 处理算术运算符
                ch = maths_calcuProcess(ch);
            else
            {
                ERROR(&ch);
                ch = fgetc(fp);
            }
        }
    }
    fclose(fp); //
    return 0;
}

void ERROR(char *s)
{
    printf("ERROR '%s' in line %d\n", s, line);
}

void output()
{
    printf("(%s,%s)\n", category, value);
}

bool isstring(char buffer)
{
    if (buffer == 34)
        return true;
    return false;
}

char stringprocess(char buffer)
{
    int i = 0;
    value[i] = buffer;
    buffer = fgetc(fp);
    i++;
    while (!isstring(buffer))
    {
        value[i] = buffer;
        buffer = fgetc(fp);
        i++;
    }
    value[i] = buffer;
    buffer = fgetc(fp);
    i++;
    value[i] = '\0';
    strcpy(category, "STRCON");
    output();
    return buffer;
}

bool isalpha(char buffer)
{
    if ((buffer >= 'a' && buffer <= 'z') || (buffer >= 'A' && buffer <= 'Z') || buffer == '_')
        return true;
    return false;
}

// 处理自定义变量和关键字
char alphaprocess(char buffer)
{
    int atype; // 保留字数组中的位置
    int i = 0;
    while (isalpha(buffer) || isnumber(buffer))
    {
        value[i] = buffer;
        buffer = fgetc(fp);
        i++;
    }
    value[i] = '\0';
    atype = search(value);
    if (atype != 0) // 关键字
    {
        strcpy(category, key_name[atype]);
    }
    else // 变量
    {
        strcpy(category, "IDENFR");
    }
    output();
    return buffer; // 返回buffer值
}

int search(char searchchar[])
{
    int i;
    int p;
    for (i = 0; i < 13; i++)
    {
        if (strcmp(key[i], searchchar) == 0)
        {
            p = i;
            break;
        }
        else
            p = 0;
    }
    return p;
}

bool isnumber(char buffer)
{
    if (buffer >= '0' && buffer <= '9')
        return true;
    return false;
}

// 识别正整数小数，实数
char numberprocess(char buffer)
{
    strcpy(category, "NUM");
    int i = 0, flag = 0;
    while (isnumber(buffer) || buffer == '.' || buffer == 'e' || buffer == 'E' || buffer == '+' || buffer == '-')
    {
        if (buffer == 'e' || buffer == 'E') // 科学计数法
        {
            flag = 1;
            value[i] = buffer;
        }
        else if (buffer == '+' || buffer == '-')
        {
            if (flag == 1)
            {
                value[i] = buffer;
            }
            else
                break;
        }
        else
        {
            value[i] = buffer;
        }
        buffer = fgetc(fp);
        i++;
    }
    value[i] = '\0';
    output();
    return buffer;
}

bool isother(char buffer)
{
    if (buffer == '&' || buffer == '|' || buffer == ';' || buffer == ',' || buffer == '(' || buffer == ')' || buffer == '{' || buffer == '}' || buffer == '[' || buffer == ']')
        return true;
    return false;
}

// 输出标识符
char otherprocess(char buffer)
{
    int i = 0;
    while (isother(buffer))
    {
        if (buffer == '(' || buffer == ')' || buffer == '{' || buffer == '}' || buffer == '[' || buffer == ']')
        {
            value[i] = buffer;
            buffer = fgetc(fp);
            i++;
            break;
        }
        value[i] = buffer;
        buffer = fgetc(fp);
        i++;
    }
    value[i] = '\0';

    for (i = 0; i < 11; i++)
    {
        if (strcmp(value, other_table[i]) == 0)
        {
            strcpy(category, other_name[i]);
            output();
            return buffer;
        }
    }
    ERROR(value);
    return buffer;
}

bool isrelation_calcu(char buffer) // 关系运算符
{
    if (buffer == '>' || buffer == '<' || buffer == '=' || buffer == '!')
        return true;
    return false;
}

char relation_calcuProcess(char buffer)
{
    int i = 0;
    int flag = 0;
    while ((isrelation_calcu(buffer)))
    {
        // 假如后面都是关系运算符，则一直加入，直到后面不是关系运算符为止
        value[i] = buffer;
        i++;
        buffer = fgetc(fp);
    }
    value[i] = '\0';

    if (value[0] == '!' && value[1] == '\0')
    { // 正确识别“！”与“！=”
        strcpy(category, "NOT");
        output();
        return buffer;
    }

    // 检查该操作符是否正确
    for (i = 0; i < 7; i++)
    {
        if (strcmp(value, relation_calcu_table[i]) == 0)
        {
            strcpy(category, relation_calcu_name[i]);
            output();
            return buffer;
        }
    }
    ERROR(value);
    return buffer;
}

bool ismaths_calcu(char buffer)
{
    if (buffer == '+' || buffer == '-' || buffer == '*' || buffer == '/')
        return true;
    return false;
}

char maths_calcuProcess(char buffer)
{
    int i = 0;
    while ((ismaths_calcu(buffer)))
    {
        // 假如后面都是算术运算符，则一直加入，直到后面不是算术运算符为止
        value[i] = buffer;
        i++;
        buffer = fgetc(fp);
    }
    value[i] = '\0';

    // 检查是否是注释
    bool flag1 = false; // 注释“//”
    bool flag2 = false; // 注释“/**/”

    if (value[0] == '/' && value[1] == '/')
        flag1 = true;

    if (value[0] == '/' && value[1] == '*')
        flag2 = true;

    if (flag1)
    {
        while (buffer != '\n')
        {
            buffer = fgetc(fp);
        }
        printf("(注释，_) \n");
        return buffer;
    }

    if (flag2)
    {
        int flag3 = 0;
        while (buffer != '/' && flag3 == 0)
        {
            if (buffer == '\n')
                line++;
            if (buffer == '*')
                flag3 = 1;
            else
                flag3 = 0;
            buffer = fgetc(fp);
        }
        buffer = fgetc(fp);
        printf("(注释，_) \n");
        return buffer;
    }

    // 检查该操作符是否在预设的符号之中
    for (i = 0; i < 4; i++)
    {
        if (strcmp(value, maths_calcu_table[i]) == 0)
        {
            strcpy(category, maths_calcu_name[i]);
            output();
            return buffer;
        }
    }
    ERROR(value);
    return buffer;
}
