#ifndef UTILS_H
#define UTILS_H

void reset_stream_change_variables(void);
void declare_new_output_stream(int read_end, int write_end);
void declare_new_input_stream(int read_end, int write_end);
void change_standard_stream(void);

#endif