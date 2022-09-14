#include "shell.h"
#include "parser.h"

static void execute_simple_command(char **args);
static void execute_sequence_command(char **args);
static void execute_pipeline_command(char **args);
static void execute_single_pipeline_command(char **args);
static void execute_multiple_pipeline_command(char **args);
static void set_command_type(char *command, cmd *cmd_type);
static void parse_command(char *command, cmd cmd_type, char ***parse_command);
static void run_command(char **command, cmd cmd_type);


void execute_command(char *command) {

    cmd cmd_type = SIMPLE_CMD;
    char **parsed_command = NULL;

    set_command_type(command, &cmd_type);
    parse_command(command, cmd_type, &parsed_command);
    run_command(parsed_command, cmd_type);
    free_allocated_memory_for_parsed_text(parsed_command);
}

static void set_command_type(char *command, cmd *cmd_type) {
    if(check_if_sequence_command(command)) {
        *cmd_type = SEQUENCE_CMD;
    }
    else if(check_if_pipeline_command(command)){
        *cmd_type = PIPELINE_CMD;
    }
    else if(check_if_redirection_0_command(command)) {
        *cmd_type = REDIRECTION_0_CMD;
    }   
    else if(check_if_redirection_1_command(command)) {
        *cmd_type = REDIRECTION_1_CMD;
    } 
}

static void parse_command(char *command, cmd cmd_type, char ***parsed_command) {
    
    if(cmd_type == SEQUENCE_CMD) {
        *parsed_command = parse_text_by_separator(command, ';');
    }
    else if(cmd_type == PIPELINE_CMD) {
        *parsed_command = parse_text_by_separator(command, '|');
    }
    else if(cmd_type == REDIRECTION_0_CMD) {
        *parsed_command = parse_text_by_separator(command, '>');
    }
    else if(cmd_type == REDIRECTION_1_CMD) {
        *parsed_command = parse_text_by_separator(command, '<');
    }
    else {
        *parsed_command = parse_text_by_separator(command, ' ');
    }
}

static void run_command(char **command, cmd cmd_type) {
    if(cmd_type == SEQUENCE_CMD) {
        execute_sequence_command(command);
    }
    else if(cmd_type == SIMPLE_CMD) {
        execute_simple_command(command);
    }
    else if(cmd_type == PIPELINE_CMD) {
        execute_pipeline_command(command);
    }
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
        printf("Exiting shell ...\n");
        exit(0);
    }

    pid_t pid = fork();

    if (pid == 0) {
        char cmd_path[CMD_SIZE + 10] = "/usr/bin/";
        char main_command[CMD_SIZE] = {0};

        // exec first try
        strcpy(main_command, args[0]);
        strcat(cmd_path, args[0]);
        args[0] = cmd_path;
        execv(cmd_path, args);

        // exec second try
        strcpy(cmd_path, "/bin/");
        strcat(cmd_path, main_command);
        args[0] = cmd_path;
        execv(cmd_path, args);
        perror("execv");
        exit(1);
    }
    else if (pid < 0) {
        perror("fork");
        exit(1);
    }

    wait(NULL);
    
}

static void execute_pipeline_command(char **args) {
    int pipeline_order = 0;

    for(pipeline_order=0; args[pipeline_order]!=NULL; pipeline_order++);

    if (pipeline_order == 2) {
        execute_single_pipeline_command(args);
    }
    else if (pipeline_order > 2) {
        execute_multiple_pipeline_command(args);
    }   
    else {
        printf("Should not be here ... Exiting with status 100.\n");
        exit(10);
    }
}

static void execute_single_pipeline_command(char **args) {
    
    int fd[2];

    if(pipe(fd) < 0) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();
    
    if(pid == 0) {
        printf("here child\n");
        dup2(fd[WRITE_END], STDOUT_FILENO);
        close(fd[WRITE_END]);
        close(fd[READ_END]);
        printf("command: %s\n", args[0]);
        exit(0);
    }
    else if(pid < 0){
        perror("fork");
        exit(1);
    }

    wait(NULL);

    
    
}

static void execute_multiple_pipeline_command(char **args) {
    printf("executing multiple pipeline command\n");
}