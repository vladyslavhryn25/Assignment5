#include "Lexer.h"
#include <cctype>
#include <stdexcept>

Lexer::Lexer(const std::string& source) : source(source) {}

bool Lexer::isAtEnd() const
{
    return pos >= source.size();
}

char Lexer::peek() const
{
    if (isAtEnd()) return '\0';
    return source[pos];
}

char Lexer::advance()
{
    return source[pos++];
}

Token Lexer::readNumber()
{
    size_t start = pos;
    while (!isAtEnd() && (std::isdigit(peek()) || peek() == '.'))
        advance();

    std::string text = source.substr(start, pos - start);

    Token token;
    token.type = TokenType::Number;
    token.text = text;
    token.value = std::stod(text);
    return token;
}

Token Lexer::readIdentifier()
{
    size_t start = pos;
    while (!isAtEnd() && (std::isalnum(peek()) || peek() == '_'))
        advance();

    Token token;
    token.type = TokenType::Identifier;
    token.text = source.substr(start, pos - start);
    return token;
}

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;

    while (!isAtEnd())
    {
        char c = peek();

        if (std::isspace(c)) { advance(); continue; }
        if (std::isdigit(c)) { tokens.push_back(readNumber()); continue; }
        if (std::isalpha(c) || c == '_') { tokens.push_back(readIdentifier()); continue; }

        switch (c)
        {
        case '+': 
            tokens.push_back({ TokenType::Plus, "+" }); advance(); 
            break;
        case '-': 
            tokens.push_back({ TokenType::Minus, "-" }); advance(); 
            break;
        case '*': 
            tokens.push_back({ TokenType::Star, "*" }); advance();
            break;
        case '/':
            tokens.push_back({ TokenType::Slash, "/" }); advance();
            break;
        case '(':
            tokens.push_back({ TokenType::LParen, "(" }); advance();
            break;
        case ')': 
            tokens.push_back({ TokenType::RParen, ")" }); advance(); 
            break;
        case ',': 
            tokens.push_back({ TokenType::Comma, "," }); advance();
            break;
        case '{':
            tokens.push_back({ TokenType::LBrace, "{" }); advance(); 
            break;
        case '}':
            tokens.push_back({ TokenType::RBrace, "}" }); advance(); 
            break;
        case '=': 
            tokens.push_back({ TokenType::Assign, "=" }); advance(); 
            break;
        default:
            throw 
                std::runtime_error(std::string("Unexpected character: ") + c);
        }
    }

    tokens.push_back({ TokenType::End, "" });
    return tokens;
}