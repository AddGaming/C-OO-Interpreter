/**
 * print in color
 */

#define print_redln(...) \
    printf ("\x1B[31m"); \
    printf (__VA_ARGS__); \
    printf ("\x1B[0m\n");

#define print_greenln(...) \
    printf ("\x1B[32m"); \
    printf (__VA_ARGS__); \
    printf ("\x1B[0m\n");

#define print_blackln(...) \
    printf ("\x1B[30m"); \
    printf (__VA_ARGS__); \
    printf ("\x1B[0m\n");

#define print_yellowln(...) \
    printf ("\x1B[33m"); \
    printf (__VA_ARGS__); \
    printf ("\x1B[0m\n");

#define print_blueln(...) \
    printf ("\x1B[34m"); \
    printf (__VA_ARGS__); \
    printf ("\x1B[0m\n");

#define print_magentyln(...) \
    printf ("\x1B[35m"); \
    printf (__VA_ARGS__); \
    printf ("\x1B[0m\n");

#define print_cyanln(...) \
    printf ("\x1B[36m"); \
    printf (__VA_ARGS__); \
    printf ("\x1Be[0m\n");

#define print_whiteln(...) \
    printf ("\x1B[0;37m"); \
    printf (__VA_ARGS__); \
    printf ("\x1Be[0m\n");

#define print_red(...) \
    printf ("\x1B[0;31m"); \
    printf (__VA_ARGS__); \
    printf ("\x1Be[0m");

#define print_green(...) \
    printf ("\x1B[0;32m"); \
    printf (__VA_ARGS__);  \
    printf ("\x1Be[0m");

#define print_black(...) \
    printf ("\x1B[0;30m"); \
    printf (__VA_ARGS__);  \
    printf ("\x1Be[0m");

#define print_yellow(...) \
    printf ("\x1B[0;33m"); \
    printf (__VA_ARGS__);  \
    printf ("\x1Be[0m");

#define print_blue(...) \
    printf ("\x1B[0;34m"); \
    printf (__VA_ARGS__);  \
    printf ("\x1Be[0m");

#define print_magenty(...) \
    printf ("\x1B[0;35m"); \
    printf (__VA_ARGS__);  \
    printf ("\x1Be[0m");

#define print_cyan(...) \
    printf ("\x1B[0;36m"); \
    printf (__VA_ARGS__);  \
    printf ("\x1Be[0m");

#define print_white(...) \
    printf ("\x1B[0;37m"); \
    printf (__VA_ARGS__);  \
    printf ("\x1Be[0m");


