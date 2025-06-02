#include "../include/lexer.hpp"
#include <iostream>
#include <cctype>
#include <unordered_map>

namespace g1_tinyshell
{

const std::unordered_map<std::string, TokenType> K_Keywords = {
    {"if", TokenType::If}, {"then", TokenType::Then}, {"elif", TokenType::Elif},
    {"else", TokenType::Else}, {"fi", TokenType::Fi}, {"while", TokenType::While},
    {"do", TokenType::Do}, {"done", TokenType::Done}, {"for", TokenType::For},
    {"in", TokenType::In}
};

Lexer::Lexer(const std::string& input)
    : m_input(input), m_currentPosition(0), m_errorMessage("") {}

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;
    m_errorMessage = "";
    m_currentPosition = 0;

    while (!isAtEnd())
    {
        char current_char = peek();

        if (isWhitespace(current_char))
        {
            advance();
            continue;
        }
        if (current_char == '#')
        {
            tokens.push_back(processComment());
            break;
        }
        if (current_char == '\'' || current_char == '"')
        {
            tokens.push_back(processQuotedString(current_char));
        }
        else if (isSpecialChar(current_char))
        {
            TokenType type = TokenType::Error;
            std::string val_str(1, current_char);
            if (current_char == ';') type = TokenType::Semicolon;

            if (type != TokenType::Error)
            {
                tokens.push_back({type, val_str, m_currentPosition});
                advance();
            }
            else
            {
                 tokens.push_back(processWord());
            }
        }
        else
        {
            if (current_char == '$') {
                tokens.push_back(processVariable());
            } else {
                tokens.push_back(processWord());
            }
        }

        if (!m_errorMessage.empty())
        {
            if (tokens.empty() || tokens.back().type != TokenType::Error) {
                 tokens.push_back({TokenType::Error, m_errorMessage, m_currentPosition});
            }
            break;
        }
    }
    if (m_errorMessage.empty())
    {
         tokens.push_back({TokenType::EndOfInput, "", m_currentPosition});
    }
    return tokens;
}

Token Lexer::processWord()
{
    size_t start_pos = m_currentPosition;
    std::string word_value;
    while (!isAtEnd())
    {
        char current_char = peek();
        if (isWhitespace(current_char) || isSpecialChar(current_char) ||
            current_char == '#' || current_char == '\'' || current_char == '"' || current_char == '$')
        {
            break;
        }
        // '\' bây giờ được coi là một phần của từ nếu không được trích dẫn,
        // trừ khi nó đứng trước một ký tự mà bạn muốn escape đặc biệt (hiện tại không có)
        word_value += advance();
    }
    auto keyword_it = K_Keywords.find(word_value);
    if (keyword_it != K_Keywords.end())
    {
        return {keyword_it->second, word_value, start_pos};
    }
    return {TokenType::Word, word_value, start_pos};
}

Token Lexer::processVariable()
{
    size_t start_pos = m_currentPosition;
    advance();

    std::string var_name_or_special;
    char next_char = peek();

    if (next_char == '{') {
        advance();
        size_t name_start = m_currentPosition;
        while(!isAtEnd() && peek() != '}') {
            advance();
        }
        if (isAtEnd() || peek() != '}') {
            m_errorMessage = "Lexer error: Unclosed variable brace for ${";
            return {TokenType::Error, m_errorMessage, start_pos};
        }
        var_name_or_special = m_input.substr(name_start, m_currentPosition - name_start);
        advance();
    } else if (next_char == '?') {
        var_name_or_special = "?";
        advance();
    } else if (std::isalpha(next_char) || next_char == '_') {
        size_t name_start = m_currentPosition;
        advance();
        while(!isAtEnd() && (std::isalnum(peek()) || peek() == '_')) {
            advance();
        }
        var_name_or_special = m_input.substr(name_start, m_currentPosition - name_start);
    } else {
        m_currentPosition = start_pos;
        return processWord();
    }

    if (var_name_or_special.empty() && next_char != '?') {
         m_errorMessage = "Lexer error: Empty variable name.";
         return {TokenType::Error, m_errorMessage, start_pos};
    }
    return {TokenType::Variable, var_name_or_special, start_pos};
}

Token Lexer::processQuotedString(char quote_char)
{
    size_t start_pos = m_currentPosition;
    advance();
    std::string value;
    bool found_closing_quote = false;

    while (!isAtEnd())
    {
        char current_char = peek();

        if (current_char == '\\')
        {
            advance();
            if (isAtEnd())
            {
                m_errorMessage = "Lexer error: Dangling backslash at the very end of input.";
                return {TokenType::Error, m_errorMessage, start_pos};
            }
            char next_char = peek();

            if (quote_char == '"') {
                if (next_char == '"' || next_char == '\\' || next_char == '$') {
                    value += advance();
                } else {
                    value += '\\';
                    value += advance();
                }
            } else {
                if (next_char == quote_char || next_char == '\\') {
                    value += advance();
                } else {
                    value += '\\';
                    value += advance();
                }
            }
        }
        else if (current_char == quote_char)
        {
            advance();
            found_closing_quote = true;
            break;
        }
        else
        {
            value += advance();
        }
    }

    if (!found_closing_quote)
    {
        m_errorMessage = "Lexer error: Unclosed quote: " + std::string(1, quote_char);
        return {TokenType::Error, m_errorMessage, start_pos};
    }
    return {TokenType::Word, value, start_pos};
}

Token Lexer::processComment()
{
    size_t start_pos = m_currentPosition;
    std::string comment_text;
    while (!isAtEnd())
    {
        comment_text += advance();
    }
    return {TokenType::Comment, comment_text, start_pos};
}

char Lexer::peek() const
{
    if (isAtEnd()) return '\0';
    return m_input[m_currentPosition];
}

char Lexer::advance()
{
    if (!isAtEnd()) m_currentPosition++;
    return m_input[m_currentPosition - 1];
}

bool Lexer::isAtEnd() const
{
    return m_currentPosition >= m_input.length();
}

bool Lexer::isWhitespace(char c) const
{
    return std::isspace(static_cast<unsigned char>(c));
}

bool Lexer::isSpecialChar(char c) const
{
    switch (c) {
        case ';':
            return true;
        default:
            return false;
    }
}

}