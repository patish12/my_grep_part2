#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS

#define STR_MAX_SZ 256
#define TRUE 1
#define FALSE (!TRUE)
#define USAGE "Incorrect arguments passed to my_grep.\n\tUsage: my_grep [switches] pattern filename\n"

typedef struct _switches
{
    int print_n_prev_lines;
    int print_num_bytes;
    int print_only_line_nums;
    int case_insensitive;
    int print_line_num;
    int print_not_matching;
    int print_exact_match;
    int quoted_string;
    int next_is_quoted_string;
    int next_is_prev_num_lines;
} switches;

void print_switches(switches);
int parse_arguments(int, char **, char*, char*, switches*);
int parse_switch(char*, switches*);