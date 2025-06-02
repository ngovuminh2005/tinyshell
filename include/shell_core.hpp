#pragma once

#include "tinyshell_globals.hpp"
#include "environment.hpp"
#include "lexer.hpp"
#include "parser_ast.hpp"
#include "executor.hpp"
#include <string>
#include <vector>
#include <deque> // Use deque for efficient history management

namespace g1_tinyshell
{

class ShellCore
{
public:
    ShellCore();

    // Starts the main Read-Eval-Print Loop (REPL).
    void run();

    // Adds a command line to the history.
    void addToHistory(const std::string& command_line);

    // Retrieves the command history.
    const std::deque<std::string>& getHistory() const;

    // Signals the REPL to stop.
    void requestExit();

    // Provides access to the environment (needed by builtins via executor).
    Environment& getEnvironment(); // Non-const access needed for setvar etc.

private:
    Environment m_environment;
    Executor m_executor;
    std::deque<std::string> m_commandHistory;
    bool m_shouldExit;

    // Reads a line of input from the user.
    std::string readLine();

    // Displays the shell prompt.
    void displayPrompt();
};

}

