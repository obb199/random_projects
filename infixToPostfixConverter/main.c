#include "stack.h"
#include "npi.h"


int main(){
    char teste1[] = "3+4*5-2+4/3\0";
    char teste2[] = "2^9+4*3/2-2\0";
    char teste3[] = "(3+4+6*5-2)+(3/4-1*3)\0";
    char teste4[] = "(1+3)*(2-3)*(9-2)/5^3\0";
    char teste5[] = "7*4/3^(4+9)*2^3^4^(9-3*2-4/9)/3+2-1*(3/9^2)\0";

    infix_to_postfix(teste1);
    infix_to_postfix(teste2);
    infix_to_postfix(teste3);
    infix_to_postfix(teste4);
    infix_to_postfix(teste5);


    return 0;
}

