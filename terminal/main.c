#include "shell.h"
#include "parser.h"


int main(int argc, char *argv[]) {

    if (argc > 1) {
        char *command = " la ls lo po ";

        char **args = parse_simple_command(command);

        char *arg[20] = {0};

        for(int i=0; args[i]!=NULL; i++) {
            arg[i] = args[i];
        }    

        for(int i=0; arg[i]!=NULL; i++) {
            printf("arguent: %s\n", arg[i]);
        }
    }
    else {
        run_shell();
    }

    return 0;
}