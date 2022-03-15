#include "npi.h"

void infix_to_postfix(char expression[]){
    if (!check_string(expression)){
        printf("Expressao invalida!!");
        exit(-1);
    }

    stack operators;
    stack_init(&operators);

    char result[strlen(expression)];
    int len_result = 0;

    for(int i = 0; expression[i] != '\0'; i++){
        if (expression[i] == '('){
            push(&operators, expression[i]);
        }else if (expression[i] == ')'){
            while(!stack_isempty(&operators)){
                if (top(&operators) != ')' && top(&operators) != '('){
                    result[len_result++] = pop(&operators);
                }else{
                    pop(&operators);
                }
            }
        }else if (level_priority(expression[i]) == 0){
            result[len_result++] = expression[i];
        }else{
            if (top(&operators) == '^' && expression[i] == '^'){
                push(&operators, expression[i]);
            }else if (stack_isempty(&operators) || level_priority(expression[i]) > level_priority(top(&operators))){
                push(&operators, expression[i]);
            }
            else if (level_priority(expression[i]) == level_priority(top(&operators))){
                result[len_result++] = pop(&operators);
                push(&operators, expression[i]);
            }else{
                while(!stack_isempty(&operators)){
                    if (level_priority(expression[i]) <= level_priority(top(&operators))) result[len_result++] = pop(&operators);
                    else break;
                }
                push(&operators, expression[i]);
            }
        }
    }
    while(!stack_isempty(&operators)) result[len_result++] = pop(&operators);

    printf("\n%s = ", expression);
    for(int i = 0; i < len_result; i++){
        if (result[i] != '(' && result[i] != ')')
        printf("%c", result[i]);
    }
    printf("\n");
}

int level_priority(char c){
        if (c == '+' || c == '-') return 1;
        if (c == '*' || c == '/') return 2;
        if (c == '^') return 3;
        return 0;
}


bool check_string(char str[]){
    int numbers = 0;
    int operators = 0;
    int open = 0;
    int close = 0;

    for(int i = 0; str[i] != '\0'; i++){
        if (str[i] >= '0' && str[i] <= '9'){
            numbers++;
        }else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^'){
            operators++;
        }else if (str[i] == '('){
            open++;
        }else if (str[i] == ')'){
            close++;
        }else{
            return false;
        }
    }

    if (open == close && numbers == ++operators) return true;

    return false;
}
