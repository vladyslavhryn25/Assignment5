#pragma once
#include <string>
#include <vector>
#include <map>
#include "Token.h"

class Interpreter
{
public:
    double run(const std::string& line);

private:
    std::vector<Token> tokens;
    size_t pos = 0;
    std::map<std::string, double> variables;

    const Token& current();
    void advance();
    bool match(TokenType type);

    double parseExpression(); 
    double parseTerm();     
    double parseFactor();   
};