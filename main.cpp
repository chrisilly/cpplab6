#include "interpreter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

// using namespace std;

using namespace std;

string fileName = "source.txt";

int main()
{
    // std::cout << "Hello World!" << std::endl;

    Interpreter interpreter(cout);

    interpreter.interpret(fileName);
}

Interpreter::Interpreter(ostream& out_stream)
{
    
}

void Interpreter::interpret(string fileName)
{
    // 1. get a vector<string> for each line containing all its tokens
    ifstream source("source.txt");

    string myText;

    while(getline(source, myText))
    {
        // cout << myText << endl;

        vector<string> tokens;

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
    for(auto token : tokens)
        cout << token << endl;

    cout << "---" << endl;
}