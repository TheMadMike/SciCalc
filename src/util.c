#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void readline_safe(char* destination, int max_chars) {
    assert(max_chars > 0);

    char* read = fgets(destination, max_chars, stdin);
    
    if(read == NULL) {
        return;
    }

    int str_end = 0;
    while((str_end < (max_chars-1)) && (read[str_end] != '\n') && (read[str_end] != '\0')) {
        ++str_end;
    }

    read[str_end] = '\0';
}

char* substr(char* str, size_t begin, size_t end) {
    assert(begin < end);
    assert(str != NULL);

    char* sub_str = calloc((end - begin) + 1, sizeof(char));
    
    if(sub_str == NULL)
        return NULL;

    sub_str[end - begin] = '\0';

    for(size_t i = begin; i < end; ++i) {
        sub_str[i - begin] = str[i];
    }

    return sub_str;
} 

struct token_array tokenize(char* line_buffer, size_t max_size) {
    struct token_array tokens;
    tokens.size = 0ul;
    /* set the initial token_array capacity */
    size_t capacity = 32UL;
    
    tokens.tokens = calloc(capacity, sizeof(char*));

    size_t end = 0;
    size_t begin = 0;

    char prev = line_buffer[end];
    ++end;
    char next = line_buffer[end];

    while(tokens.size < max_size && (next != '\0')) {
        next = line_buffer[end];    
        
        /* if there is a bracket 
           or if numeric literal ended
           or if text literal ended
           or if there is an operator
           we separate it into a new token */
        if((IS_CHAR_NUMERIC(prev) && !IS_CHAR_NUMERIC(next))
            || IS_CHAR_BRACKET(prev)
            || IS_CHAR_OPERATOR(prev)
            || (IS_CHAR_TEXT(prev) && !IS_CHAR_TEXT(next))
            || (next == ' ')) {

            if(tokens.size >= capacity) {
                capacity += 16UL;
                tokens.tokens = realloc(tokens.tokens, sizeof(char*) * capacity);
            }

            tokens.tokens[tokens.size] = substr(line_buffer, begin, end);
            tokens.size += 1;

            
            while(line_buffer[end] == ' ' && (end < max_size)) {
                ++end;
            }

            begin = end;
        }

        prev = line_buffer[end];
        ++end;
    }

    return tokens;
}

void delete_token_array(struct token_array token_arr) {
    assert(token_arr.tokens != NULL);

    for(size_t i = 0; i < token_arr.size; ++i) {
        
        if(token_arr.tokens[i] != NULL) {
            free(token_arr.tokens[i]);
        }

    }
    
    free(token_arr.tokens);
}