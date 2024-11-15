#include <iostream>
#include <vector>
#include <unordered_map>

class Interpreter
{
std::ostream& out_stream;
std::unordered_map<std::string, int> variables;
std::vector<std::string> tokens;
int position;
const std::string ETX = "\u0003";

public:
    Interpreter(std::ostream & out_stream);

    void evaluate(const std::vector<std::string>& tokens);

    void interpret(std::string fileName);

    void parse_Statement();
    void parse_ConfigStatement();
    void parse_AssgStatement();
    void parse_PrintStatement();
    int parse_MathExpression();
    int parse_SumExpression();
    int parse_ProductExpression();
    int parse_PrimaryExpression();
    std::string parse_Variable();
    int parse_Int();

    std::string peek();
    std::string peek(int steps);
    void consume(const std::string& token);
};