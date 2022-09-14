#include "string.h"

void str_print(char *str) {
    printf("%s\n", str);
}

size_t str_size(const char *str) {
    for(size_t size=0; ; size++) {
        if(str[size] == '\0') 
            return size;
    }
}

char* str_cat(char *dest, const char *source) {
    return str_ncat(dest, source, str_size(source));
}

char* str_ncat(char *dest, const char *source, size_t n) {
    if((dest != NULL) && (n <= str_size(source))) {
        size_t dest_size = str_size(dest);

        for(size_t i=0; i<n; i++) {
            dest[i+dest_size] = source[i];
            if(i==n-1)
                dest[i+dest_size+1] = '\0';
        }
    }
    return dest;
}