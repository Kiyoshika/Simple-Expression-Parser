#include "simple_expression_parser.h"
#include <stdio.h>

int main(void)
{
    float result = sep_parse("10-5+8*4-2");
    printf("%f\n", result);
    return 0;
}