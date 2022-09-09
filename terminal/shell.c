#include "shell.h"



void print_shell_message(void) {

    size_t width = 25;
    char *msg = "Linux Shell";
    size_t pad = (width - strlen(msg) - 2) / 2;

    for(int i=0; i<width; i++) 
        printf("*");
    printf("\n*");

    for(int i=0; i<pad; i++) 
        printf(" ");
    printf("%s", msg);

    for(int i=0; i<pad; i++) 
        printf(" ");
    printf("*\n");

    for(int i=0; i<width; i++) 
        printf("*");
    printf("\n");
}