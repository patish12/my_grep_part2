#ifndef MAIN_FULL_H
#define MAIN_FULL_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS

#define USAGE "Incorrect arguments passed to my_grep.\n\tUsage: my_grep [switches] pattern filename\n"

typedef struct _switches
{
    bool A_print_n_prev_lines;
    bool b_print_num_bytes;
    bool c_print_only_line_nums;
    bool i_case_insensitive;
    bool n_print_line_num;
    bool v_print_not_matching;
    bool x_print_exact_match;
    bool quoted_string;
    bool next_is_quoted_string;
    int A_num;
    bool next_is_prev_num_lines;
} switches;

typedef struct _indexes_pattern_and_filename
{
    /* data */
    int pattern_index_in_argc;
    int filename_index_in_argc;

}indexes_pattern_and_filename;
 
 #endif

