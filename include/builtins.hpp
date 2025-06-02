#pragma once

#include "tinyshell_globals.hpp"
#include "environment.hpp"
#include <vector>
#include <string>

namespace g1_tinyshell
{

// Forward declaration
class ShellCore; // Needed for access to history, environment etc.

class Builtins
{
public:
    // Executes a built-in command.
    // Takes the command info, the current environment, and a reference to the shell core.
    // Returns an ExecutionResult indicating success/failure and exit status.
    static ExecutionResult executeBuiltin(const CommandInfo& command_info, Environment& environment, ShellCore& shell_core);

    // Checks if a command name corresponds to a known built-in.
    static BuiltinCommandType getBuiltinType(const std::string& command_name);

    // Provides help text for built-in commands.
    static std::string getHelpText(BuiltinCommandType type);
    static std::string listBuiltins();

private:
    // --- Individual Built-in Implementations ---
    // Each returns an ExecutionResult.

    static ExecutionResult builtinExit(const std::vector<std::string>& args, ShellCore& shell_core);
    static ExecutionResult builtinEcho(const std::vector<std::string>& args);
    static ExecutionResult builtinHelp(const std::vector<std::string>& args);
    static ExecutionResult builtinIntro(const std::vector<std::string>& args);
    static ExecutionResult builtinSetVar(const std::vector<std::string>& args, Environment& environment);
    static ExecutionResult builtinGetVar(const std::vector<std::string>& args, const Environment& environment);
    static ExecutionResult builtinUnsetVar(const std::vector<std::string>& args, Environment& environment);
    static ExecutionResult builtinCd(const std::vector<std::string>& args, Environment& environment);
    static ExecutionResult builtinPwd();
    static ExecutionResult builtinLs(const std::vector<std::string>& args);
    static ExecutionResult builtinMkdir(const std::vector<std::string>& args);
    static ExecutionResult builtinRm(const std::vector<std::string>& args);
    static ExecutionResult builtinCat(const std::vector<std::string>& args);
    static ExecutionResult builtinPath(const Environment& environment);
    static ExecutionResult builtinAddPath(const std::vector<std::string>& args, Environment& environment); // Conceptual
    static ExecutionResult builtinC(const std::vector<std::string>& args);
    static ExecutionResult builtinCpp(const std::vector<std::string>& args);
    static ExecutionResult builtinHistory(const std::vector<std::string>& args, const ShellCore& shell_core);
    static ExecutionResult builtinTest(const std::vector<std::string>& args);
    // static ExecutionResult builtinCatSpin(); // Optional

    // Helper for C/CPP compilation and execution
    static ExecutionResult compileAndRun(const std::string& compiler, const std::string& source_file, const std::vector<std::string>& args);

    // Helper for test command expressions
    static bool evaluateTestExpression(const std::vector<std::string>& expression, std::string& error_msg);
    static bool compareIntegers(long long val1, const std::string& op, long long val2);
};

}

