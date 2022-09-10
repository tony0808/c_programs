#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define false 0
#define true 1
#define bool int

// size of the command
#define CMD_SIZE 256

// size of command parameter
#define CMD_PARAM_SIZE 10

// total number of parameters permitted in a command
#define CMD_TOTAL_PARAMS 20

// maximum path size
#define PATH_SIZE 128

// prints shell message
void print_shell_message(void);

// prints prompt
void print_prompt(void);

// runs shell
void run_shell(void);

// exectutes simple commands
void execute_simple_commands(char *command);

#endif