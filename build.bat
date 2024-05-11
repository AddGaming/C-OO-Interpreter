@echo off
cd src
echo --------- MSVC ------------ 
cl /Wall main.c dynamic_array.c lexer.c
echo --------- GCC ------------- 
gcc main.c dynamic_array.c lexer.c -Wall -Wextra -o main.exe
cd ..
echo --------------------------- 
copy src\main.exe main.exe
del src\main.exe
