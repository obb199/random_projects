#include "stack.h"

void stack_init(stack * p){
    p->n = 0;
}

void push(stack * p , t_data val){
    p->data[p->n] = val;
    p->n++;
}

t_data pop(stack * p){
    p->n--;
    t_data val = p->data[p->n];
    p->data[p->n] = 0;

    return val;
}

t_data top(stack * p){
    return p->data[p->n-1];
}

bool stack_isempty(stack * p){
    return (p->n == 0);
}


