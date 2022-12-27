#ifndef EXPR_STACK_H
#define EXPR_STACK_H

#include <stddef.h>
#include <inttypes.h>

#define OPERATOR 0
#define OPERAND 1

typedef char expr_type;

struct expr_t {
    expr_type type;
    union {
        char operator_char;
        double operand;
    } data;
};

/**
 * @brief Create a operator structure
 * 
 * @param operator_char character determining the operator type
 */
struct expr_t create_operator(char operator_char);

/**
 * @brief Create a operand structure
 * 
 * @param operand operand value
 */
struct expr_t create_operand(double operand);

/* simple LIFO stack for expressions */
struct expr_stack_t {
    struct expr_t* data;
    size_t capacity;
    size_t element_count;
    struct expr_t* top;
};

/**
 * @brief Allocate memory for the stack structure and initialize the top pointer
 * 
 * @param stack 
 * @param capacity 
 * @param element_size 
 */
void init_stack(struct expr_stack_t* stack, size_t capacity);

/**
 * @brief Pop the stack
 * 
 * @param stack 
 */
void pop(struct expr_stack_t* stack);

/**
 * @brief Push an element to the stack
 * 
 * @param stack 
 * @param element 
 */
void push(struct expr_stack_t* stack, struct expr_t expression);

/**
 * @brief Free the dynamically allocated memory of stack strucutre
 * 
 * @param stack 
 */
void delete_stack(struct expr_stack_t* stack);

/**
 * @brief Calculate the whole arithmetic expression final value (the result)
 * 
 * @param stack LIFO with operators/operands
 * @return double expression result
 */
double evaluate_expression(struct expr_stack_t* stack);


#endif /* EXPR_STACK_H */