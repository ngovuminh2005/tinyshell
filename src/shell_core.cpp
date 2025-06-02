#include "../include/shell_core.hpp"
#include <iostream>
#include <string>
#include <filesystem>
#include <cstdlib> // For getenv
#include <algorithm> // Added for std::all_of

namespace g1_tinyshell
{

ShellCore::ShellCore()
    : m_environment(), // Initialize environment
      m_executor(m_environment, *this), // Initialize executor with environment and self
      m_shouldExit(false)
{
    // Initialize exit status $? to 0
    m_environment.setVariable("?", "0");
}

void ShellCore::run()
{
    while (!m_shouldExit)
    {
        displayPrompt();
        std::string line = readLine();

        if (line.empty()) // Handle empty input (e.g., just pressing Enter)
        {
            continue;
        }

        addToHistory(line);

        // --- Lexing ---
        Lexer lexer(line);
        std::vector<Token> tokens = lexer.tokenize();

        // Check for lexer errors (e.g., unclosed quotes)
        if (!tokens.empty() && tokens.back().type == TokenType::Error)
        {
            std::cerr << "Tinyshell: Lexer error: " << tokens.back().value << std::endl;
            m_environment.setVariable("?", "1"); // Set error status
            continue; // Skip parsing and execution
        }
        // Remove EOI token if present before parsing
        if (!tokens.empty() && tokens.back().type == TokenType::EndOfInput)
        {
             tokens.pop_back();
        }
        // Skip processing if only comments or whitespace resulted in no significant tokens
        if (tokens.empty() || std::all_of(tokens.begin(), tokens.end(), [](const Token& t){ return t.type == TokenType::Comment; }))
        {
            continue;
        }


        // --- Parsing ---
        Parser parser(tokens);
        AstNodePtr ast_root = parser.parse();

        if (!ast_root)
        {
            std::cerr << "Tinyshell: Parser error: " << parser.getErrorMessage() << std::endl;
            m_environment.setVariable("?", "2"); // Use 2 for syntax errors like bash
            continue; // Skip execution
        }

        // --- Execution ---
        ExecutionResult result = m_executor.execute(ast_root);

        if (!result.error_message.empty())
        {
            std::cerr << "Tinyshell: " << result.error_message << std::endl;
        }

        // Exit status is set within the executor/builtins
    }
}

std::string ShellCore::readLine()
{
    std::string line;
    if (!std::getline(std::cin, line))
    {
        // Handle EOF (Ctrl+D)
        if (std::cin.eof())
        {
            std::cout << std::endl; // Print newline for clean exit
            requestExit();
            return "exit"; // Return "exit" to trigger exit logic cleanly
        }
        // Handle other potential input errors
        else if (std::cin.fail() || std::cin.bad())
        {
             std::cerr << "Tinyshell: Input error." << std::endl;
             requestExit(); // Exit on input error
             return "exit";
        }
    }
    return line;
}

void ShellCore::displayPrompt()
{
    std::error_code ec;
    std::filesystem::path current_path = std::filesystem::current_path(ec);
    std::string path_segment = "?"; // Default if path cannot be determined
    if (!ec)
    {
        path_segment = current_path.filename().string();
        if (path_segment.empty())
        {
             path_segment = "/"; // Handle root directory case
        }
    }

    // Basic prompt without color first
    // std::cout << "G1-HybridShell " << path_segment << " $ " << std::flush;

    // Prompt with optional color
    std::cout << K_DefaultPromptColor << "unitedshell " << K_ResetColor
              << K_PathPromptColor << path_segment << K_ResetColor
              << " $ " << std::flush;
}

void ShellCore::addToHistory(const std::string& command_line)
{
    if (command_line.empty() || (m_commandHistory.empty() && command_line.find_first_not_of(" \t\n\v\f\r") == std::string::npos) || (!m_commandHistory.empty() && command_line == m_commandHistory.back()))
    {
        // Avoid adding empty lines or consecutive duplicates
        return;
    }

    m_commandHistory.push_back(command_line);
    // Limit history size
    if (m_commandHistory.size() > K_MaxHistorySize)
    {
        m_commandHistory.pop_front();
    }
}

const std::deque<std::string>& ShellCore::getHistory() const
{
    return m_commandHistory;
}

void ShellCore::requestExit()
{
    m_shouldExit = true;
}

Environment& ShellCore::getEnvironment()
{
    return m_environment;
}

}

