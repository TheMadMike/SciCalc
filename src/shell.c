#include "shell.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "strings.h"
#include "util.h"

#define MAX_LINE_LENGTH 64

static struct token_array tokens;

void handle_sigint(int flags) {
    puts(GOODBYE_MESSAGE);
    if(tokens.tokens != NULL)
        delete_token_array(tokens);
    exit(0);
} 

int shell_run(void) {
    signal(SIGINT, handle_sigint);

    printf(INITIAL_PROMPT_FORMAT, VERSION_STRING);

    char line_buffer[MAX_LINE_LENGTH];

    
    while(1) {
        printf(USER_PROMPT);
        readline_safe(line_buffer, MAX_LINE_LENGTH);
        
        tokens = tokenize(line_buffer, MAX_LINE_LENGTH);
        for(size_t i = 0; i < tokens.size; ++i) {
            printf("%s \n", tokens.tokens[i]);
        }

        if(tokens.size == 1) {
            if(strcmp(tokens.tokens[0], "help") == 0) {
                puts(HELP_MESSAGE);
            }
            else if(strcmp(tokens.tokens[0], "exit") == 0) {
                puts(GOODBYE_MESSAGE);
                delete_token_array(tokens);
                return 0;
            }
        }

        delete_token_array(tokens);
    }

    return 0;
}

void print_error_message(int error_code) {
    /* TODO: add messages to associated error codes */
}