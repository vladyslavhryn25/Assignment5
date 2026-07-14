#pragma once
#include <string>

enum class TokenType
{
    Number,
    Identifier,
    Plus,
    Minus,
    Star,
    Slash,
    LParen,
    RParen,
    Comma,
    LBrace,
    RBrace,
    Assign,
    End
};

struct Token
{
    TokenType type;
    std::string text;
    double value = 0.0;
};