#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// size of the command
#define CMD_SIZE 256

// maximum path size
#define PATH_SIZE 128

// prints shell message
void print_shell_message(void);

// prints prompt
void print_prompt(void);

// runs shell
void run_shell(void);


#endif