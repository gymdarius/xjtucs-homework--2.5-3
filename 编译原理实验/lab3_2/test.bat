@echo off
set str=%1
@echo on
flex %str%.l
bison --yacc -dv %str%.y
gcc -o %str% y.tab.c lex.yy.c
test.exe <1.c
 