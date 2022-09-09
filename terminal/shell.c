#include "shell.h"

// prints shell message
void print_shell_message(void) 
{

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

// prints prompt
void print_prompt(void)
{
    static char *login_name = NULL;
    static char curr_working_dir[PATH_SIZE];

    if (login_name == NULL && strlen(curr_working_dir) == 0) {
        if ((login_name = getlogin()) == NULL) {
            perror("getlogin");
        }
        
        if (getcwd(curr_working_dir, PATH_SIZE) == NULL) {
            perror("getcwd");
        }
    }

    printf("%s@csd345sh/%s$ ", login_name, curr_working_dir);
}

// runs shell
void run_shell(void) {

    char command[CMD_SIZE] = {0};

    print_shell_message();
    while(1) {
        print_prompt();
        fgets(command, CMD_SIZE, stdin);    
    }
}