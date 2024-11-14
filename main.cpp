#include "interpreter.h"
#include <iostream>
#include <fstream>
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
        cout << myText << endl;        

        // Separate the tokens in the current line (myText) of the file
        regex regex("\\s+");
        sregex_token_iterator iterator(myText.begin(), myText.end(), regex, -1);
        sregex_token_iterator end;
        vector<string> tokens(iterator, end);
        
        // 2. call evaluate()
        evaluate(tokens);
    }

}

void Interpreter::evaluate(const std::vector<std::string>& tokens)
{
    for(auto token : tokens)
        cout << token << endl;
}