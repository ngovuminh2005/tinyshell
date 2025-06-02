#include "../include/parser_ast.hpp"
#include <stdexcept> // For potential errors, though we use setError
#include <algorithm> // Ensure this is included for std::remove_if
#include <string>    // Ensure std::to_string is available

namespace g1_tinyshell
{

Parser::Parser(const std::vector<Token>& tokens)
    : m_tokens(tokens), m_currentTokenIndex(0), m_errorMessage("")
{
    // Filter out comments before parsing
    // Ensure std::remove_if is used correctly
    m_tokens.erase(std::remove_if(m_tokens.begin(), m_tokens.end(),
                                  [](const Token& t){ return t.type == TokenType::Comment; }),
                   m_tokens.end());
}

AstNodePtr Parser::parse()
{
    m_currentTokenIndex = 0;
    m_errorMessage = "";
    if (isAtEnd() || currentToken().type == TokenType::EndOfInput)
    {
        // Handle empty input gracefully
        return std::make_shared<CommandSequenceNode>(); // Empty sequence
    }
    auto sequence = parseCommandSequence();
    if (!m_errorMessage.empty())
    {
        // Return null or a special error node if parsing failed
        return nullptr;
    }
    if (!isAtEnd() && currentToken().type != TokenType::EndOfInput)
    {
        setError("Unexpected token after command sequence: " + currentToken().value);
        return nullptr;
    }
    return sequence;
}

const std::string& Parser::getErrorMessage() const
{
    return m_errorMessage;
}

// Parses sequences like: cmd1 ; cmd2 ; cmd3
AstNodePtr Parser::parseCommandSequence()
{
    auto sequence_node = std::make_shared<CommandSequenceNode>();
    while (!isAtEnd() && currentToken().type != TokenType::EndOfInput &&
           currentToken().type != TokenType::Fi && currentToken().type != TokenType::Else &&
           currentToken().type != TokenType::Elif && currentToken().type != TokenType::Done)
    {
        AstNodePtr command = parseCommand();
        if (!command)
        {
            // Error occurred during command parsing
            return nullptr;
        }
        sequence_node->commands.push_back(command);

        // Expect semicolon or end of sequence/block
        if (matchToken(TokenType::Semicolon))
        {
            // Consume semicolon, continue if more commands in sequence
            advanceToken(); // Consume the semicolon
            if (isAtEnd() || currentToken().type == TokenType::EndOfInput ||
                currentToken().type == TokenType::Fi || currentToken().type == TokenType::Else ||
                currentToken().type == TokenType::Elif || currentToken().type == TokenType::Done)
            {
                break; // End of sequence/block after semicolon
            }
        }
        else if (isAtEnd() || currentToken().type == TokenType::EndOfInput ||
                 currentToken().type == TokenType::Fi || currentToken().type == TokenType::Else ||
                 currentToken().type == TokenType::Elif || currentToken().type == TokenType::Done)
        {
            break; // Natural end of sequence/block
        }
        else
        {
            // If it's not a semicolon and not the end of a block, it's an error
            // unless we support other separators like && or || later.
            // Corrected setError call with semicolon inside the string:
            setError("Expected ';' or end of command block, found: " + currentToken().value);
            return nullptr;
        }
    }
    return sequence_node;
}

// Parses a single command unit (Simple, If, While, For)
AstNodePtr Parser::parseCommand()
{
    if (isAtEnd()) return nullptr;

    switch (currentToken().type)
    {
        case TokenType::If:
            return parseIfCommand();
        case TokenType::While:
            return parseWhileCommand();
        case TokenType::For:
            return parseForCommand();
        case TokenType::Word:
        case TokenType::Variable: // Variables might start a command name after expansion
            // Assume it's a simple command if it starts with a word or variable
            return parseSimpleCommand();
        default:
            // Handle cases like lone operators or unexpected tokens
            setError("Unexpected token at start of command: " + currentToken().value);
            return nullptr;
    }
}

AstNodePtr Parser::parseSimpleCommand()
{
    auto command_node = std::make_shared<SimpleCommandNode>();
    // Allow Variable as command name start, expansion happens later
    if (currentToken().type != TokenType::Word && currentToken().type != TokenType::Variable) {
        setError("Expected command name (word or variable), found: " + currentToken().value);
        return nullptr;
    }

    command_node->command = currentToken().value;
    advanceToken();

    // Collect arguments until a semicolon, EOI, or control flow keyword
    while (!isAtEnd() && currentToken().type != TokenType::EndOfInput &&
           currentToken().type != TokenType::Semicolon &&
           currentToken().type != TokenType::Fi && currentToken().type != TokenType::Else &&
           currentToken().type != TokenType::Elif && currentToken().type != TokenType::Done &&
           currentToken().type != TokenType::Then && // Should be handled by control flow parsers
           currentToken().type != TokenType::Do)
    {
        // For now, treat all subsequent words/variables as arguments
        // Redirection/piping would need more complex handling here
        if (currentToken().type == TokenType::Word || currentToken().type == TokenType::Variable)
        {
            command_node->arguments.push_back(currentToken().value);
            advanceToken();
        }
        else
        {
            // Unexpected token within a simple command
            setError("Unexpected token in simple command arguments: " + currentToken().value);
            return nullptr;
        }
    }

    return command_node;
}

AstNodePtr Parser::parseIfCommand()
{
    auto if_node = std::make_shared<IfNode>();
    if (!expectToken(TokenType::If, "if statement")) return nullptr;
    advanceToken(); // Consume 'if'

    // Parse condition command sequence
    if_node->condition_command = parseCommandSequence();
    if (!if_node->condition_command) return nullptr;

    if (!expectToken(TokenType::Then, "if condition")) return nullptr;
    advanceToken(); // Consume 'then'

    // Parse 'then' branch command sequence
    if_node->then_branch = parseCommandSequence();
    if (!if_node->then_branch) return nullptr;

    // Parse optional 'elif' branches
    while (matchToken(TokenType::Elif))
    {
        advanceToken(); // Consume 'elif'
        AstNodePtr elif_condition = parseCommandSequence();
        if (!elif_condition) return nullptr;

        if (!expectToken(TokenType::Then, "elif condition")) return nullptr;
        advanceToken(); // Consume 'then'

        AstNodePtr elif_body = parseCommandSequence();
        if (!elif_body) return nullptr;

        if_node->elif_branches.push_back({elif_condition, elif_body});
    }

    // Parse optional 'else' branch
    if (matchToken(TokenType::Else))
    {
        advanceToken(); // Consume 'else'
        if_node->else_branch = parseCommandSequence();
        if (!if_node->else_branch) return nullptr;
    }

    if (!expectToken(TokenType::Fi, "if statement body")) return nullptr;
    advanceToken(); // Consume 'fi'

    return if_node;
}

AstNodePtr Parser::parseWhileCommand()
{
    auto while_node = std::make_shared<WhileNode>();
    if (!expectToken(TokenType::While, "while statement")) return nullptr;
    advanceToken(); // Consume 'while'

    // Parse condition command sequence
    while_node->condition_command = parseCommandSequence();
    if (!while_node->condition_command) return nullptr;

    if (!expectToken(TokenType::Do, "while condition")) return nullptr;
    advanceToken(); // Consume 'do'

    // Parse body command sequence
    while_node->body = parseCommandSequence();
    if (!while_node->body) return nullptr;

    if (!expectToken(TokenType::Done, "while body")) return nullptr;
    advanceToken(); // Consume 'done'

    return while_node;
}

AstNodePtr Parser::parseForCommand()
{
    auto for_node = std::make_shared<ForNode>();
    if (!expectToken(TokenType::For, "for statement")) return nullptr;
    advanceToken(); // Consume 'for'

    // Variable name must be a Word token
    if (!expectToken(TokenType::Word, "for variable name")) return nullptr;
    for_node->variable_name = currentToken().value;
    advanceToken(); // Consume variable name

    if (!expectToken(TokenType::In, "for variable")) return nullptr;
    advanceToken(); // Consume 'in'

    // Collect words for the list until 'do' or ';'
    while (!isAtEnd() && currentToken().type != TokenType::Do && currentToken().type != TokenType::Semicolon)
    {
        if (currentToken().type == TokenType::Word || currentToken().type == TokenType::Variable)
        {
            for_node->word_list.push_back(currentToken().value);
            advanceToken();
        }
        else
        {
            setError("Expected word or variable in 'for' list, found: " + currentToken().value);
            return nullptr;
        }
    }

    // Optional semicolon after word list
    if (matchToken(TokenType::Semicolon))
    {
        advanceToken();
    }

    if (!expectToken(TokenType::Do, "for word list")) return nullptr;
    advanceToken(); // Consume 'do'

    // Parse body command sequence
    for_node->body = parseCommandSequence();
    if (!for_node->body) return nullptr;

    if (!expectToken(TokenType::Done, "for body")) return nullptr;
    advanceToken(); // Consume 'done'

    return for_node;
}

// --- Token manipulation helpers ---

const Token& Parser::currentToken() const
{
    if (isAtEnd())
    {
        // Return a static EndOfInput token to avoid out-of-bounds
        static Token eoi_token = {TokenType::EndOfInput, "", m_tokens.empty() ? 0 : m_tokens.back().position + m_tokens.back().value.length()};
        return eoi_token;
    }
    return m_tokens[m_currentTokenIndex];
}

const Token& Parser::peekToken(size_t offset) const
{
    if (m_currentTokenIndex + offset >= m_tokens.size())
    {
        static Token eoi_token = {TokenType::EndOfInput, "", m_tokens.empty() ? 0 : m_tokens.back().position + m_tokens.back().value.length()};
        return eoi_token;
    }
    return m_tokens[m_currentTokenIndex + offset];
}

void Parser::advanceToken()
{
    if (!isAtEnd())
    {
        m_currentTokenIndex++;
    }
}

bool Parser::matchToken(TokenType type)
{
    return !isAtEnd() && currentToken().type == type;
}

bool Parser::expectToken(TokenType type, const std::string& error_context)
{
    if (isAtEnd() || currentToken().type != type)
    {
        std::string expected_type_str; // Convert TokenType enum to string if needed
        // Basic conversion for error message
        switch(type) {
            case TokenType::Word: expected_type_str = "word"; break;
            case TokenType::Variable: expected_type_str = "variable"; break; // Added
            case TokenType::If: expected_type_str = "'if'"; break;
            case TokenType::Then: expected_type_str = "'then'"; break;
            case TokenType::Elif: expected_type_str = "'elif'"; break;
            case TokenType::Else: expected_type_str = "'else'"; break;
            case TokenType::Fi: expected_type_str = "'fi'"; break;
            case TokenType::While: expected_type_str = "'while'"; break;
            case TokenType::Do: expected_type_str = "'do'"; break;
            case TokenType::Done: expected_type_str = "'done'"; break;
            case TokenType::For: expected_type_str = "'for'"; break;
            case TokenType::In: expected_type_str = "'in'"; break;
            case TokenType::Semicolon: expected_type_str = "';'"; break; // Corrected string literal
            default: expected_type_str = "specific token";
        }
        // Ensure std::to_string is available and used correctly
        setError("Parser error: Expected " + expected_type_str + " for " + error_context +
                 ", but found '" + currentToken().value + "' (type " +
                 std::to_string(static_cast<int>(currentToken().type)) + ")");
        return false;
    }
    return true;
}

bool Parser::isAtEnd() const
{
    // Consider EndOfInput as the end
    return m_currentTokenIndex >= m_tokens.size() || m_tokens[m_currentTokenIndex].type == TokenType::EndOfInput;
}

void Parser::setError(const std::string& message)
{
    if (m_errorMessage.empty()) // Only record the first error
    {
        m_errorMessage = message;
    }
}

}

