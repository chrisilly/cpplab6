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
    void parse_MathExp();
    void parse_SumExp();
    void parse_ProductExp();
    void parse_PrimaryExp();
    void parse_Variable();
    void parse_Int();

    std::string peek();
    std::string peek(int steps);
    void consume(const std::string& token);
};