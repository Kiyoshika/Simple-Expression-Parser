#ifndef SIMPLE_EXPRESSION_PARSER_H
#define SIMPLE_EXPRESSION_PARSER_H

#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Parse a character buffer representing a mathematical expression and return the result as a float.
 * This tokenizes the expression on each operator (+,-,*,/) and creates a linked list where each node contains the value before the operator and the operator itself.
 * Then the list is traversed to first search the operators with the highest precendence (* and /) then finally scans left to right to compute the final result.
 * Parenthesis are currently not supported but will recursively call sep_parse(const char*) to evaluate the inner expression of each parenthesis.
 * 
 * @param expression A character buffer representing a mathematical expression such as "10-5+8*4-2"
 * @return the result of the expression as a float
 */
float sep_parse(const char* expression);

#endif