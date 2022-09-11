#include "shell.h"
#include "parser.h"

static void execute_simple_command(char **args);
static void execute_sequence_command(char **args);
static char* replace_separator_with_space(char *command, char separator);

void execute_command(char *command) {

    cmd cmd_type = SIMPLE_CMD;
    char **parsed_command;

    if(check_if_sequence_command(command)) {
        cmd_type = SEQUENCE_CMD;
    }
    else if(check_if_pipeline_command(command)){
        cmd_type = PIPELINE_CMD;
    }
    else if(check_if_redirection_0_command(command)) {
        cmd_type = REDIRECTION_0_CMD;
    }   
    else if(check_if_redirection_1_command(command)) {
        cmd_type = REDIRECTION_1_CMD;
    } 

    if(cmd_type == SEQUENCE_CMD) {
        parsed_command = parse_text_by_separator(command, ';');
    }
    else if(cmd_type == PIPELINE_CMD) {
        parsed_command = parse_text_by_separator(command, '|');
    }
    else if(cmd_type == REDIRECTION_0_CMD) {
        parsed_command = parse_text_by_separator(command, '>');
    }
    else if(cmd_type == REDIRECTION_1_CMD) {
        parsed_command = parse_text_by_separator(command, '<');
    }
    else {
        parsed_command = parse_text_by_separator(command, ' ');
    }
    
    if(cmd_type == SEQUENCE_CMD) {
        execute_sequence_command(parsed_command);
    }
    else if(cmd_type == SIMPLE_CMD) {
        execute_simple_command(parsed_command);
    }

    free_allocated_memory_for_parsed_text(parsed_command);
}

static char* replace_separator_with_space(char *command, char separator) {

    int i;
    char *replaced_command = (char *)malloc(sizeof(char) * (strlen(command) + 1));
    if(replaced_command == NULL) {
        printf("Error allocating memory. Exiting with status 6 ... ");
        exit(6);
    }
    for(i=0; (command[i]!='\0' && command[i]!='\n'); i++) {
        if(command[i] == separator) {
            replaced_command[i] = ' ';
        }
        else {
            replaced_command[i] = command[i];
        }
    }
    replaced_command[i] = '\0';
    return replaced_command;
}

static void execute_sequence_command(char **args) {
    for(int i=0; args[i]!=NULL; i++) {
        execute_command(args[i]);
    }
}

static void execute_simple_command(char **args) {

    if(strcmp("cd", args[0]) == 0) {
        chdir(args[1]);
        return;
    }
    else if(strcmp("exit", args[0]) == 0) {
        exit(0);
    }

    pid_t pid = fork();

    if (pid == 0) {

        char cmd_path[CMD_SIZE + 4] = "/bin/";
        char *params[CMD_TOTAL_PARAMS + 1] = {0};
        
        strcat(cmd_path, args[0]);
        if((params[0] = (char *)malloc(sizeof(char) * strlen(cmd_path))) == NULL) {
            printf("memory allocation failed. Exiting with status 3 ...\n");
            exit(3);
        }
        strcpy(params[0], cmd_path);
        for(int i=1; ; i++) {
            params[i] = args[i];

            if(args[i] == NULL) 
                break;
        }
        execv(cmd_path, params);
    }

    wait(NULL);
    
}