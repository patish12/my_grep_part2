#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "keys.h"


bool print_output(char* line, bool print_line,switches* sws,int total_read_chars,int line_counter,int c_key_need_to_print,bool A_print_line,bool print_sequencly){
	char a;
	bool need_to_print=A_print_line || print_line;
	if (line_counter==1){
			print_sequencly=need_to_print;
	}
	if (sws->A_print_n_prev_lines){
		//printf("%d, %d\n",line_counter,last_printed);
		if (need_to_print==true && print_sequencly==false){
			printf("--\n");
		}
	}
	if (A_print_line){
		a='-';
	}
	if (print_line){
		a=':';
	}
	if (need_to_print){
		if (sws->n_print_line_num){
			printf("%d%c",line_counter,a);
		}
		if (sws->b_print_num_bytes){
			printf("%d%c",total_read_chars,a);
		}
			printf("%s\n",line);
	}

	return need_to_print;
}

void print_c_key_output(int c_key_need_to_print){
	printf("%d\n",c_key_need_to_print);
}

bool check_default(char* line, char* pattern){
	char* p=strstr(line,pattern);
	if (p){
		return true;
	}
	else{
		return false;
	}
}

char* i_key_get_lowcase_line(char* line, int line_len){
	int i = 0;
	for (i = 0; i < line_len; i++) {
		line[i] = tolower(line[i]);
	}
	return line;
}

char* i_key_get_lowcase_pattern(char* pattern){
    int pattern_len=strlen(pattern);
	for (int i = 0; i < pattern_len; i++) {
		pattern[i] = tolower(pattern[i]);
	}
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
	char* p=strstr(line,pattern);
	if (!p){
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

int c_key_count_line_to_print(int c_key_need_to_print, bool print_line){
	if (print_line){
		c_key_need_to_print++;
	}
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
	if (A_key_count_remaining>=0){
		return true;
	}
	return false;
}