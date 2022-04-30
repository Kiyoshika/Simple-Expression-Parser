#include "token_linked_list.h"

void token_init(token* token)
{
    token->next_token = NULL;
    token->operator = NONE;
    token->value = 0.0f;
}

void token_add(token* _token, const token* add_token)
{
    _token->next_token = add_token;
}

void token_set_operator(token* _token, const operator operator)
{
    _token->operator = operator;
}

void token_set_value(token* _token, const float value)
{
   _token->value = value;
}