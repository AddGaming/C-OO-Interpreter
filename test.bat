@echo off
cd src
echo --------- GCC ------------- 
gcc tests.c testing.c dynamic_array.c -Wall -Wextra -o test.exe
echo --------------------- 
test.exe 2> nul :: redirecting stderr to null, since errors are exprected
del test.exe
cd ..

