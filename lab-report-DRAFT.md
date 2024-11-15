**Chris Culling**

Lab for **assignment 6**

9 Nov 2024

<!-- Assignment reference and example: https://github.com/Rassou1/CatInterpreter -->

1. Parsing function per nonterminal
2. Peek-function: identify *statments* and *expressions* from tokens before parsing
3. Consume-function

Variable names + values = key-value pairs in hash table (symbol table, managed by `AssgStmt`)

1. Have file with C@ source code
2. function takes filename as input
- getline for each line
- split each token in each line in and store all those tokens in a vector<string>
- send them to intepreter that interprets one vector<string> at a time

why tf does `Interpreter` take an `ostream`???

# Requirements

# Issues