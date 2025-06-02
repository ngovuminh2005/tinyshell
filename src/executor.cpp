#include "../include/executor.hpp"
#include "../include/shell_core.hpp"
#include "../include/expansion.hpp"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <variant>
#include <algorithm> // For std::all_of if needed, or remove

namespace g1_tinyshell
{

Executor::Executor(Environment& environment, ShellCore& shell_core)
    : m_environment(environment), m_shellCore(shell_core)
{
}

void Executor::setLastExitStatus(int status)
{
    m_environment.setVariable("?", std::to_string(status));
}

ExecutionResult Executor::execute(AstNodePtr node)
{
    if (!node)
    {
        return {1, "Internal error: Null AST node passed to executor.", true};
    }

    if (auto simple_cmd = std::dynamic_pointer_cast<SimpleCommandNode>(node))
    {
        return executeSimpleCommand(*simple_cmd);
    }
    else if (auto sequence_cmd = std::dynamic_pointer_cast<CommandSequenceNode>(node))
    {
        return executeCommandSequence(*sequence_cmd);
    }
    else if (auto if_cmd = std::dynamic_pointer_cast<IfNode>(node))
    {
        return executeIfNode(*if_cmd);
    }
    else if (auto while_cmd = std::dynamic_pointer_cast<WhileNode>(node))
    {
        return executeWhileNode(*while_cmd);
    }
    else if (auto for_cmd = std::dynamic_pointer_cast<ForNode>(node))
    {
        return executeForNode(*for_cmd);
    }
    else
    {
        return {1, "Internal error: Unknown AST node type encountered.", true};
    }
}

ExecutionResult Executor::executeSimpleCommand(const SimpleCommandNode& node)
{
    std::string command_name = node.command;
    std::vector<std::string> arguments = node.arguments;
    std::string expansion_error;

    if (!command_name.empty() && command_name[0] == '$')
    {
        command_name = Expansion::expandWord(command_name, m_environment, expansion_error);
        if (!expansion_error.empty())
        {
            setLastExitStatus(1);
            return {1, "Error expanding command name: " + expansion_error, true};
        }
    }
    if (command_name.empty())
    {
         return {0, "", true};
    }

    if (!Expansion::expandArguments(arguments, m_environment, expansion_error))
    {
        setLastExitStatus(1);
        return {1, "Error expanding arguments: " + expansion_error, true};
    }

    BuiltinCommandType builtin_type = Builtins::getBuiltinType(command_name);
    if (builtin_type != BuiltinCommandType::Unknown)
    {
        CommandInfo cmd_info;
        cmd_info.type = CommandType::Builtin;
        cmd_info.command_name = command_name;
        cmd_info.builtin_type = builtin_type;

        if (command_name == "cd") {
            if (arguments.empty()) {
                cmd_info.arguments = {}; // cd không có đối số
            } else {
                // Ghép tất cả các arguments lại thành một đường dẫn duy nhất cho cd
                // nếu người dùng không dùng dấu nháy kép cho đường dẫn có khoảng trắng.
                std::string combined_path;
                for (size_t i = 0; i < arguments.size(); ++i) {
                    combined_path += arguments[i];
                    if (i < arguments.size() - 1) {
                        combined_path += " "; // Thêm lại khoảng trắng
                    }
                }
                cmd_info.arguments = {combined_path};
            }
        } else {
            cmd_info.arguments = arguments;
        }

        ExecutionResult result = Builtins::executeBuiltin(cmd_info, m_environment, m_shellCore);
        setLastExitStatus(result.exit_status);
        return result;
    }
    else
    {
        ExecutionResult result = executeExternalCommand(command_name, arguments);
        setLastExitStatus(result.exit_status);
        return result;
    }
}

ExecutionResult Executor::executeCommandSequence(const CommandSequenceNode& node)
{
    ExecutionResult last_result = {0, "", true};
    for (const auto& command_node : node.commands)
    {
        last_result = execute(command_node);
        if (!last_result.continue_shell)
        {
            return last_result;
        }
    }
    return last_result;
}

ExecutionResult Executor::executeIfNode(const IfNode& node)
{
    ExecutionResult condition_result = execute(node.condition_command);
    if (!condition_result.continue_shell) return condition_result;

    if (condition_result.exit_status == 0)
    {
        return execute(node.then_branch);
    }
    else
    {
        for (const auto& elif_pair : node.elif_branches)
        {
            ExecutionResult elif_condition_result = execute(elif_pair.first);
            if (!elif_condition_result.continue_shell) return elif_condition_result;

            if (elif_condition_result.exit_status == 0)
            {
                return execute(elif_pair.second);
            }
        }
        if (node.else_branch)
        {
            return execute(node.else_branch);
        }
    }
    setLastExitStatus(0);
    return {0, "", true};
}

ExecutionResult Executor::executeWhileNode(const WhileNode& node)
{
    ExecutionResult last_body_result = {0, "", true};
    while (true)
    {
        ExecutionResult condition_result = execute(node.condition_command);
        if (!condition_result.continue_shell) return condition_result;

        if (condition_result.exit_status != 0)
        {
            break;
        }
        last_body_result = execute(node.body);
        if (!last_body_result.continue_shell) return last_body_result;
    }
    return last_body_result;
}

ExecutionResult Executor::executeForNode(const ForNode& node)
{
    ExecutionResult last_body_result = {0, "", true};
    std::string expansion_error;
    std::vector<std::string> expanded_words;
    for (const std::string& word : node.word_list)
    {
        std::string expanded_word = Expansion::expandWord(word, m_environment, expansion_error);
        if (!expansion_error.empty())
        {
             setLastExitStatus(1);
             return {1, "Error expanding word list in for loop: " + expansion_error, true};
        }
        expanded_words.push_back(expanded_word);
    }

    std::optional<std::string> original_value = m_environment.getVariable(node.variable_name);

    for (const std::string& word_value : expanded_words)
    {
        m_environment.setVariable(node.variable_name, word_value);
        last_body_result = execute(node.body);

        if (!last_body_result.continue_shell)
        {
            if (original_value.has_value())
            {
                m_environment.setVariable(node.variable_name, original_value.value());
            }
            else
            {
                m_environment.unsetVariable(node.variable_name);
            }
            return last_body_result;
        }
    }

    if (original_value.has_value())
    {
        m_environment.setVariable(node.variable_name, original_value.value());
    }
    else
    {
        m_environment.unsetVariable(node.variable_name);
    }
    return last_body_result;
}

ExecutionResult Executor::executeExternalCommand(const std::string& command, const std::vector<std::string>& arguments)
{
    std::stringstream command_stream;
    command_stream << command;
    for (const auto& arg : arguments)
    {
        bool needs_quotes = arg.find_first_of(" \t\n\v\f\r\"") != std::string::npos || arg.empty();
        command_stream << " ";
        if (needs_quotes) command_stream << "\"";
        for (char c : arg)
        {
            if (c == '"' || c == '\\') { // Escape " and \ for system command
                command_stream << '\\';
            }
            command_stream << c;
        }
        if (needs_quotes) command_stream << "\"";
    }

    std::string full_command = command_stream.str();
    int system_ret = std::system(full_command.c_str());
    int exit_status = 0;
    std::string error_message = "";

    if (system_ret == -1)
    {
        exit_status = 1;
        error_message = "Failed to execute command: " + command;
    }
    else
    {
#ifdef __linux__
        if (WIFEXITED(system_ret)) { exit_status = WEXITSTATUS(system_ret); }
        else { exit_status = 127; }
#else
        exit_status = system_ret;
#endif
    }
    if (exit_status == 127)
    {
        error_message = command + ": command not found";
    }
    return {exit_status, error_message, true};
}

}