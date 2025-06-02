#pragma once

#include "tinyshell_globals.hpp"
#include <string>
#include <vector>

namespace g1_tinyshell
{

enum class TokenType
{
    Word,         // Command or argument
    Operator,     // e.g., ';', '&&', '||' (future extension)
    RedirectIn,   // '<'
    RedirectOut,  // '>'
    RedirectAppend,// '>>'
    Pipe,         // '|'
    If,           // 'if'
    Then,         // 'then'
    Elif,         // 'elif'
    Else,         // 'else'
    Fi,           // 'fi'
    While,        // 'while'
    Do,           // 'do'
    Done,         // 'done'
    For,          // 'for'
    In,           // 'in'
    Semicolon,    // ';'
    Background,   // '&' (future extension)
    Variable,     // '$VAR' or '${VAR}' (for expansion phase)
    Comment,      // '#...'
    EndOfInput,
    Error
};

struct Token
{
    TokenType type;
    std::string value;
    size_t position; // Starting position in the original input line
};

class Lexer
{
public:
    Lexer(const std::string& input);

    std::vector<Token> tokenize();

private:
    std::string m_input;
    size_t m_currentPosition;
    std::string m_errorMessage;

    Token getNextToken();
    Token processWord();
    Token processOperatorOrRedirect(); // Placeholder for future operators
    Token processVariable();
    Token processComment();
    Token processQuotedString(char quote_char);

    char peek() const;
    char advance();
    bool isAtEnd() const;
    bool isWhitespace(char c) const;
    bool isOperatorChar(char c) const; // Placeholder
    bool isSpecialChar(char c) const;
};

}

