#include "interpreter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <bitset>

// using namespace std;

using namespace std;

string fileName = "example-source.txt";

int main()
{
    // std::cout << "Hello World!" << std::endl;

    Interpreter interpreter(cout);

    interpreter.interpret(fileName);

    cout << "---------------------------------" << endl;
}

Interpreter::Interpreter(ostream& out_stream) : config(Config::dec), out_stream(out_stream), position(0) {}

void Interpreter::interpret(string& fileName)
{
    // 1. get a vector<string> for each line containing all its tokens
    ifstream source(fileName);

    string myText;

    while(getline(source, myText))
    {
        // cout << myText << endl;

        istringstream line(myText);
        string token;

        // Separate the tokens in the current line (myText) of the file
        while (line >> token)
        {
            tokens.push_back(token);
        }
        
        // 2. call evaluate()
        evaluate(tokens);
    }
}

void Interpreter::evaluate(const std::vector<std::string>& tokens)
{
    parse_Statement();
}

void Interpreter::consume(const string& token)
{
    string next_token = peek();
    if(next_token == ETX)
        throw runtime_error("Consumed past last token\n");
    if(next_token != token)
        throw runtime_error("Could not consume token " + token + "\n");

    ++position;
}

string Interpreter::peek()
{
    return peek(0);
}

std::string Interpreter::peek(int steps)
{
    const string ETX = "\u0003";

    if(position+steps >= tokens.size()) return ETX;

    return tokens[position + steps];
}

void Interpreter::parse_Statement()
{
    string next_token = peek();

    if(next_token == "config")
        parse_ConfigStatement();
    else if(next_token == "print")
        parse_PrintStatement();
    else
        parse_AssgStatement();
}

void Interpreter::parse_ConfigStatement()
{
    consume("config");
    string next_token = peek();

    cout << "config set to ";

    if(next_token == "dec")
    {
        config = Config::dec;
        cout << "decimal" << endl;
    }
    else if(next_token == "hex")
    {
        config = Config::hex;
        cout << "hexadecimal" << endl;
    }
    else if(next_token == "bin")
    {
        config = Config::binary;
        cout << "binary" << endl;
    }
    else
        throw runtime_error("Expected dec, hex or bin\n");

    consume(next_token);
}

void Interpreter::parse_PrintStatement()
{
    consume("print");

    switch (config)
    {
    case Config::binary:
        out_stream << bitset<16>(parse_MathExpression()).to_string();
        break;
    case Config::hex:
        out_stream << std::hex << showbase << parse_MathExpression();
        break;
    default:
        out_stream << parse_MathExpression();
        break;
    }

    out_stream << endl;
}

void Interpreter::parse_AssgStatement()
{
    string name = peek();
    int value;

    consume(name);
    string next_token = peek();

    if(next_token == "=")
    {
        consume("=");
        value = parse_MathExpression();
    }
    else
        throw runtime_error("Expected: =\n");

    variables[name] = value;
}

int Interpreter::parse_MathExpression()
{
    return parse_SumExpression();
}

int Interpreter::parse_SumExpression()
{
    int result = parse_ProductExpression();

    string next_token = peek();

    while(1)
    {
        if(next_token == "+")
        {
            consume("+");
            int newTerm = parse_ProductExpression();
            result = result + newTerm;
        }
        else if(next_token == "-")
        {
            consume("-");
            int newTerm = parse_ProductExpression();
            result = result - newTerm;
        }
        else
            break;

        next_token = peek();
    }

    return result;
}

int Interpreter::parse_ProductExpression()
{
    int result = parse_PrimaryExpression();

    string next_token = peek();

    while(1)
    {
        if(next_token == "*")
        {
            consume("*");
            int newTerm = parse_PrimaryExpression();
            result = result * newTerm;
        }
        else if(next_token == "/")
        {
            consume("/");
            int newTerm = parse_PrimaryExpression();
            result = result / newTerm;
        }
        else
            break;

        next_token = peek();
    }

    return result;
}

int Interpreter::parse_PrimaryExpression()
{
    int value;
    string next_token = peek();

    // check regex matching
    bool isInt = regex_match(next_token, regex("-?[0-9]+"));
    bool isVariable = regex_match(next_token, regex("[a-zA-Z][a-zA-Z0-9]*"));

    if(isInt)
    {
        value = parse_Int();
    }
    else if(isVariable)
    {
        consume(next_token);
        if(variables.find(next_token) == variables.end())
            throw runtime_error("Undefined variable\n");

        value = variables[next_token];
    }
    else if(next_token == "(")
    {
        consume("(");

        value = parse_MathExpression();

        if(peek() == ")")
            consume(")");
        else
            throw runtime_error("Expected: )\n");
    }
    else
        throw runtime_error("Expected Int, Variable or MathExpression\n");

    return value;
}

int Interpreter::parse_Int()
{
    string next_token = peek();
    int value = stoi(next_token);
    consume(next_token);

    return value;
}