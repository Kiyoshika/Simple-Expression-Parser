#include "simple_expression_parser.h"
#include <stdio.h>

int main(void)
{
    float result = sep_parse("10-5+2*4-3*3/2*5/2+5*2-3/6*3");
    printf("%f\n", result);
    return 0;
}