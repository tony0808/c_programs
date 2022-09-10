#include "shell.h"
#include "parser.h"

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
        execute_simple_commands(command);
    }
}

// exectutes simple commands
void execute_simple_commands(char *command) {
    
    pid_t pid = fork();

    if (pid == 0) {
        
        char cmd_path[CMD_SIZE + 4] = "/bin/";
        char *params[CMD_TOTAL_PARAMS+1] = {0};
        char **args = parse_simple_command(command); 

        strcat(cmd_path, args[0]);
        params[0] = (char *)malloc(sizeof(char) * strlen(cmd_path));
        strcpy(params[0], cmd_path);
 
        for(int i=1; ; i++) {
            params[i] = args[i];
            
            if(args[i] == NULL)
                break;
        }

        execv(cmd_path, params);
    }
    else {
        wait(NULL);
    }
}