#include "simple_expression_parser.h"
#include "token_linked_list.h"
#include <stdio.h>

static bool is_operator(const char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

static int get_operator_enum_value(char c)
{
    switch(c)
    {
        case '+':
            return ADD;
        case '-':
            return SUBTRACT;
        case '*':
            return MULTIPLY;
        case '/':
            return DIVIDE;
    }

    return -1;
}

static void add_token(token** root_token, bool* root_token_set, char* buff, operator _operator)
{
    if (*root_token_set)
    {
        token* new_token = malloc(sizeof(token));
        token_init(new_token);
        token_set_operator(new_token, _operator);
        
        token_set_value(new_token, strtof(buff, NULL));
        (*root_token)->next_token = new_token;
        (*root_token) = (*root_token)->next_token;
    }
    else
    {
        token_set_operator(*root_token, _operator);
        token_set_value(*root_token, strtof(buff, NULL));
        *root_token_set = true;
    }
}

float sep_parse(const char* expression)
{
    token* _token = malloc(sizeof(token));
    token_init(_token);
    token* _next = _token;

    size_t start_idx = 0;
    size_t total_tokens = 0;
    char buff[64] = {0};
    bool root_token_set = false;
    for (size_t i = 0; i < strlen(expression); ++i)
    {
        if (is_operator(expression[i]))
        {
            memset(buff, 0, 64);
            strncpy(buff, &expression[start_idx], (i-start_idx));
            add_token(&_next, &root_token_set, buff, get_operator_enum_value(expression[i]));
            start_idx = i + 1;
            total_tokens++;
        }  
    }
    // end of line
    memset(buff, 0, 64);
    strncpy(buff, &expression[start_idx], strlen(expression));
    add_token(&_next, &root_token_set, buff, NONE);
    total_tokens++;

    token* temp = _token;
    while (temp != NULL)
    {
        printf("Value: %f\nOperator: %d\n\n", temp->value, temp->operator);
        temp = temp->next_token;
    }

    return 0.0f;
}