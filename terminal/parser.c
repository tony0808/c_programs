#include "shell.h"
#include "parser.h"

static bool count_words_in_command(char *command);
static bool char_reader(char c);

// parses a simple command into the name of the command and it's arguments
char** parse_simple_command(char *command) {

    char current_word[CMD_PARAM_SIZE];
    bool new_word_is_being_read = false;
    int word_index = 0;
    int array_index = 0;
    int total_words = count_words_in_command(command);
    char **args = (char **)malloc(sizeof(char *) * (total_words + 1));
    
    for (int i=0; (command[i]!='\0' && command[i]!='\n'); i++) {

        // case where the current character is not space
        if (char_reader(command[i])) {
        
            // set flag that indicates that a word is being read
            if (!new_word_is_being_read) 
                new_word_is_being_read = true;
            
            // fill the buffer with letters from the word being currently read
            current_word[word_index++] = command[i];
        }
        // case where a new word is being 
        else if (new_word_is_being_read) {

            current_word[word_index] = '\0';
            args[array_index] = (char *)malloc(sizeof(char) * (strlen(current_word) + 1));
            strcpy(args[array_index++], current_word);
            word_index = 0;
            new_word_is_being_read = false;
        }
    }
    
    // case where the command ended with '\n' or '\0'
    if (new_word_is_being_read) {
        current_word[word_index] = '\0';
        args[array_index] = (char *)malloc(sizeof(char) * (strlen(current_word) + 1));
        strcpy(args[array_index++], current_word);
    }
    args[array_index] = NULL;
    return args;
}

// returns the total number of paramers in the command plus one (for the command itself)
static bool count_words_in_command(char *command) {

    int total_words = 0;
    bool reading_word = false;

    for(int i=0; (command[i]!='\0' && command[i]!='\n'); i++) {

        if(char_reader(command[i])) {
            if (!reading_word) {
                reading_word = true;
                total_words++;
            }
        }
        else {
            reading_word = false;
        }
    }   

    return total_words;
}

// returns true if the character is not a space (' '), otherwise it returns false 
static bool char_reader(char c) {
    return (c == ' ') ? false : true;
}

