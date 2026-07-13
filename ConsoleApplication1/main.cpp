#include <iostream>
#include <string>
#include "Lexer.h"

std::string tokenTypeName(TokenType type)
{
    switch (type)
    {
    case TokenType::Number:     return "Number";
    case TokenType::Identifier: return "Identifier";
    case TokenType::Plus:       return "Plus";
    case TokenType::Minus:      return "Minus";
    case TokenType::Star:       return "Star";
    case TokenType::Slash:      return "Slash";
    case TokenType::LParen:     return "LParen";
    case TokenType::RParen:     return "RParen";
    case TokenType::Comma:      return "Comma";
    case TokenType::LBrace:     return "LBrace";
    case TokenType::RBrace:     return "RBrace";
    case TokenType::Assign:     return "Assign";
    case TokenType::End:        return "End";
    }
    return "?";
}

int main()
{
    std::string input;
    while (std::getline(std::cin, input))
    {
        if (input == "exit" || input == "quit")
            break;
        if (input.empty())
            continue;

        try
        {
            Lexer lexer(input);
            std::vector<Token> tokens = lexer.tokenize();

            for (const Token& token : tokens)
                std::cout << tokenTypeName(token.type) << "(" << token.text << ") ";
            std::cout << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cout << "Lexer error: " << e.what() << std::endl;
        }
    }
    return 0;
}