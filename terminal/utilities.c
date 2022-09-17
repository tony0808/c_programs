#include "utilities.h"
#include "shell.h"

int stream_to_chage = -1;
int change_stream_flag = 0;
int stream_operation_changed = -1;
int stream_operation_unchanged = -1;

void reset_stream_change_variables(void) {
    stream_to_chage = -1;
    stream_operation_changed = -1;
    stream_operation_unchanged = -1;
}

void declare_new_output_stream(int read_end, int write_end) {
    stream_to_chage = STDOUT_FILENO;
    stream_operation_changed = write_end;
    stream_operation_unchanged = read_end;
}

void declare_new_input_stream(int read_end, int write_end) {
    stream_to_chage = STDIN_FILENO;
    stream_operation_changed = read_end;
    stream_operation_unchanged = write_end;
}

void change_standard_stream(void) {
    if(stream_to_chage >= 0) {
        dup2(stream_operation_changed, stream_to_chage);
        close(stream_operation_changed);
        close(stream_operation_unchanged);
    }
}