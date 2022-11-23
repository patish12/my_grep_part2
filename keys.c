#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "keys.h"


void print_output(data_for_print* data,char* line, switches* sws){
	char a;
	bool need_to_print=data->print_becauseof_A || data->print_line;

	if (sws->A_print_n_prev_lines){
		if (need_to_print && data->last_printed==false && data->first_print_done){
			printf("--\n");
		}
		if (need_to_print && data->first_print_done==false){
			data->first_print_done=true;
		}
	}
	if (data->print_becauseof_A){
		a='-';
	}
	if (data->print_line){
		a=':';
	}
	if (need_to_print){
		if (sws->n_print_line_num){
			printf("%d%c",data->line_counter,a);
		}
		if (sws->b_print_num_bytes){
			printf("%d%c",data->total_bytes_read,a);
		}
			printf("%s\n",line);
	}

	data->last_printed=need_to_print;
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

void c_key_count_line_to_print(data_for_print* data){
	if (data->print_line){
		data->c_key_need_to_print++;
		data->print_line=false;
	}
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