#include <iostream>
#include <string>
#include "Interpreter.h"

int main()
{
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

            bool isVarDeclaration = input.size() >= 3 && input.substr(0, 3) == "var";
            if (!isVarDeclaration)
                std::cout << result << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}