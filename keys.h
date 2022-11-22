#ifndef KEYS_H
#define KEYS_H
#include <stdbool.h>
char* i_key_get_lowcase_line(char* line, int line_len);
char* i_key_get_lowcase_pattern(char* pattern);
bool v_key_pattern_not_found(char* line, char* pattern);
bool x_key_only_and_exact_pattern(char* line, char* pattern);
int b_key_count_bytes(int total_read_chars, int read_chars);
int n_key_count_lines(int line_counter);
int c_key_count_line_to_print(int c_key_need_to_print);
int A_key_add_num_lines(bool print_line, int A_NUM, int A_key_count_remaining);
bool check_if_print(int A_key_count_remaining);
#endif