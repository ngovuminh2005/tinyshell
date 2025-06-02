#pragma once

#include "tinyshell_globals.hpp"
#include "parser_ast.hpp"
#include "environment.hpp"
#include "builtins.hpp"
#include <memory> // For shared_ptr

namespace g1_tinyshell
{

// Forward declaration
class ShellCore;

class Executor
{
public:
    Executor(Environment& environment, ShellCore& shell_core);

    // Executes a parsed AST node.
    ExecutionResult execute(AstNodePtr node);

private:
    Environment& m_environment; // Reference to the shell's environment
    ShellCore& m_shellCore;     // Reference to the shell core for history, exit status etc.

    // Specific execution handlers for different AST node types
    ExecutionResult executeSimpleCommand(const SimpleCommandNode& node);
    ExecutionResult executeCommandSequence(const CommandSequenceNode& node);
    ExecutionResult executeIfNode(const IfNode& node);
    ExecutionResult executeWhileNode(const WhileNode& node);
    ExecutionResult executeForNode(const ForNode& node);

    // Helper to execute external commands
    ExecutionResult executeExternalCommand(const std::string& command, const std::vector<std::string>& arguments);

    // Helper to update the last exit status ($?)
    void setLastExitStatus(int status);
};

}

