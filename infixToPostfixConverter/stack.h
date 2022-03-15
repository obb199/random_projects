#ifndef _STACK_H
#define _STACK_H

#define MAX_STACK 50
#include <stdbool.h>

typedef char t_data;

typedef struct {
    t_data data[MAX_STACK];
    int n;
} stack;

void stack_init(stack *);

void push(stack *, t_data);

t_data pop(stack *);

t_data top(stack *);

bool stack_isempty(stack * p);

#endif
