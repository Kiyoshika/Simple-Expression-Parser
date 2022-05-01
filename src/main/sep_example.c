#include "simple_expression_parser.h"
#include <stdio.h>

int main(void)
{
    float result = sep_parse("(5-3)*3-5*((3-1)/(3*4-3))");
    printf("%f\n", result);
    return 0;
}