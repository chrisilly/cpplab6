#include <iostream>
#include <vector>

class Interpreter
{
std::ostream& out_stream;
std::vector<std::string> tokens;
int position;
const std::string ETX = "\u0003";

public:
    Interpreter(std::ostream & out_stream);

    void evaluate(const std::vector<std::string>& tokens);

    void interpret(std::string fileName);

    void parse_Stmt();
    void parse_ConfigStmt();
    void parse_AssgStmt();
    void parse_PrintStmt();
    int parse_MathExpression();
    int parse_SumExpression();
    int parse_ProductExpression();
    int parse_PrimaryExpression();
    int parse_Variable();
    int parse_Int();

    std::string peek();
    std::string peek(int steps);
    void consume(const std::string& token);
};