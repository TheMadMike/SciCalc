#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>

struct token_array {
    char** tokens;
    size_t size;
};

/**
 * @brief Read from stdin until newline 
 * or when the length of the input reached max_chars
 * 
 * @param destination a pointer to the destination
 * @param max_chars maximum characters to read
 */
void readline_safe(char* destination, int max_chars);

/**
 * @brief Splits line buffer into tokens (operands, operators, brackets)
 * 
 * @param line_buffer line read from stdin
 * @param max_size max size of the line_buffer string
 * @return struct token_array an array of tokens
 */
struct token_array tokenize(char* line_buffer, size_t max_size);

void delete_token_array(struct token_array token_arr);

#endif /* UTIL_H */