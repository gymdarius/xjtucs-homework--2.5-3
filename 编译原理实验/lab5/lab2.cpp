
#include <stdio.h>
#include <ctype.h>
#include <string.h>

FILE *fp;
char cbuffer;
char Isalpha(char buffer);     // 判断是否是关键字
char Isnumber(char buffer);    // 判断是否是数字
char Isanotation(char buffer); // 判断是否是注释
char ISother(char buffer);     // 判断是否是其他符号
void scanner();                // 词法分析

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("error");
        return 0;
    }
    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        printf("文件打开失败\n");
        return 0;
    }
    scanner();
    fclose(fp);
    return 0;
}
void scanner()
{
    cbuffer = fgetc(fp);
    while (cbuffer != EOF)
    {
        if (cbuffer == ' ' || cbuffer == '\n' || cbuffer == '\t')
            cbuffer = fgetc(fp);
        else if (isalpha(cbuffer) || cbuffer == '_')
            cbuffer = Isalpha(cbuffer);
        else if (isdigit(cbuffer)) // 识别正整数
            cbuffer = Isnumber(cbuffer);
        else if (cbuffer == '/')
            cbuffer = Isanotation(cbuffer);
        else // 处理分隔符和其他符号
            cbuffer = ISother(cbuffer);
    }
}
// 判断关键字，是返回1和i（i是key位置，从1开始），否则标识符则返回2
char Isalpha(char buffer)
{
    int atype; /*保留字数组中的位置*/
    int i = 0;
    char alphatp[100];
    while (isalpha(buffer) || isdigit(buffer) || buffer == '_') // 如果buffer是字母数字or下划线，则放入 alphatp字符数组
    {
        alphatp[i] = buffer;
        buffer = fgetc(fp); // 从指定的文件流中读取一个字符
        i++;
    }
    alphatp[i] = '\0'; // alphatp字符数组结尾加空字符，确保单词在被正确识别。
    if (strcmp(alphatp, "main") == 0)
    {
        {
            printf("MAINTK %s\n", alphatp);
        }
        return buffer;
    }
    else if (strcmp(alphatp, "const") == 0)
    {
        printf("CONSTTK %s\n", alphatp);
        return buffer;
    }
    else if (strcmp(alphatp, "break") == 0)
    {
        printf("BREAKTK %s\n", alphatp);
        return buffer;
    }
    else if (strcmp(alphatp, "continue") == 0)
    {
        printf("CONTINUETK %s\n", alphatp);
        return buffer;
    }
    else if (strcmp(alphatp, "return") == 0)
    {
        printf("RETURNTK %s\n", alphatp);
        return buffer;
    }
    else if (strcmp(alphatp, "if") == 0)
    {
        printf("IFTK %s\n", alphatp);
        return buffer;
    }
    else if (strcmp(alphatp, "else") == 0)
    {
        printf("ELSETK %s\n", alphatp);
        return buffer;
    }
    else if (strcmp(alphatp, "while") == 0)
    {
        printf("WHILETK %s\n", alphatp);
        return buffer;
    }
    else if (strcmp(alphatp, "do") == 0)
    {
        printf("DOTK %s\n", alphatp);
        return buffer;
    }
    else if (strcmp(alphatp, "for") == 0)
    {
        printf("FORTK %s\n", alphatp);
        return buffer;
    }
    else if (strcmp(alphatp, "int") == 0)
    {
        printf("INTTK %s\n", alphatp);
        return buffer;
    }
    else if (strcmp(alphatp, "float") == 0)
    {
        printf("FLOATTK %s\n", alphatp);
        return buffer;
    }
    else if (strcmp(alphatp, "double") == 0)
    {
        printf("DOUBLETK %s\n", alphatp);
        return buffer;
    }
    else if (strcmp(alphatp, "char") == 0)
    {
        printf("CHARTK %s\n", alphatp);
        return buffer;
    }
    else if (strcmp(alphatp, "void") == 0)
    {
        printf("VOIDTK %s\n", alphatp);
        return buffer;
    }
    else if (strcmp(alphatp, "long") == 0)
    {
        printf("LONGTK %s\n", alphatp);
        return buffer;
    }
    else if (strcmp(alphatp, "short") == 0)
    {
        printf("SHORTTK %s\n", alphatp);
        return buffer;
    }
    else if (strcmp(alphatp, "switch") == 0)
    {
        printf("SWITCHTK %s\n", alphatp);
        return buffer;
    }
    else if (strcmp(alphatp, "then") == 0)
    {
        printf("THENTK then\n");
        return buffer;
    }
    printf("IDENFR %s\n", alphatp);
    return buffer; // 返回buffer值
}

// 输出数字类，3
char Isnumber(char buffer)
{
    int i = -1, flag = 0;
    char digittp[20];
    while (isdigit(buffer))
    {
        digittp[++i] = buffer;
        buffer = fgetc(fp);
    }
    digittp[++i] = '\0';
    printf("INTCON %s\n", digittp);
    return buffer;
}
char Isanotation(char buffer)
{
    buffer = fgetc(fp);
    if (buffer == '/') // 单行注释
    {
        while (buffer != '\n')
        {
            buffer = fgetc(fp);
        }
        return buffer;
    }
    else if (buffer == '*') // 多行注释
    {
        buffer = fgetc(fp);
        while (1)
        {
            if (buffer == '*')
            {
                buffer = fgetc(fp);
                if (buffer == '/') // 注释结束
                {
                    return fgetc(fp);
                }
            }
            else
            {
                buffer = fgetc(fp);
            }
        }
    }
    else
    {
        printf("DIVTK /\n");
        return buffer;
    }
}
char ISother(char buffer)
{
    if (buffer == '!')
    {
        buffer = fgetc(fp);
        if (buffer == '=')
        {
            printf("NEQTK !=\n");
            return fgetc(fp);
        }
        else
        {
            printf("NOTTK !\n");
            return buffer;
        }
    }
    else if (buffer == '+')
    {
        buffer = fgetc(fp);
        if (buffer == '=')
        {
            printf("PLUSTK +=\n");
            return fgetc(fp);
        }
        else if (buffer == '+')
        {
            printf("PLUSTK ++\n");
            return fgetc(fp);
        }
        else
        {
            printf("PLUSTK +\n");
            return buffer;
        }
    }
    else if (buffer == '=')
    {
        buffer = fgetc(fp);
        if (buffer == '=')
        {
            printf("EQUTK ==\n");
            return fgetc(fp);
        }
        else
        {
            printf("ASSIGNTK =\n");
            return buffer;
        }
    }
    else if (buffer == '-')
    {
        buffer = fgetc(fp);
        if (buffer == '=')
        {
            printf("MINUTETK -=\n");
            return fgetc(fp);
        }
        else if (buffer == '-')
        {
            printf("MINUTETK --\n");
            return fgetc(fp);
        }
        else
        {
            printf("MINUTETK -\n");
            return buffer;
        }
    }
    else if (buffer == '*')
    {
        buffer = fgetc(fp);
        if (buffer == '=')
        {
            printf("MULTITK *=\n");
            return fgetc(fp);
        }
        else
        {
            printf("MULTITK *\n");
            return buffer;
        }
    }
    else if (buffer == '<')
    {
        buffer = fgetc(fp);
        if (buffer == '=')
        {
            printf("LEQTK <=\n");
            return fgetc(fp);
        }
        else
        {
            printf("LSS %c\n", buffer);
            return buffer;
        }
    }
    else if (buffer == '>')
    {
        buffer = fgetc(fp);
        if (buffer == '=')
        {
            printf("GEQTK >=\n");
            return fgetc(fp);
        }
        else
        {
            printf("GRE %c\n", buffer);
            return buffer;
        }
    }
    else if (buffer == '&')
    {
        buffer = fgetc(fp);
        if (buffer == '&')
        {
            printf("ANDTK &&\n");
            return fgetc(fp);
        }
        else
        {
            printf("ANDTK &\n");
            return buffer;
        }
    }
    else if (buffer == '|')
    {
        buffer = fgetc(fp);
        if (buffer == '|')
        {
            printf("ORTK ||\n");
            return fgetc(fp);
        }
        else
        {
            printf("ORTK |\n");
            return buffer;
        }
    }
    else if (buffer == '%')
    {
        printf("MODTK %\n");
        return fgetc(fp);
    }
    else if (buffer == '~')
    {
        printf("REMTK ~\n");
        return fgetc(fp);
    }
    else if (buffer == '^')
    {
        printf("XORTK ^\n");
        return fgetc(fp);
    }
    else if (buffer == '(')
    {
        printf("LPARTK (\n");
        return fgetc(fp);
    }
    else if (buffer == ')')
    {
        printf("RPARTK )\n");
        return fgetc(fp);
    }
    else if (buffer == '[')
    {
        printf("LBRATK [\n");
        return fgetc(fp);
    }
    else if (buffer == ']')
    {
        printf("RBRATK ]\n");
        return fgetc(fp);
    }
    else if (buffer == '{')
    {
        printf("LBRATK {\n");
        return fgetc(fp);
    }
    else if (buffer == '}')
    {
        printf("RBRATK }\n");
        return fgetc(fp);
    }
    else if (buffer == ',')
    {
        printf("COMMATK ,\n");
        return fgetc(fp);
    }
    else if (buffer == ';')
    {
        printf("SEMICOLONTK ;\n");
        return fgetc(fp);
    }
    else if (buffer == '.')
    {
        printf("PERIODTK .\n");
        return fgetc(fp);
    }
    else if (buffer == '"')
    {
        printf("QUOTETK \"\n");
        return fgetc(fp);
    }
    else if (buffer == '#')
    {
        printf("POUNDTK #\n");
        return fgetc(fp);
    }
    else
    {
        printf("error");
        return fgetc(fp);
    }
}