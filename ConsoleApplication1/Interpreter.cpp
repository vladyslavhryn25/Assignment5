#include "Interpreter.h"
#include "Lexer.h"
#include <stdexcept>
#include <cmath>
#include <algorithm>

const Token& Interpreter::current()
{
    return tokens[pos];
}

void Interpreter::advance()
{
    pos++;
}

bool Interpreter::match(TokenType type)
{
    if (current().type == type)
    {
        advance();
        return true;
    }
    return false;
}

double Interpreter::parseFactor()
{
    if (current().type == TokenType::Number)
    {
        double value = current().value;
        advance();
        return value;
    }

    if (current().type == TokenType::LParen)
    {
        advance();
        double value = parseExpression();
        if (!match(TokenType::RParen))
            throw std::runtime_error("Expected ')'");
        return value;
    }

    if (current().type == TokenType::Identifier)
    {
        std::string name = current().text;
        advance();

    
        if (current().type == TokenType::LParen)
        {
            advance();
            std::vector<double> args;

            if (current().type != TokenType::RParen)
            {
                args.push_back(parseExpression());
                while (match(TokenType::Comma))
                    args.push_back(parseExpression());
            }

            if (!match(TokenType::RParen))
                throw std::runtime_error("Expected ')'");

            if (name == "pow")
            {
                if (args.size() != 2) throw std::runtime_error("pow needs 2 arguments");
                return std::pow(args[0], args[1]);
            }
            if (name == "abs")
            {
                if (args.size() != 1) throw std::runtime_error("abs needs 1 argument");
                return std::fabs(args[0]);
            }
            if (name == "max")
            {
                if (args.size() != 2) throw std::runtime_error("max needs 2 arguments");
                return std::max(args[0], args[1]);
            }
            if (name == "min")
            {
                if (args.size() != 2) throw std::runtime_error("min needs 2 arguments");
                return std::min(args[0], args[1]);
            }

            throw std::runtime_error("Unknown function: " + name);
        }

       
        if (variables.count(name) == 0)
            throw std::runtime_error("Unknown variable: " + name);
        return variables[name];
    }

    throw std::runtime_error("Unexpected token: " + current().text);
}

double Interpreter::parseTerm()
{
    double left = parseFactor();

    while (current().type == TokenType::Star || current().type == TokenType::Slash)
    {
        bool isMultiply = current().type == TokenType::Star;
        advance();
        double right = parseFactor();
        left = isMultiply ? left * right : left / right;
    }

    return left;
}

double Interpreter::parseExpression()
{
    double left = parseTerm();

    while (current().type == TokenType::Plus || current().type == TokenType::Minus)
    {
        bool isPlus = current().type == TokenType::Plus;
        advance();
        double right = parseTerm();
        left = isPlus ? left + right : left - right;
    }

    return left;
}

double Interpreter::run(const std::string& line)
{
    Lexer lexer(line);
    tokens = lexer.tokenize();
    pos = 0;

  
    if (current().type == TokenType::Identifier && current().text == "var")
    {
        advance();

        if (current().type != TokenType::Identifier)
            throw std::runtime_error("Expected variable name after 'var'");
        std::string name = current().text;
        advance();

        if (!match(TokenType::Assign))
            throw std::runtime_error("Expected '=' after variable name");

        if (variables.count(name) > 0)
            throw std::runtime_error("Variable '" + name + "' is already defined");

        double value = parseExpression();
        variables[name] = value;
        return value;
    }

    return parseExpression();
}