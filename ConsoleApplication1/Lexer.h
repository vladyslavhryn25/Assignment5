#pragma once
#include <string>
#include <vector>
#include "Token.h"

class Lexer
{
public:
    explicit Lexer(const std::string& source);
    std::vector<Token> tokenize();

private:
    std::string source;
    size_t pos = 0;

    char peek() const;    
    char advance();        
    bool isAtEnd() const;

    Token readNumber();
    Token readIdentifier();
};