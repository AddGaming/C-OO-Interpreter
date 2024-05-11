# Readme

Little interpreter for a little OO language written as a C practice execise.

## Building

```
echo --------- MSVC ------------ 
cl /Wall /O1 main.c
echo --------- GCC ------------- 
gcc main.c -Wall -Wextra -o main.exe
```

## Testing

```
echo --------- GCC ------------- 
gcc tests.c testing.c dynamic_array.c -Wall -Wextra -o test.exe
echo --------------------- 
test.exe 2> nul :: redirecting stderr to null, since errors are exprected
del test.exe
```
