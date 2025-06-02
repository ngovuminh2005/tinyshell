#pragma once

#include <string>
#include <vector>
#include <map>
#include <variant>

namespace g1_tinyshell
{

// Forward declarations
class Environment;
class Executor;
// AST Node structs are defined in parser_ast.hpp

// --- Constants ---
constexpr int K_MaxHistorySize = 100;
constexpr const char* K_DefaultPromptColor = "\033[1;34m"; // Bold Blue
constexpr const char* K_PathPromptColor = "\033[1;32m";    // Bold Green
constexpr const char* K_ResetColor = "\033[0m";

// --- Enums ---

enum class BuiltinCommandType
{
    Exit,
    Echo,
    Help,
    Intro,
    SetVar,
    GetVar,
    UnsetVar,
    Cd,
    Pwd,
    Ls,
    Mkdir,
    Rm,
    Cat,
    Path,
    AddPath,
    C,
    Cpp,
    History,
    Test,
    CatSpin, // Optional
    Unknown
};

enum class CommandType
{
    Builtin,
    External,
    Empty,
    Error
};

// --- Basic Structures (can be expanded in respective headers) ---

struct CommandInfo
{
    CommandType type = CommandType::Empty;
    std::string command_name;
    std::vector<std::string> arguments;
    BuiltinCommandType builtin_type = BuiltinCommandType::Unknown;
    // Add fields for redirection, backgrounding if extending later
};

// Structure to hold execution result
struct ExecutionResult
{
    int exit_status = 0;
    std::string error_message;
    bool continue_shell = true;
};

}

