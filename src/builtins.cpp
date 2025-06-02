#include "../include/builtins.hpp"
#include "../include/shell_core.hpp" // Include ShellCore for history access etc.
#include <iostream>
#include <cstdlib> // system, getenv, exit
#include <filesystem> // C++17 filesystem operations
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <cstdio> // std::remove for temp files
#include <limits> // numeric_limits
#include <algorithm> // std::find_if

// Define platform-specific home directory retrieval
#ifdef _WIN32
#define GETENV_HOME "USERPROFILE"
#else
#define GETENV_HOME "HOME"
#endif

namespace g1_tinyshell
{

// --- Built-in Command Mapping ---
const std::map<std::string, BuiltinCommandType> K_BuiltinCommands = {
    {"exit", BuiltinCommandType::Exit},
    {"echo", BuiltinCommandType::Echo},
    {"help", BuiltinCommandType::Help},
    {"intro", BuiltinCommandType::Intro},
    {"setvar", BuiltinCommandType::SetVar},
    {"getvar", BuiltinCommandType::GetVar},
    {"unsetvar", BuiltinCommandType::UnsetVar},
    {"cd", BuiltinCommandType::Cd},
    {"pwd", BuiltinCommandType::Pwd},
    {"ls", BuiltinCommandType::Ls},
    {"mkdir", BuiltinCommandType::Mkdir},
    {"rm", BuiltinCommandType::Rm},
    {"cat", BuiltinCommandType::Cat},
    {"path", BuiltinCommandType::Path},
    {"addpath", BuiltinCommandType::AddPath},
    {"c", BuiltinCommandType::C},
    {"cpp", BuiltinCommandType::Cpp},
    {"history", BuiltinCommandType::History},
    {"test", BuiltinCommandType::Test},
    {"[", BuiltinCommandType::Test} // Alias for test
    // {"cat_spin", BuiltinCommandType::CatSpin} // Optional
};

BuiltinCommandType Builtins::getBuiltinType(const std::string& command_name)
{
    auto it = K_BuiltinCommands.find(command_name);
    if (it != K_BuiltinCommands.end())
    {
        return it->second;
    }
    return BuiltinCommandType::Unknown;
}

ExecutionResult Builtins::executeBuiltin(const CommandInfo& command_info, Environment& environment, ShellCore& shell_core)
{
    switch (command_info.builtin_type)
    {
        case BuiltinCommandType::Exit:    return builtinExit(command_info.arguments, shell_core);
        case BuiltinCommandType::Echo:    return builtinEcho(command_info.arguments);
        case BuiltinCommandType::Help:    return builtinHelp(command_info.arguments);
        case BuiltinCommandType::Intro:   return builtinIntro(command_info.arguments);
        case BuiltinCommandType::SetVar:  return builtinSetVar(command_info.arguments, environment);
        case BuiltinCommandType::GetVar:  return builtinGetVar(command_info.arguments, environment);
        case BuiltinCommandType::UnsetVar:return builtinUnsetVar(command_info.arguments, environment);
        case BuiltinCommandType::Cd:      return builtinCd(command_info.arguments, environment);
        case BuiltinCommandType::Pwd:     return builtinPwd();
        case BuiltinCommandType::Ls:      return builtinLs(command_info.arguments);
        case BuiltinCommandType::Mkdir:   return builtinMkdir(command_info.arguments);
        case BuiltinCommandType::Rm:      return builtinRm(command_info.arguments);
        case BuiltinCommandType::Cat:     return builtinCat(command_info.arguments);
        case BuiltinCommandType::Path:    return builtinPath(environment);
        case BuiltinCommandType::AddPath: return builtinAddPath(command_info.arguments, environment);
        case BuiltinCommandType::C:       return builtinC(command_info.arguments);
        case BuiltinCommandType::Cpp:     return builtinCpp(command_info.arguments);
        case BuiltinCommandType::History: return builtinHistory(command_info.arguments, shell_core);
        case BuiltinCommandType::Test:    return builtinTest(command_info.arguments);
        // case BuiltinCommandType::CatSpin: return builtinCatSpin();
        default: // Should not happen if getBuiltinType is used correctly
            return {1, "Internal error: Unknown built-in type.", true};
    }
}

// --- Individual Built-in Implementations ---

ExecutionResult Builtins::builtinExit(const std::vector<std::string>& args, ShellCore& shell_core)
{
    int exit_code = 0;
    if (!args.empty())
    {
        try
        {
            // Check for non-numeric characters more robustly
            size_t processed_chars = 0;
            exit_code = std::stoi(args[0], &processed_chars);
            if (processed_chars != args[0].length())
            {
                 return {1, "exit: Numeric argument required", true};
            }
        }
        catch (const std::invalid_argument&)
        {
            return {1, "exit: Numeric argument required", true};
        }
        catch (const std::out_of_range&)
        {
            return {1, "exit: Argument out of range", true};
        }
    }
    shell_core.requestExit(); // Signal the shell core to stop the REPL
    return {exit_code, "", false}; // Indicate shell should not continue
}

ExecutionResult Builtins::builtinEcho(const std::vector<std::string>& args)
{
    for (size_t i = 0; i < args.size(); ++i)
    {
        std::cout << args[i];
        if (i < args.size() - 1)
        {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    return {0, "", true};
}

ExecutionResult Builtins::builtinHelp(const std::vector<std::string>& args)
{
    if (args.empty())
    {
        std::cout << listBuiltins() << std::endl;
    }
    else
    {
        BuiltinCommandType type = getBuiltinType(args[0]);
        if (type == BuiltinCommandType::Unknown)
        {
            return {1, "help: no help topics match `" + args[0] + "`", true};
        }
        std::cout << getHelpText(type) << std::endl;
    }
    return {0, "", true};
}

ExecutionResult Builtins::builtinIntro(const std::vector<std::string>& args)
{
    // Basic implementation without color handling for simplicity first
    // Color could be added later based on args[0]
    std::cout << "Tinyshell Project - Group 1:" << std::endl;
    std::cout << "  Đặng Tiến Cường (20220020)" << std::endl;
    std::cout << "  Trần Huy Dương (20230025)" << std::endl;
    std::cout << "  Phạm Gia Hưng (20230036)" << std::endl;
    std::cout << "  Ngô Vũ Minh (20230084)" << std::endl;
    return {0, "", true};
}

ExecutionResult Builtins::builtinSetVar(const std::vector<std::string>& args, Environment& environment)
{
    if (args.empty())
    {
        // Maybe list all variables like shell `set`?
        // For now, require VAR=value format.
        return {1, "setvar: Usage: setvar VAR=value", true};
    }

    std::string assignment = args[0];
    size_t equals_pos = assignment.find("=");

    if (equals_pos == std::string::npos || equals_pos == 0)
    {
        return {1, "setvar: Invalid format. Usage: setvar VAR=value", true};
    }

    std::string var_name = assignment.substr(0, equals_pos);
    std::string value = assignment.substr(equals_pos + 1);

    if (!Environment::isValidVariableName(var_name))
    {
        return {1, "setvar: Invalid variable name: " + var_name, true};
    }

    environment.setVariable(var_name, value);
    return {0, "", true};
}

ExecutionResult Builtins::builtinGetVar(const std::vector<std::string>& args, const Environment& environment)
{
    if (args.size() != 1)
    {
        return {1, "getvar: Usage: getvar VAR", true};
    }
    std::string var_name = args[0];
    if (!Environment::isValidVariableName(var_name))
    {
        // Allow getting invalid names? Maybe not.
        return {1, "getvar: Invalid variable name: " + var_name, true};
    }

    std::optional<std::string> value = environment.getVariable(var_name);
    if (value.has_value())
    {
        std::cout << value.value() << std::endl;
        return {0, "", true};
    }
    else
    {
        // POSIX shells often print nothing and return 0 for unset variables
        // Return error 1 to indicate it wasn't found for clarity in this shell.
        return {1, "getvar: Variable not set: " + var_name, true};
    }
}

ExecutionResult Builtins::builtinUnsetVar(const std::vector<std::string>& args, Environment& environment)
{
    if (args.size() != 1)
    {
        return {1, "unsetvar: Usage: unsetvar VAR", true};
    }
    std::string var_name = args[0];
    if (!Environment::isValidVariableName(var_name))
    {
        return {1, "unsetvar: Invalid variable name: " + var_name, true};
    }

    if (environment.unsetVariable(var_name))
    {
        return {0, "", true};
    }
    else
    {
        // Variable didn't exist, but unsetting is usually idempotent (exit 0)
        return {0, "", true};
    }
}

ExecutionResult Builtins::builtinCd(const std::vector<std::string>& args, Environment& environment)
{
    std::filesystem::path target_path;

    if (args.empty())
    {
        // Go to home directory
        const char* home_dir = std::getenv(GETENV_HOME);
        if (home_dir == nullptr)
        {
            return {1, "cd: HOME directory not set", true};
        }
        target_path = home_dir;
    }
    else if (args.size() == 1)
    {
        target_path = args[0];
    }
    else
    {
        return {1, "cd: Too many arguments", true};
    }

    std::error_code ec;
    std::filesystem::path current_p = std::filesystem::current_path(ec);
    if (ec)
    {
        return {1, "cd: Cannot determine current path: " + ec.message(), true};
    }

    // Resolve target path relative to current path
    // std::filesystem::absolute handles many cases, but be careful with symlinks etc.
    // For simplicity, let current_path handle resolution.
    // std::filesystem::path absolute_target = std::filesystem::absolute(target_path, ec);
    // if (ec) {
    //     return {1, "cd: Cannot resolve path: " + target_path.string() + ": " + ec.message(), true};
    // }

    try
    {
        std::filesystem::current_path(target_path, ec);
        if (ec)
        {
            // Check specific errors if possible
            std::string error_msg = "cd: Cannot change directory to " + target_path.string() + ": " + ec.message();
            // Try to provide more specific common errors
            if (!std::filesystem::exists(target_path, ec))
            {
                 error_msg = "cd: No such file or directory: " + target_path.string();
            }
            else if (!std::filesystem::is_directory(target_path, ec))
            {
                 error_msg = "cd: Not a directory: " + target_path.string();
            }
            return {1, error_msg, true};
        }
        // Update PWD environment variable (optional, but good practice)
        environment.setVariable("PWD", std::filesystem::current_path().string());
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        return {1, "cd: Filesystem error: " + std::string(e.what()), true};
    }

    return {0, "", true};
}

ExecutionResult Builtins::builtinPwd()
{
    std::error_code ec;
    std::filesystem::path current_path = std::filesystem::current_path(ec);
    if (ec)
    {
        return {1, "pwd: Cannot determine current path: " + ec.message(), true};
    }
    std::cout << current_path.string() << std::endl;
    return {0, "", true};
}

ExecutionResult Builtins::builtinLs(const std::vector<std::string>& args)
{
    std::filesystem::path target_path = "."; // Default to current directory
    if (!args.empty())
    {
        target_path = args[0];
    }

    std::error_code ec;
    if (!std::filesystem::exists(target_path, ec) || ec)
    {
        return {1, "ls: Cannot access `" + target_path.string() + "`: No such file or directory", true};
    }
    if (!std::filesystem::is_directory(target_path, ec) || ec)
    {
        // If it's a file, just print its name
        std::cout << target_path.filename().string() << std::endl;
        return {0, "", true};
    }

    try
    {
        for (const auto& entry : std::filesystem::directory_iterator(target_path))
        {
            std::cout << entry.path().filename().string() << std::endl;
        }
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        return {1, "ls: Cannot read directory `" + target_path.string() + "`: " + std::string(e.what()), true};
    }

    return {0, "", true};
}

ExecutionResult Builtins::builtinMkdir(const std::vector<std::string>& args)
{
    if (args.size() != 1)
    {
        return {1, "mkdir: Usage: mkdir <dirname>", true};
    }
    std::filesystem::path dir_path = args[0];
    std::error_code ec;
    if (std::filesystem::create_directory(dir_path, ec))
    {
        return {0, "", true};
    }
    else
    {
        std::string error_msg = "mkdir: Cannot create directory `" + dir_path.string() + "`: " + ec.message();
        if (std::filesystem::exists(dir_path)) // More specific error if it exists
        {
            error_msg = "mkdir: Cannot create directory `" + dir_path.string() + "`: File exists";
        }
        return {1, error_msg, true};
    }
}

ExecutionResult Builtins::builtinRm(const std::vector<std::string>& args)
{
    if (args.size() != 1)
    {
        return {1, "rm: Usage: rm <filename_or_empty_dirname>", true};
    }
    std::filesystem::path path_to_remove = args[0];
    std::error_code ec;

    // Check existence first for a better error message
    if (!std::filesystem::exists(path_to_remove, ec))
    {
        return {1, "rm: Cannot remove `" + path_to_remove.string() + "`: No such file or directory", true};
    }

    // Check if it's a directory and if it's empty (basic check)
    if (std::filesystem::is_directory(path_to_remove, ec))
    {
        if (!std::filesystem::is_empty(path_to_remove, ec))
        {
             return {1, "rm: Cannot remove `" + path_to_remove.string() + "`: Directory not empty", true};
        }
    }
    else if (ec) // Error checking if it's a directory
    {
         return {1, "rm: Cannot check status of `" + path_to_remove.string() + "`: " + ec.message(), true};
    }

    // Attempt removal
    if (std::filesystem::remove(path_to_remove, ec))
    {
        return {0, "", true};
    }
    else
    {
        return {1, "rm: Cannot remove `" + path_to_remove.string() + "`: " + ec.message(), true};
    }
}

ExecutionResult Builtins::builtinCat(const std::vector<std::string>& args)
{
    if (args.size() != 1)
    {
        return {1, "cat: Usage: cat <filename>", true};
    }
    std::filesystem::path file_path = args[0];
    std::error_code ec;

    if (!std::filesystem::exists(file_path, ec) || ec)
    {
        return {1, "cat: `" + file_path.string() + "`: No such file or directory", true};
    }
    if (std::filesystem::is_directory(file_path, ec) || ec)
    {
        return {1, "cat: `" + file_path.string() + "`: Is a directory", true};
    }

    std::ifstream input_file(file_path);
    if (!input_file.is_open())
    {
        return {1, "cat: `" + file_path.string() + "`: Permission denied or other error opening file", true};
    }

    std::string line;
    while (std::getline(input_file, line))
    {
        std::cout << line << std::endl;
    }

    if (input_file.bad())
    {
         return {1, "cat: Error reading file `" + file_path.string() + "`", true};
    }

    return {0, "", true};
}

ExecutionResult Builtins::builtinPath(const Environment& environment)
{
    // Display the system PATH variable
    const char* path_var = std::getenv("PATH");
    if (path_var != nullptr)
    {
        std::cout << path_var << std::endl;
    }
    else
    {
        std::cerr << "path: PATH environment variable not found." << std::endl;
        return {1, "path: PATH environment variable not found.", true};
    }
    return {0, "", true};
}

ExecutionResult Builtins::builtinAddPath(const std::vector<std::string>& args, Environment& environment)
{
    if (args.size() != 1)
    {
        return {1, "addpath: Usage: addpath <directory>", true};
    }
    // This is conceptual: modifies an *internal* variable, maybe named TINYSHELL_PATH?
    // It does NOT reliably modify the system PATH used by std::system().
    std::string dir_to_add = args[0];
    std::error_code ec;
    if (!std::filesystem::exists(dir_to_add, ec) || !std::filesystem::is_directory(dir_to_add, ec))
    {
        // Optional: Check if directory exists
        // return {1, "addpath: Directory not found: " + dir_to_add, true};
    }

    std::optional<std::string> current_tinyshell_path = environment.getVariable("TINYSHELL_PATH");
    std::string new_path;
    if (current_tinyshell_path.has_value() && !current_tinyshell_path.value().empty())
    {
        new_path = current_tinyshell_path.value() + 
#ifdef _WIN32
                   ";"
#else
                   ":"
#endif
                   + dir_to_add;
    }
    else
    {
        new_path = dir_to_add;
    }
    environment.setVariable("TINYSHELL_PATH", new_path);
    std::cerr << "Warning: addpath modifies internal TINYSHELL_PATH, not system PATH used by external commands." << std::endl;
    return {0, "", true};
}

ExecutionResult Builtins::builtinC(const std::vector<std::string>& args)
{
    if (args.empty())
    {
        return {1, "c: Usage: c <source.c> [compile_args...]", true};
    }
    std::string source_file = args[0];
    std::vector<std::string> compile_args(args.begin() + 1, args.end());
    return compileAndRun("gcc", source_file, compile_args);
}

ExecutionResult Builtins::builtinCpp(const std::vector<std::string>& args)
{
    if (args.empty())
    {
        return {1, "cpp: Usage: cpp <source.cpp> [compile_args...]", true};
    }
    std::string source_file = args[0];
    std::vector<std::string> compile_args(args.begin() + 1, args.end());
    return compileAndRun("g++", source_file, compile_args);
}

ExecutionResult Builtins::builtinHistory(const std::vector<std::string>& args, const ShellCore& shell_core)
{
    int count = -1; // Default: show all
    if (!args.empty())
    {
        try
        {
            size_t processed_chars = 0;
            count = std::stoi(args[0], &processed_chars);
            if (processed_chars != args[0].length() || count < 0)
            {
                 return {1, "history: Numeric argument required (non-negative)", true};
            }
        }
        catch (const std::invalid_argument&)
        {
            return {1, "history: Numeric argument required", true};
        }
        catch (const std::out_of_range&)
        {
            return {1, "history: Argument out of range", true};
        }
    }

    const auto& history = shell_core.getHistory();
    int start_index = 0;
    if (count > 0 && static_cast<int>(history.size()) > count)
    {
        start_index = history.size() - count;
    }

    for (size_t i = start_index; i < history.size(); ++i)
    {
        // Consider adding line numbers
        std::cout << "  " << (i + 1) << "  " << history[i] << std::endl;
    }

    return {0, "", true};
}

ExecutionResult Builtins::builtinTest(const std::vector<std::string>& args)
{
    std::vector<std::string> expression = args;
    // Handle `[` alias: requires `]` as last argument
    if (!args.empty() && args[0] == "[")
    {
        if (args.back() != "]")
        {
            return {2, "test: missing `]`", true}; // Use exit code 2 for syntax errors like bash
        }
        expression.erase(expression.begin()); // Remove `[`
        expression.pop_back(); // Remove `]`
    }

    if (expression.empty())
    {
        return {1, "", true}; // Empty expression is false
    }

    std::string error_msg;
    bool result = evaluateTestExpression(expression, error_msg);

    if (!error_msg.empty())
    {
        // std::cerr << "test: " << error_msg << std::endl;
        return {2, "test: " + error_msg, true}; // Syntax or evaluation error
    }

    return {result ? 0 : 1, "", true}; // 0 for true, 1 for false
}

// --- Helper Functions ---

ExecutionResult Builtins::compileAndRun(const std::string& compiler, const std::string& source_file, const std::vector<std::string>& args)
{
    std::error_code ec;
    if (!std::filesystem::exists(source_file, ec) || !std::filesystem::is_regular_file(source_file, ec))
    {
        return {1, compiler + ": Source file not found or is not a regular file: " + source_file, true};
    }

    // Create a temporary executable name
    std::filesystem::path temp_dir = std::filesystem::temp_directory_path(ec);
    if (ec)
    {
        temp_dir = "."; // Fallback to current directory
    }
    std::filesystem::path temp_executable = temp_dir / (std::filesystem::path(source_file).stem().string() + "_temp_exec");
#ifdef _WIN32
    temp_executable += ".exe";
#endif

    // Construct compile command
    std::stringstream compile_command_ss;
    compile_command_ss << compiler << " \"" << source_file << "\" -o \"" << temp_executable.string() << "\"";
    // Add extra compile args if any (simple space separation, no complex quoting handled)
    // This part is basic and might fail with complex arguments.
    // for (const auto& arg : args) { compile_command_ss << " " << arg; }

    // Execute compile command
    int compile_status = std::system(compile_command_ss.str().c_str());
    if (compile_status != 0)
    {
        std::filesystem::remove(temp_executable, ec); // Clean up even if compile failed
        return {compile_status, compiler + ": Compilation failed (exit code: " + std::to_string(compile_status) + ")", true};
    }

    // Construct run command
    std::stringstream run_command_ss;
    run_command_ss << "\"" << temp_executable.string() << "\"";
    // Add runtime args
    for (const auto& arg : args) { run_command_ss << " \"" << arg << "\""; } // Basic quoting for args

    // Execute the compiled program
    int run_status = std::system(run_command_ss.str().c_str());

    // Clean up temporary executable
    std::filesystem::remove(temp_executable, ec);
    // Ignore cleanup error? Maybe log it.

    return {run_status, "", true};
}

// Basic implementation of `test` / `[`
bool Builtins::evaluateTestExpression(const std::vector<std::string>& expression, std::string& error_msg)
{
    if (expression.empty())
    {
        return false; // Empty expression is false
    }

    // Handle unary operators: -e, -f, -d (existence, file, directory)
    if (expression.size() == 2)
    {
        const std::string& op = expression[0];
        const std::string& path_arg = expression[1];
        std::error_code ec;
        if (op == "-e")
        {
            return std::filesystem::exists(path_arg, ec);
        }
        if (op == "-f")
        {
            return std::filesystem::is_regular_file(path_arg, ec);
        }
        if (op == "-d")
        {
            return std::filesystem::is_directory(path_arg, ec);
        }
        error_msg = "Unknown unary operator: " + op;
        return false;
    }

    // Handle binary operators: =, !=, -eq, -ne, -gt, -ge, -lt, -le
    if (expression.size() == 3)
    {
        const std::string& arg1 = expression[0];
        const std::string& op = expression[1];
        const std::string& arg2 = expression[2];

        // String comparison
        if (op == "=" || op == "==")
        {
            return arg1 == arg2;
        }
        if (op == "!=")
        {
            return arg1 != arg2;
        }

        // Integer comparison
        if (op == "-eq" || op == "-ne" || op == "-gt" || op == "-ge" || op == "-lt" || op == "-le")
        {
            try
            {
                size_t pos1 = 0, pos2 = 0;
                long long val1 = std::stoll(arg1, &pos1);
                long long val2 = std::stoll(arg2, &pos2);
                if (pos1 != arg1.length() || pos2 != arg2.length())
                {
                    error_msg = "Integer expression expected: " + arg1 + " or " + arg2;
                    return false;
                }
                return compareIntegers(val1, op, val2);
            }
            catch (const std::exception&)
            {
                error_msg = "Integer expression expected: " + arg1 + " or " + arg2;
                return false;
            }
        }

        error_msg = "Unknown binary operator: " + op;
        return false;
    }

    error_msg = "Invalid test expression";
    return false;
}

bool Builtins::compareIntegers(long long val1, const std::string& op, long long val2)
{
    if (op == "-eq") return val1 == val2;
    if (op == "-ne") return val1 != val2;
    if (op == "-gt") return val1 > val2;
    if (op == "-ge") return val1 >= val2;
    if (op == "-lt") return val1 < val2;
    if (op == "-le") return val1 <= val2;
    return false; // Should not happen if called correctly
}

// --- Help Text Generation ---

std::string Builtins::listBuiltins()
{
    std::stringstream ss;
    ss << "Tinyshell (Group 1) Built-in Commands:\n";
    ss << "  exit [n]         Exit the shell with status n (default 0).\n";
    ss << "  echo [args...]   Write arguments to standard output.\n";
    ss << "  help [cmd]       Display help for built-in command cmd.\n";
    ss << "  intro [color]    Display group information.\n";
    ss << "  setvar VAR=value Set internal shell variable VAR to value.\n";
    ss << "  getvar VAR       Display the value of internal variable VAR.\n";
    ss << "  unsetvar VAR     Unset internal shell variable VAR.\n";
    ss << "  cd [dir]         Change the current directory.\n";
    ss << "  pwd              Print the current working directory.\n";
    ss << "  ls [path]        List directory contents (basic).\n";
    ss << "  mkdir <dirname>  Create a directory.\n";
    ss << "  rm <path>        Remove a file or empty directory.\n";
    ss << "  cat <filename>   Concatenate and print files.\n";
    ss << "  path             Display the system PATH variable.\n";
    ss << "  addpath <dir>    Add directory to internal TINYSHELL_PATH (conceptual).\n";
    ss << "  c <src> [args]   Compile and run a C source file using gcc.\n";
    ss << "  cpp <src> [args] Compile and run a C++ source file using g++.\n";
    ss << "  history [n]      Display command history (last n commands).\n";
    ss << "  test expr        Evaluate conditional expression.\n";
    ss << "  [ expr ]         Alias for test command.\n";
    // ss << "  cat_spin         (Optional fun command).\n";
    return ss.str();
}

std::string Builtins::getHelpText(BuiltinCommandType type)
{
    switch (type)
    {
        case BuiltinCommandType::Exit:    return "exit [n]: Exit the shell.\n    Exits the shell with a status of N. If N is omitted, the exit status\n    is that of the last command executed.";
        case BuiltinCommandType::Echo:    return "echo [args...]: Write arguments to standard output.\n    Outputs the ARGs, separated by spaces, followed by a newline.";
        case BuiltinCommandType::Help:    return "help [pattern...]: Display help for built-in commands.\n    Displays brief summaries of built-in commands. If PATTERN is specified,\n    gives detailed help on command matching PATTERN.";
        case BuiltinCommandType::Intro:   return "intro [color]: Display group information.\n    Shows the names and IDs of Group 1 members. Optional color argument (not fully implemented). ";
        case BuiltinCommandType::SetVar:  return "setvar VAR=value: Set internal shell variable.\n    Assigns VALUE to the internal shell variable VAR.";
        case BuiltinCommandType::GetVar:  return "getvar VAR: Display the value of internal variable VAR.\n    Prints the value of the specified internal variable.";
        case BuiltinCommandType::UnsetVar:return "unsetvar VAR: Unset internal shell variable VAR.\n    Removes the specified variable from the internal shell environment.";
        case BuiltinCommandType::Cd:      return "cd [dir]: Change the shell working directory.\n    Change the current directory to DIR. The default DIR is the value of the\n    HOME environment variable.";
        case BuiltinCommandType::Pwd:     return "pwd: Print the name of the current working directory.";
        case BuiltinCommandType::Ls:      return "ls [path]: List directory contents (basic).\n    Lists files and directories in the specified path (or current directory).";
        case BuiltinCommandType::Mkdir:   return "mkdir <dirname>: Create a directory.\n    Creates a directory named DIRNAME.";
        case BuiltinCommandType::Rm:      return "rm <path>: Remove a file or empty directory.\n    Removes the specified file or empty directory.";
        case BuiltinCommandType::Cat:     return "cat <filename>: Concatenate and print files.\n    Displays the content of the specified file.";
        case BuiltinCommandType::Path:    return "path: Display the system PATH variable.\n    Prints the value of the PATH environment variable from the system.";
        case BuiltinCommandType::AddPath: return "addpath <dir>: Add directory to internal TINYSHELL_PATH (conceptual).\n    Appends the specified directory to an internal variable TINYSHELL_PATH.\n    Warning: Does not affect system PATH used by external commands.";
        case BuiltinCommandType::C:       return "c <src.c> [args...]: Compile and run a C source file.\n    Compiles SRC.C using 'gcc' and runs the resulting executable with ARGS.";
        case BuiltinCommandType::Cpp:     return "cpp <src.cpp> [args...]: Compile and run a C++ source file.\n    Compiles SRC.CPP using 'g++' and runs the resulting executable with ARGS.";
        case BuiltinCommandType::History: return "history [n]: Display command history.\n    Displays the command history list. If N is specified, displays the last N commands.";
        case BuiltinCommandType::Test:    return "test expression | [ expression ]: Evaluate conditional expression.\n    Evaluates EXPRESSION and returns status 0 (true) or 1 (false).\n    Operators: -e, -f, -d (file tests), =, != (string), -eq, -ne, -gt, -ge, -lt, -le (integer).";
        // case BuiltinCommandType::CatSpin: return "cat_spin: Optional fun command.";
        default: return "No help available for this command.";
    }
}

}

