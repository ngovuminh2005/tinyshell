#pragma once

#include "tinyshell_globals.hpp"
#include "lexer.hpp"
#include <vector>
#include <string>
#include <memory>
#include <variant>

namespace g1_tinyshell
{

// --- Abstract Syntax Tree (AST) Node Definitions ---

// Base class (optional, could use std::variant directly)
struct AstNodeBase
{
    virtual ~AstNodeBase() = default;
};

// Represents a simple command like `ls -l` or `echo hello`
struct SimpleCommandNode : AstNodeBase
{
    std::string command;
    std::vector<std::string> arguments;
};

// Represents a sequence of commands, e.g., commands separated by ';'
struct CommandSequenceNode : AstNodeBase
{
    std::vector<std::shared_ptr<AstNodeBase>> commands;
};

// Represents an if-then-else structure
struct IfNode : AstNodeBase
{
    std::shared_ptr<AstNodeBase> condition_command; // Command whose exit status is checked
    std::shared_ptr<AstNodeBase> then_branch;       // Command sequence for 'then'
    std::vector<std::pair<std::shared_ptr<AstNodeBase>, std::shared_ptr<AstNodeBase>>> elif_branches; // Condition and body for elif
    std::shared_ptr<AstNodeBase> else_branch;       // Optional command sequence for 'else'
};

// Represents a while loop
struct WhileNode : AstNodeBase
{
    std::shared_ptr<AstNodeBase> condition_command;
    std::shared_ptr<AstNodeBase> body;
};

// Represents a for loop
struct ForNode : AstNodeBase
{
    std::string variable_name;
    std::vector<std::string> word_list; // Words to iterate over
    std::shared_ptr<AstNodeBase> body;
};

// Use std::variant to hold different node types
// Using shared_ptr to manage lifetime and allow recursive structures
using AstNodePtr = std::shared_ptr<AstNodeBase>;

// --- Parser Class Definition ---

class Parser
{
public:
    Parser(const std::vector<Token>& tokens);

    // Parses the entire sequence of tokens into a top-level command sequence
    AstNodePtr parse();

    const std::string& getErrorMessage() const;

private:
    std::vector<Token> m_tokens;
    size_t m_currentTokenIndex;
    std::string m_errorMessage;

    // Helper methods for parsing different structures
    AstNodePtr parseCommandSequence(); // Parses commands separated by ';'
    AstNodePtr parseCommand();         // Parses a single command (simple, if, while, for)
    AstNodePtr parseSimpleCommand();
    AstNodePtr parseIfCommand();
    AstNodePtr parseWhileCommand();
    AstNodePtr parseForCommand();

    // Token manipulation helpers
    const Token& currentToken() const;
    const Token& peekToken(size_t offset = 1) const;
    void advanceToken();
    bool matchToken(TokenType type);
    bool expectToken(TokenType type, const std::string& error_context);
    bool isAtEnd() const;

    void setError(const std::string& message);
};

}

