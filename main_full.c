#include "main_full.h"


/* 
    parse_arguments() recieves argc and argv and copies the command line
    parameters to the output buffers pattern and filename. 
*/
int parse_arguments(int argc, char *argv[], char* pattern, char* filename, switches* sws)
{
    if(argc < 3)
        return FALSE;

    // if the first argument is not a switch, then it's the pattern to search
    if (!parse_switch(argv[1], sws))
        strcpy(pattern, argv[1]);
    
    // parse the remaining command line arguments
    for(int i=2; i < argc; i++)
    {
        // handle compound switch (-A number, -E "quoted string")
        if(sws->next_is_prev_num_lines)
        {
            sws->next_is_prev_num_lines = FALSE;
            sws->print_n_prev_lines = atoi(argv[i]);
        }
        else if(sws->next_is_quoted_string)
        {
            sws->next_is_quoted_string = FALSE;
            strcpy(pattern, argv[i]);
        }
        else
        {
            // handle switches
            if(!parse_switch(argv[i], sws))
            {
                // if unable to parse the switch and it's the last argument then it's the filename
                if (i == argc - 1)
                    strcpy(filename, argv[argc - 1]);
                // otherwise it's an error
                else
                    return FALSE;                
            }
        }
    }

    return TRUE;
}

/*
    parse_switch() is a helper function to search for switches
    return TRUE if the string is a switch
*/
int parse_switch(char*s, switches*sws)
{
    if(strcmp(s, "-b") == 0)
        sws->print_num_bytes = TRUE;
    else if(strcmp(s, "-c") == 0)
        sws->print_only_line_nums = TRUE;
    else if(strcmp(s, "-i") == 0)
        sws->case_insensitive = TRUE;
    else if(strcmp(s, "-n") == 0)
        sws->print_line_num = TRUE;        
    else if(strcmp(s, "-v") == 0)
        sws->print_not_matching = TRUE;
    else if(strcmp(s, "-x") == 0)
        sws->print_exact_match = TRUE;
    else if(strcmp(s, "-A") == 0)
    {
        sws->print_n_prev_lines = TRUE;
        sws->next_is_prev_num_lines = TRUE;
    }
    else if(strcmp(s, "-E") == 0)
    {
        sws->quoted_string = TRUE;
        sws->next_is_quoted_string = TRUE;
    }
    else
        return FALSE;
    return TRUE;
}
/*
    print_switches() prints the parsed switches, for debugging purposes
*/
void print_switches(switches sws)
{
    printf("print_n_prev_lines %d\n", sws.print_n_prev_lines);
    printf("print_num_bytes %d\n", sws.print_num_bytes);
    printf("print_only_line_nums %d\n", sws.print_only_line_nums);
    printf("case_insensitive %d\n", sws.case_insensitive);
    printf("print_line_num %d\n", sws.print_line_num);
    printf("print_not_matching %d\n", sws.print_not_matching);
    printf("print_exact_match %d\n", sws.print_exact_match);
}


/* 
    match_pattern() receives a pattern and filename and goes through every line in 
    the file and searches for the pattern. Upon a match, it prints the entire line 
*/
int match_pattern(char* pattern, char* filename)
{
    FILE *f;
    char line[STR_MAX_SZ];

    if (strlen(filename) == 0)
    {
        // TODO handle standard input
        return TRUE;
    }
    f = fopen(filename, "rt");
    if(f==NULL)
    {
        printf("File %s not found\n", filename);
        return FALSE;
    }

    while(!feof(f))
    {
        fgets(line, STR_MAX_SZ, f);
        if(f==NULL)
            break;
        if(strstr(line, pattern))
            printf("%s", line);
    }
    fclose(f);
    return TRUE;
}

/*
    main program entry
*/
int main(int argc, char*argv[])
{
    char filename[STR_MAX_SZ] = { 0 }, pattern[STR_MAX_SZ] = { 0 };
    switches sws = { 0 };

    if(parse_arguments(argc, argv, pattern, filename, (switches*)&sws))
        match_pattern(pattern, filename);
    else
    {
        printf(USAGE);
        return 1;
    }

    print_switches(sws);
    printf("File is %s\n", (strlen(filename) == 0) ? "stdin" : filename);
    printf("String to search is '%s'\n", pattern);

    return 0;
}