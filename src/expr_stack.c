#include "expr_stack.h"
#include <stdlib.h>
#include <math.h>
#include <assert.h>

void init_stack(struct expr_stack_t* stack, size_t capacity) {
    assert(stack != NULL);
    stack->data = calloc(capacity, sizeof(struct expr_t));
    stack->capacity = capacity;
    stack->top = stack->data;
    stack->element_count = 0;
}

void pop(struct expr_stack_t* stack) {
    assert(stack != NULL);
    if(stack->element_count > 0) {
        --(stack->top);
        --(stack->element_count);
    }
}

void push(struct expr_stack_t* stack, struct expr_t expression) {
    assert(stack != NULL);
    assert(stack->element_count < stack->capacity);
    
    ++(stack->top);
    *(stack->top) = expression;
    ++(stack->element_count);
}

void delete_stack(struct expr_stack_t* stack) {
    if(stack != NULL) {
        free(stack->data);
    }
}

struct expr_t create_operator(char operator_char) {
    struct expr_t expr;
    expr.type = OPERATOR;
    expr.data.operator_char = operator_char;

    return expr;
}

struct expr_t create_operand(double operand) {
    struct expr_t expr;
    expr.type = OPERAND;
    expr.data.operand = operand;

    return expr;
}

double evaluate_expression(struct expr_stack_t* stack) {
    double a, b;
    char operator;
    double result;

    while(stack->element_count > 1) {
        a = stack->top->data.operand;
        pop(stack);
        b = stack->top->data.operand;
        pop(stack);
        operator = stack->top->data.operator_char;
        pop(stack);
        
        /* TODO: change this ugly switch to something more neat */
        switch(operator) {
            case '+': {
                    result = a + b;
                    break;
                }
            case '-': {
                    result = a - b;
                    break;
                }

            case '*': {
                    result = a * b;
                    break;
                }
            case '/': {
                    result = a / b;
                    break;
                }
            case '^': {
                    result = powf(a, b);
                    break;
                }
            case '%': {
                    result = (int)a % (int)b;
                    break;
                }
            default: {
                return 0.0;
            }
        }
        push(stack, create_operand(result));
    }
    return result;
}