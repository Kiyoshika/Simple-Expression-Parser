#include "simple_expression_parser.h"
#include <stdio.h>

int main(void)
{
    float result = sep_parse("5-5+10+3");
    printf("Result: %f\n", result);
    return 0;
}