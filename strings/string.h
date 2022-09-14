#ifndef STRING_H
#define STRING_H

#include <stdio.h>
#include <stdlib.h>

void str_print(char *str);

size_t str_size(const char *str);

char* str_cat(char *dest, const char *source);
char* str_ncat(char *dest, const char *source, size_t n);



#endif