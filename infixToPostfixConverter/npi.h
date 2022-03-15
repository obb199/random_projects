#ifndef _NPI_H
#define _NPI_H

#include <stdio.h>
#include <stdbool.h>
#include "stack.h"
#include <string.h>

int level_priority(char);
bool check_string(char []);
void infix_to_postfix(char expression[]);

#endif //_NPI_H
