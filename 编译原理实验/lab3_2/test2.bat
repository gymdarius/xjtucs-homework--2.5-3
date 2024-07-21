@echo off
set str=%1
@echo on
bison --yacc -dv %str%.y
flex %str%.l
gcc -o %str% y.tab.c lex.yy.c
test.exe <2.c
 