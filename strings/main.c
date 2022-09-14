#include "string.h"
#include <string.h>

int main(int argc, char *argv[]) {

    char str[100] = {0};
    strcpy(str, "hello world");

    if(argc > 1) {
        strcpy(str, argv[1]);
    }
    
    char arr[100] = {0};



    str_ncat(arr, "tony_ivanov_csd4262", 123);


    str_print(arr);






    return 0;
}