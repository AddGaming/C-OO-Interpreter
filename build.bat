@echo off
cd src
echo --------- MSVC ------------ 
cl /Wall main.c dynamic_array.c
echo --------- GCC ------------- 
gcc main.c dynamic_array.c -Wall -Wextra -o main.exe
cd ..
copy src\main.exe main.exe
