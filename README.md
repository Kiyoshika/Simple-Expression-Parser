# Simple Expression Parser
This is a simple expression parser that converts a character buffer representing a mathematical expression and returns the result as a float.

This will be used in an embedded calculator project (coming soon).

Note that this parser expects sanitized inputs, parser will likely break if you have spaces or any unexpected characters/functions.

# Building from Source
This is a simple cmake project. After cloning the repo and entering root directory,
* `mkdir build && cd build`
* `cmake ..`
* `make`

This will create a `libsep.a` static library, I have not created any `make install` target so for now this will have to be added to your projects manually.

# Tests
I was having trouble getting googletest to work with pure C code so I will have to find a different alternative to write tests.

# How it Works

### High Level
1. Given a character buffer representing a mathematical expression, parse into tokens on each operator (+,-,*,/).
   1. A token contains the value and it's corresponding operator (e.g. 5 and +)
   2. NOTE: if parenthesis are enountered, the parsing is called recursively to get the final value even if there are nested parenthesis.
2. A linked list is constructed by all of these tokens, essentially converting the character buffer into a chain of values and operators
3. Search and compute highest precedence operators first (* and /)
4. Finally, start left-to-right and compute remaining expression
### Details / Example

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

### Complex Example With Parenthesis
Here's a much more sophisticated example involving parenthesis

Buffer: `(5-3)*3-5*((3-1)/(3*4-3))`

1. Extract inner expression `5-3` and parse
   1. `[5|-] -> [3|null]`
   2. `2`
2. Add value to our list with its corresponding operator. This is the first value so it's our root node
   1. `[2|*] -> null`
3. Add next token to our list
   1. `[2|*] -> [3|-] -> null`
4. Add next token to our list
   1. `[2|*] -> [3|-] -> [5|*] -> null`
5. Extract inner expression `((3-1)/(3*4-3))` and parse
   1. This itself contains another inner expression `3-1` with operator `/`
      1. `[3|-] -> [1|null]`
      2. Current list: `[2|/] -> null`
   2. And another inner expression `3*4-3` with no operator
      1. `[3|*] -> [4|-] -> [3|null]`
      2. Compute highest precedence first and evaluate final expression (see previous example for this)
      3. `9`
      4. Current list: `[2|/] -> [9|null]`
      5. `0.222`
6. Add parsed value to list; note it doesn't have any operators afterwards
   1. `[2|*] -> [3|-] -> [5|*] -> [0.222|null]`
   2. Compute highest precedence operators first
   3. `[6|-] -> [1.111|null]`
7. Evaluate final expression left-to-right
   1. `4.889`