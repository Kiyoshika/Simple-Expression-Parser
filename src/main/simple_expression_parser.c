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

    return 0;
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

static void parse_token(char** buff, const char* expression, size_t start_idx, size_t len)
{
    memset(*buff, 0, 64);
    strncpy(*buff, &expression[start_idx], len);
}

static void construct_linked_list(token* _token, token* _next, size_t* total_tokens, const char* expression)
{
    size_t start_idx = 0;
    char* buff = calloc(65, 1);
    bool root_token_set = false;
    bool parsing_parenthesis = false;
    size_t parenthesis_count = 0;
    size_t inner_expression_idx_start, inner_expression_idx_end;
    for (size_t i = 0; i < strlen(expression); ++i)
    {
        if (is_operator(expression[i]) && !parsing_parenthesis)
        {
            parse_token(&buff, expression, start_idx, (i-start_idx));
            add_token(&_next, &root_token_set, buff, get_operator_enum_value(expression[i]));
            start_idx = i + 1;
            *total_tokens++;
        }
        else if (expression[i] == '(' && !parsing_parenthesis)
        {
            parenthesis_count++;
            parsing_parenthesis = true;
            inner_expression_idx_start = i + 1;
        }
        else if (expression[i] == '(' && parsing_parenthesis)
        {
            parenthesis_count++;
        }
        else if (expression[i] == ')' && parsing_parenthesis)
        {
            parenthesis_count--;
            if (parenthesis_count == 0)
            {
                inner_expression_idx_end = i;
                parse_token(&buff, expression, inner_expression_idx_start, inner_expression_idx_end - inner_expression_idx_start);
                float result = sep_parse(buff);
                char result_char[65] = {0};
                gcvt(result, 10, result_char);
                add_token(&_next, &root_token_set, result_char, get_operator_enum_value(expression[i+1]));
                start_idx = i + 2;
                i++; // increment i otherwise (i - start_idx) becomes negative when parsing token
                parsing_parenthesis = false;
            }
        }
    }
    // end of line
    if (strlen(buff) > 0)
    {
        parse_token(&buff, expression, start_idx, strlen(expression));
        add_token(&_next, &root_token_set, buff, NONE);
        *total_tokens++;
    }
    free(buff);
}

static void compute_high_precedence_operators(token* _token)
{
    token* temp = _token;
    token* free_token;
    while (temp != NULL)
    {
        if (temp->operator == MULTIPLY || temp->operator == DIVIDE)
        {
            switch(temp->operator)
            {
                case MULTIPLY:
                    temp->value *= temp->next_token->value;
                    break;
                case DIVIDE:
                    temp->value /= temp->next_token->value;
                    break;
            }
            temp->operator = temp->next_token->operator;
            free_token = temp->next_token;
            temp->next_token = temp->next_token->next_token;
            free(free_token);
        }
        else
            temp = temp->next_token;
    }
}

static float evaluate_final_expression(token* _token)
{
    token* temp = _token;
    float result = temp->value;
    while (temp != NULL)
    {
        switch(temp->operator)
        {
            case ADD:
                result += temp->next_token->value;
                break;
            case SUBTRACT:
                result -= temp->next_token->value;
                break;
            case MULTIPLY:
                result *= temp->next_token->value;
                break;
            case DIVIDE:
                result /= temp->next_token->value;
                break;
        }
        temp = temp->next_token;
    }
    return result;
}

float sep_parse(const char* expression)
{
    token* _token = malloc(sizeof(token));
    token_init(_token);
    token* _next = _token;

    size_t total_tokens = 0;
    construct_linked_list(_token, _next, &total_tokens, expression);

    compute_high_precedence_operators(_token);
    float result = evaluate_final_expression(_token);

    // free memory
    token* _temp;
    token* prev;
    _temp = _token;
    while (_temp != NULL)
    {
        prev = _temp;
        _temp = _temp->next_token;
        free(prev);
    }

    return result;
}