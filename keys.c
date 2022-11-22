#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "keys.h"

char* i_key_get_lowcase_line(char* line, int line_len){
	int i = 0;
	for (i = 0; i < line_len; i++) {
		line[i] = tolower(line[i]);
	}
	line[line_len-1] = '\0';
	return line;
}

char* i_key_get_lowcase_pattern(char* pattern){
    int pattern_len=strlen(pattern);
	for (int i = 0; i < pattern_len; i++) {
		pattern[i] = tolower(pattern[i]);
	}
	pattern[pattern_len-1] = '\0';
	return pattern;
}

bool x_key_only_and_exact_pattern(char* line, char* pattern){
	if (!strcmp(line,pattern)){
		return true;
	}
	else{
		return false;
	}
}

bool v_key_pattern_not_found(char* line, char* pattern){
	if (strstr(line,pattern)==NULL){
		return true;
	}
	else{
		return false;
	}
}

int b_key_count_bytes(int total_read_chars, int read_chars){
	total_read_chars+=read_chars;
	return total_read_chars;
}

int n_key_count_lines(int line_counter){
	line_counter++;
	return line_counter;
}

int c_key_count_line_to_print(int c_key_need_to_print){
	c_key_need_to_print++;
	return c_key_need_to_print;
}

int A_key_add_num_lines(bool print_line, int A_NUM, int A_key_count_remaining){
	if (print_line){
		return A_NUM;
	}
	else{
		A_key_count_remaining-=1;
		return A_key_count_remaining;
	}
}

bool check_if_print(int A_key_count_remaining){
	if (A_key_count_remaining>0){
		return true;
	}
	return false;
}