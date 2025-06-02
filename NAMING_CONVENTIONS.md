# Tinyshell (Group 1) - Naming and Coding Conventions

This document outlines the naming and basic code structure conventions strictly adhered to throughout the Tinyshell project (Group 1).

## 1. General

- **Language Version:** C++17
- **Encoding:** UTF-8

## 2. File Naming

- **Convention:** `lower_snake_case.ext`
- **Examples from Code:**
    - Source files: `main.cpp`, `shell_core.cpp`, `environment.cpp`, `lexer.cpp`, `parser_ast.cpp`, `executor.cpp`, `expansion.cpp`, `builtins.cpp`
    - Header files: `tinyshell_globals.hpp`, `shell_core.hpp`, `environment.hpp`, `lexer.hpp`, `parser_ast.hpp`, `executor.hpp`, `expansion.hpp`, `builtins.hpp`

## 3. Namespaces

- **Primary Project Namespace:** `g1_tinyshell`
- **Sub-namespaces:** None used.
- **`using namespace std;`:** Disallowed in headers. Explicit `std::` preferred in source files.
- **Example from Code:** All project code resides within the `g1_tinyshell` namespace.

## 4. Classes and Structs

- **Naming Convention:** `PascalCase`
- **Examples from Code:**
    - `ShellCore`
    - `Environment`
    - `Lexer`
    - `Token`
    - `Parser`
    - `AstNodeBase` (struct)
    - `SimpleCommandNode` (struct)
    - `CommandSequenceNode` (struct)
    - `IfNode` (struct)
    - `WhileNode` (struct)
    - `ForNode` (struct)
    - `Executor`
    - `Expansion`
    - `Builtins`
    - `CommandInfo` (struct)
    - `ExecutionResult` (struct)

## 5. Member Variables

- **Naming Convention:** `m_camelCase`
- **Visibility:** `private`
- **Examples from Code:**
    - `m_environment`, `m_executor`, `m_commandHistory`, `m_shouldExit` (in `ShellCore`)
    - `m_variables` (in `Environment`)
    - `m_input`, `m_currentPosition`, `m_errorMessage` (in `Lexer`)
    - `m_tokens`, `m_currentTokenIndex`, `m_errorMessage` (in `Parser`)
    - `m_environment`, `m_shellCore` (in `Executor`)

## 6. Member Functions (Methods)

- **Naming Convention:** `camelCase()`
- **`const` Correctness:** Applied where applicable.
- **Examples from Code:**
    - `run()`, `addToHistory()`, `getHistory() const`, `requestExit()`, `getEnvironment()`, `readLine()`, `displayPrompt()` (in `ShellCore`)
    - `setVariable()`, `getVariable() const`, `unsetVariable()`, `getAllVariables() const`, `isValidVariableName()` (in `Environment`)
    - `tokenize()`, `getNextToken()`, `processWord()`, `peek() const`, `advance()`, `isAtEnd() const` (in `Lexer`)
    - `parse()`, `getErrorMessage() const`, `parseCommandSequence()`, `parseCommand()`, `currentToken() const`, `advanceToken()`, `expectToken()` (in `Parser`)
    - `execute()`, `executeSimpleCommand()`, `executeCommandSequence()`, `executeIfNode()`, `executeWhileNode()`, `executeForNode()`, `executeExternalCommand()`, `setLastExitStatus()` (in `Executor`)
    - `expandWord()`, `expandArguments()`, `performExpansion()` (in `Expansion`)
    - `executeBuiltin()`, `getBuiltinType()`, `getHelpText()`, `listBuiltins()`, `builtinExit()`, `builtinEcho()`, `builtinCd()`, `builtinPwd()`, `builtinLs()`, `builtinMkdir()`, `builtinRm()`, `builtinCat()`, `builtinTest()`, `compileAndRun()`, `evaluateTestExpression()`, `compareIntegers()` (in `Builtins`)

## 7. Global Functions

- **Usage:** Minimized. Confined to `g1_tinyshell` namespace.
- **Naming Convention:** `lower_snake_case()`
- **Examples from Code:** (None currently implemented).

## 8. Local Variables

- **Naming Convention:** `lower_snake_case`
- **Examples from Code:**
    - `line`, `tokens`, `lexer`, `parser`, `ast_root`, `result`, `current_path`, `path_segment`, `ec` (in `ShellCore`)
    - `assignment`, `equals_pos`, `var_name`, `value`, `it`, `env_value` (in `Environment`)
    - `tokens`, `current_char`, `start_pos`, `word_value`, `keyword_it`, `var_name`, `value`, `found_closing_quote` (in `Lexer`)
    - `sequence_node`, `command`, `command_node`, `if_node`, `elif_condition`, `elif_body`, `while_node`, `for_node`, `expected_type_str` (in `Parser`)
    - `command_name`, `arguments`, `expansion_error`, `builtin_type`, `cmd_info`, `result`, `last_result`, `condition_result`, `elif_pair`, `elif_condition_result`, `last_body_result`, `expanded_words`, `expanded_word`, `original_value`, `word_value`, `command_stream`, `full_command`, `system_ret`, `exit_status`, `error_message` (in `Executor`)
    - `result_stream`, `potential_error`, `var_name`, `start_pos`, `use_braces`, `end_brace_pos`, `current_pos`, `value`, `current_error`, `expanded_arg` (in `Expansion`)
    - `exit_code`, `processed_chars`, `i`, `type`, `assignment`, `equals_pos`, `var_name`, `value`, `target_path`, `home_dir`, `current_p`, `ec`, `error_msg`, `entry`, `dir_path`, `path_to_remove`, `file_path`, `input_file`, `line`, `path_var`, `dir_to_add`, `current_tinyshell_path`, `new_path`, `source_file`, `compile_args`, `count`, `history`, `start_index`, `expression`, `result`, `op`, `path_arg`, `arg1`, `arg2`, `val1`, `val2`, `pos1`, `pos2`, `ss`, `compiler`, `temp_dir`, `temp_executable`, `compile_command_ss`, `compile_status`, `run_command_ss`, `run_status` (in `Builtins`)
    - `argc`, `argv`, `tinyshell_core`, `final_exit_code`, `exit_status_str` (in `main`)

## 9. Constants and Enums

- **Enums:** `enum class EnumName { ValueOne };` (`PascalCase` for type and values).
    - **Examples from Code:** `TokenType`, `BuiltinCommandType`, `CommandType` (types); `TokenType::Word`, `BuiltinCommandType::Exit` (values).
- **Constants:** `constexpr type K_CONSTANT_NAME = value;` (`K_PascalCase` or `K_ALL_CAPS_SNAKE_CASE`).
    - **Examples from Code:** `K_Keywords`, `K_BuiltinCommands` (maps); `K_MaxHistorySize`, `K_DefaultPromptColor`, `K_PathPromptColor`, `K_ResetColor` (constexpr values).
- **Type Aliases:** `PascalCase`.
    - **Example from Code:** `AstNodePtr`.

## 10. Preprocessor Macros

- **Usage:** Minimized (primarily include guards if not `#pragma once`).
- **Naming Convention:** `ALL_CAPS_SNAKE_CASE`.
- **Example from Code:** `GETENV_HOME` (used in `builtins.cpp`).

## 11. Include Guards

- **Method:** `#pragma once` used in all header files.

## 12. Indentation and Formatting

- **Indentation:** 4 spaces.
- **Brace Style:** Allman style.
- **Line Length:** Aim for 100-120 characters.

## 13. Example Snippet (Illustrative - See sections above for actual examples)

```cpp
#pragma once

#include <string>
#include <vector>

namespace g1_tinyshell
{

constexpr int K_MaxBufferSize = 1024; // K_PascalCase constant

enum class TaskStatus // PascalCase enum class
{
    Pending, // PascalCase enum value
    Complete
};

class DataProcessor // PascalCase class name
{
public:
    DataProcessor();

    // camelCase() method name
    bool processData(const std::vector<std::string>& data_list) const;

private:
    // m_camelCase member variable
    int m_processedCount;
};

// lower_snake_case() standalone function name
std::string format_output(int count);

// lower_snake_case local variable
void runAnalysis()
{
    int item_index = 0;
    // ...
}

}
```

