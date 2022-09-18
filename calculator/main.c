#include "calc.h"




int main(int argc, char *argv[]) {

    if(argc < 2) {
        printf("Seconds argument is the expression to be computed.\n");
        exit(1);
    }

    printf("expression: %s\n", argv[1]);

    return 0;
}