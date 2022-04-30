# Simple Expression Parser
This is a simple expression parser that converts a character buffer representing a mathematical expression and returns the result as a float.

This will be used in an embedded calculator project (coming soon).

More to be written as the project progresses

# How it Works
This is still in development but this is essentially the idea:

For example, let's say our character buffer is `10-5+2*4-3`

1. The character buffer is tokenized on operators and will construct a linked list where each node holds the parsed value as a float and the operator.

`[10|-] -> [5|+] -> [2|*] -> [4|-] -> [3|null]`

2. Any parenthesis will have to be evaluated (probably recursively) to construct the final chain like above.

3. The list is scanned to compute highest precendence operators (multiplication and division) first. To actually do the computations, whenever it finds an operator (* or /) it will operate with the next node's value and replace current node's operator with next node's operator then de-link the next node.

`... -> [2|*] -> [4|-] -> [3|null]`

becomes

`... -> [8|-] -> [3|null]`

4. After the higher precedence operators are computed, we finally scan left to right to compute everything with similar logic until we reach the end (when the operator is null/none) giving us the final result

`[10|-] -> [5|+] -> [8|-] -> [3|null]`

`[5|+] -> [8|-] -> [3|null]`

`[13|-] -> [3|null]`

`10`