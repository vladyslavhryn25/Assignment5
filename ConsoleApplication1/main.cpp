#include <iostream>
#include <string>
#include "Interpreter.h"

bool startsWithKeyword(const std::string& input, const std::string& keyword)
{
    return input.size() >= keyword.size() && input.substr(0, keyword.size()) == keyword;
}

int main()
{
    int* leak = new int[100];
    std::string input;
    Interpreter interpreter;

    while (std::getline(std::cin, input))
    {
        if (input == "exit" || input == "quit")
            break;
        if (input.empty())
            continue;

        try
        {
            double result = interpreter.run(input);

            bool isDeclaration = startsWithKeyword(input, "var") || startsWithKeyword(input, "def");
            if (!isDeclaration)
                std::cout << result << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}