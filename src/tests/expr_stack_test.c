#ifndef ASSERT_H
#include <assert.h>
#endif /* ASSERT_H */

#include "../expr_stack.h"

void expr_stack_setup(struct expr_stack_t* stack) {
    init_stack(stack, 64UL);
}

void expr_stack_teardown(struct expr_stack_t* stack) {
    delete_stack(stack);
}

void exp_stack_test_expr_eval() {
    struct expr_stack_t stack;

    /* 1. Setup: initialize the stack with sample expression: (4.3 + 3.1415) * 4.5 */
    expr_stack_setup(&stack);

    push(&stack, create_operator('*'));
    push(&stack, create_operand(4.5));
    push(&stack, create_operator('+'));
    push(&stack, create_operand(4.3));
    push(&stack, create_operand(3.1415));

    /* 2. Run the evaluation function, expect the correct result */
    double result = evaluate_expression(&stack);

    assert(result == ((4.3 + 3.1415)*4.5));

    /* 3. Teardown*/
    expr_stack_teardown(&stack);
}

/* test push/pop functionality */
void exp_stack_test_push_pop() {
    struct expr_stack_t stack;

    /* 1. Setup: initialize the stack with sample expression: 4.3 + 4.5*/
    expr_stack_setup(&stack);

    push(&stack, create_operator('+'));
    push(&stack, create_operand(4.5));
    push(&stack, create_operand(4.3));

    double expected_operands[2] = {4.3, 4.5};

    /* 2. Pop the stack 2 times and check if all of the operands are in correct format */
    for(size_t i = 0; i < 2; ++i) {
        assert((*(stack.top)).type == OPERAND);
        assert((*(stack.top)).data.operand == expected_operands[i]);
        pop(&stack);
    }

    assert((*stack.top).type == OPERATOR);
    assert((*stack.top).data.operator_char == '+');

    /* 3. Teardown*/
    expr_stack_teardown(&stack);
}   

void exp_stack_test_run_all() {
    exp_stack_test_push_pop();
    exp_stack_test_expr_eval();
}