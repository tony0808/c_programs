#ifndef PARSER_H
#define PARSER_H

#include <string.h>

typedef enum {
    SIMPLE_CMD,
    SEQUENCE_CMD,
    PIPELINE_CMD,
    REDIRECTION_0_CMD,
    REDIRECTION_1_CMD,
    REDIRECTION_2_CMD
} cmd;

// parses a simple command into the name of the command and it's arguments
char** parse_text_by_separator(char *command, char separator);

// returns true if the command is a sequence command type
bool check_if_sequence_command(char *command);

// returns true if the command is a pipeline command type
bool check_if_pipeline_command(char *command);

// returns true if the command is a redirection command type
bool check_if_redirection_0_command(char *command); 
bool check_if_redirection_1_command(char *command);
bool check_if_redirection_2_command(char *command); 

// frees allocated memory used for parsing the command
void free_allocated_memory_for_parsed_text(char **ptr);

#endif