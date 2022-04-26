#include "simple_expression_parser.h"
#include <stdio.h>

static bool is_operator(const char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

float sep_parse(const char* expression)
{
    char left_hand_expression[64] = {0};
    char right_hand_expression[64] = {0};

    for (size_t i = 0; i < strlen(expression); ++i)
    {
        if (is_operator(expression[i]))
        {
            strncpy(left_hand_expression, expression, i);
            strncpy(right_hand_expression, &expression[i+1], strlen(expression));
            switch(expression[i])
            {
                case '+':
                    return sep_parse(left_hand_expression) + sep_parse(right_hand_expression);
                case '-':
                    return sep_parse(left_hand_expression) - sep_parse(right_hand_expression);
                case '*':
                    return sep_parse(left_hand_expression) * sep_parse(right_hand_expression);
                case '/':
                    return sep_parse(left_hand_expression) / sep_parse(right_hand_expression);
                default: // this shouldn't be reachable but putting it here anyways
                    break;
            }
        }
    }

    return strtof(expression, NULL);
}