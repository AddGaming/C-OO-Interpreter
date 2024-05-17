@echo off
cd src
echo --------- MSVC ------------ 
cl /Wall main.c rstd\\dynamic_array.c lexer.c
cd ..
echo --------------------------- 
copy src\main.exe main.exe
del src\main.exe
