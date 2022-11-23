#include "main_full.h"
#include "keys.h"

/*
    parse_switch() is a helper function to search for switches
    return true if the string is a switch
*/
bool parse_switch(char*s, switches*sws)
{
    if(strcmp(s, "-b") == 0){
        sws->b_print_num_bytes = true;
    }
    else if(strcmp(s, "-c") == 0){
        sws->c_print_only_line_nums = true;
    }
    else if(strcmp(s, "-i") == 0){
        sws->i_case_insensitive = true;
    }
    else if(strcmp(s, "-n") == 0){
        sws->n_print_line_num = true;
    }        
    else if(strcmp(s, "-v") == 0){
        sws->v_print_not_matching = true;
    }
    else if(strcmp(s, "-x") == 0){
        sws->x_print_exact_match = true;
    }
    else if(strcmp(s, "-A") == 0)
    {
        sws->A_print_n_prev_lines = true;
        sws->next_is_prev_num_lines = true;
    }
    else if(strcmp(s, "-E") == 0)
    {
        sws->quoted_string = true;
        sws->next_is_quoted_string = true;
    }
    else{
        return false;
    }
    return true;
}
/*
    print_switches() prints the parsed switches, for debugging purposes
*/
void print_switches(switches sws)
{
    printf("print_n_prev_lines %d\n", sws.A_print_n_prev_lines);
    printf("print_num_bytes %d\n", sws.b_print_num_bytes);
    printf("print_only_line_nums %d\n", sws.c_print_only_line_nums);
    printf("case_insensitive %d\n", sws.i_case_insensitive);
    printf("print_line_num %d\n", sws.n_print_line_num);
    printf("print_not_matching %d\n", sws.v_print_not_matching);
    printf("print_exact_match %d\n", sws.x_print_exact_match);
}

void error_no_pattern(){
    printf("please enter a pattern\n");
}

bool parse_arguments(int argc, char *argv[], char* pattern, char* filename, switches* sws,indexes_pattern_and_filename* indexes_pattern_filename)
{   
    bool grep_flag , input_with_file;
    int check_if_pattern_or_filename=0;
    int i;
    for (i=1; i<argc; i++){
        if (sws->next_is_prev_num_lines){
            sws->next_is_prev_num_lines=false;
            sws->A_num=atoi(argv[i]);
            continue;
        }
        grep_flag=parse_switch(argv[i],sws);
        if (!grep_flag && check_if_pattern_or_filename==0){
            indexes_pattern_filename->pattern_index_in_argc=i;
            check_if_pattern_or_filename++;
        }
        else if(!grep_flag && check_if_pattern_or_filename==1){
            indexes_pattern_filename->filename_index_in_argc=i;
            check_if_pattern_or_filename++;
        }
    }
    if (check_if_pattern_or_filename==0){
        error_no_pattern();
    }
    if (check_if_pattern_or_filename==1){
        input_with_file=false;
    }
    input_with_file=true;
    return input_with_file;
}

void initialize_print_data(data_for_print* data){
    data->print_line=false;
    data->print_becauseof_A=false;
    data->total_bytes_read=0;
    data->line_counter=1;
    data->c_key_need_to_print=0;
    data->last_printed=true;
    data->first_print_done=false;
}

int analyze_line_and_print(data_for_print* data,switches* sws, char* pattern, char* line, char* original_line_copy,
 int A_key_count_remaining, int line_len, int read_chars){
    if (sws->i_case_insensitive){
        strcpy(line,i_key_get_lowcase_line(line,line_len));
        strcpy(pattern,i_key_get_lowcase_pattern(pattern));
    }
    if (sws->x_print_exact_match){
        data->print_line=x_key_only_and_exact_pattern(line,pattern);
    }
    if (sws->v_print_not_matching){
        if (sws->x_print_exact_match){
            data->print_line=!data->print_line;
        }
        else{
            data->print_line=v_key_pattern_not_found(line,pattern);
        }
    }
    if (!sws->x_print_exact_match && !sws->v_print_not_matching){
        data->print_line=check_default(line, pattern);
    }
    if (sws->c_print_only_line_nums){
        c_key_count_line_to_print(data);
        data->print_line=false;
    }
    if (sws->A_print_n_prev_lines){
        A_key_count_remaining=A_key_add_num_lines(data->print_line, sws->A_num, A_key_count_remaining);
        data->print_becauseof_A=check_if_print(A_key_count_remaining);
    }
    print_output(data, original_line_copy,sws);
    if (sws->b_print_num_bytes){
        data->total_bytes_read=b_key_count_bytes(data->total_bytes_read,read_chars);
    }
    data->line_counter=n_key_count_lines(data->line_counter);
    return A_key_count_remaining;
}

void read_file_and_print(char* filename, char* pattern, switches* sws){
    size_t line_len=0;
    char *line=0, *original_line_copy;
    int read_chars=1, A_key_count_remaining=-1;
    FILE* f;
    data_for_print *data = (data_for_print*) malloc(sizeof(data_for_print));
    initialize_print_data(data);
    f=fopen(filename,"r");
    while (read_chars>0){
        read_chars=getline(&line,&line_len,f);
        original_line_copy=(char*) malloc (read_chars*sizeof(char));
        if (read_chars==-1){
            continue;
        }
        line[read_chars-1]='\0';
        strcpy(original_line_copy, line);
        //sws,line,original_line_copy,line_len,pattern,data,A_count_remaining
        A_key_count_remaining=analyze_line_and_print(data,sws, pattern, line, original_line_copy, A_key_count_remaining,line_len, read_chars);
        free(original_line_copy);
    }
    if (sws->c_print_only_line_nums){
        print_c_key_output(data->c_key_need_to_print);
    }
    free(data);
    fclose(f);
}

/*
    main program entry
*/
int main(int argc, char*argv[])
{
    char *filename, *pattern;
    bool input_with_file;
    switches sws = { false };
    indexes_pattern_and_filename* indexes_pattern_filename;
    indexes_pattern_filename=(indexes_pattern_and_filename*) malloc(sizeof(indexes_pattern_and_filename));
    input_with_file=parse_arguments(argc, argv, pattern, filename, (switches*)&sws, indexes_pattern_filename);
    pattern=(char*) malloc(strlen(argv[indexes_pattern_filename->pattern_index_in_argc])*sizeof(char));
    filename=(char*) malloc(strlen(argv[indexes_pattern_filename->filename_index_in_argc])*sizeof(char));
    strcpy(pattern,argv[indexes_pattern_filename->pattern_index_in_argc]);
    strcpy(filename,argv[indexes_pattern_filename->filename_index_in_argc]);
    read_file_and_print(filename, pattern, &sws);

    free(pattern);
    free(filename);
    free(indexes_pattern_filename);
    return 0;
}