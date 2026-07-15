#pragma once
#include <string>
#include <vector>
#include <map>
#include "Token.h"

struct FunctionDef
{
    std::vector<std::string> params;
    std::vector<Token> body; 
};

class Interpreter
{
public:
    double run(const std::string& line);

private:
    std::vector<Token> tokens;
    size_t pos = 0;

    std::map<std::string, double> variables;
    std::map<std::string, FunctionDef> functions;

    const Token& current();
    void advance();
    bool match(TokenType type);

    double parseExpression();
    double parseTerm();
    double parseFactor();

    double callUserFunction(const std::string& name, const std::vector<double>& args);
    void parseDef();
};