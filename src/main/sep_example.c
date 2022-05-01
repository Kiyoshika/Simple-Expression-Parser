#include "simple_expression_parser.h"
#include <stdio.h>

int main(void)
{
    float result = sep_parse("2-(5-2)*5");
    printf("%f\n", result);
    return 0;
}