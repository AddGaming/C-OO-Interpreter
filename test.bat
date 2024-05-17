@echo off
cd src
echo --------- MSVC ------------- 
cl /Wall tests.c rstd\\testing.c rstd\\dynamic_array.c lexer.c
echo --------------------- 
tests.exe 2> nul :: redirecting stderr to null, since errors are exprected
del tests.exe
cd ..

