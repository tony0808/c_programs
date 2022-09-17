#ifndef UTILS_H
#define UTILS_H

extern int stream_to_chage;
extern int change_stream_flag;
extern int stream_operation_changed;
extern int stream_operation_unchanged;

void reset_stream_change_variables(void);
void declare_new_output_stream(int read_end, int write_end);
void declare_new_input_stream(int read_end, int write_end);

void change_standard_stream(void);

#endif