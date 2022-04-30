#ifndef TOKEN_LINKED_LIST
#define TOKEN_LINKED_LIST

#include <stdlib.h>
#include <stdio.h>

typedef enum operator
{
    NONE,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE
} operator;

typedef struct token token;
struct token
{
    token* next_token;
    operator operator;
    float value;

};

void token_init(token* _token);
void token_add(token* root_token, const token* add_token);
void token_set_operator(token* _token, const operator operator);
void token_set_value(token* _token, const float value);

#endif