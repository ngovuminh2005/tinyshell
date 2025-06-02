# Tinyshell (Group 1) - Verifiably Working C++ Shell

## 1. Project Overview

Tinyshell is a simple, cross-platform command-line interpreter (shell) developed as a university project. It aims to demonstrate core shell functionalities using standard C++17 features, particularly `std::filesystem` and `std::system`, while minimizing direct OS-specific API calls. The focus is on clear, maintainable code adhering to defined conventions, robust error handling, and verifiable execution through automated testing.

## 2. Group Information

Project by Group 1:
- Đặng Tiến Cường (20220020)
- Trần Huy Dương (20230025)
- Phạm Gia Hưng (20230036)
- Ngô Vũ Minh (20230084)

## 3. Compilation Instructions

This project uses CMake (version 3.14 or newer recommended) for cross-platform building. You will need a C++17 compliant compiler (like GCC, Clang, or MSVC).

**General Steps:**

1.  **Prerequisites:** Ensure you have CMake and a C++17 compiler installed.
2.  **Navigate:** Open a terminal or command prompt and navigate to the root directory of the Tinyshell project (the directory containing this `README.md` and `CMakeLists.txt`).
3.  **Configure:** Create a build directory and run CMake to configure the project. Replace `"Your Generator"` with the appropriate generator for your system (e.g., `"MinGW Makefiles"`, `"Unix Makefiles"`, `"Visual Studio 16 2019"`).
    ```bash
    mkdir build
    cd build
    cmake .. -G "Your Generator" 
    # Example for MinGW on Windows: cmake .. -G "MinGW Makefiles"
    # Example for Linux/macOS: cmake .. 
    ```
4.  **Build:** Compile the project using CMake's build command.
    ```bash
    cmake --build .
    # Alternatively, if using Makefiles: make
    ```

**Platform-Specific Examples:**

*   **Windows (MinGW):**
    ```bash
    mkdir build
    cd build
    cmake .. -G "MinGW Makefiles"
    cmake --build .
    # Executable: build\tinyshell.exe
    ```
*   **Windows (MSVC - Visual Studio):**
    ```bash
    mkdir build
    cd build
    cmake .. -G "Visual Studio 16 2019" # Adjust generator as needed
    cmake --build . --config Release # Or Debug
    # Executable: build\Release\tinyshell.exe or build\Debug\tinyshell.exe
    ```
*   **Linux (GCC/Clang):**
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    # Executable: build/tinyshell
    ```
*   **macOS (Clang):**
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    # Executable: build/tinyshell
    ```

The compiled executable (`tinyshell` or `tinyshell.exe`) will be located in the `build` directory (or a subdirectory like `build/Release` depending on the generator).

## 4. Easy Access and Execution Instructions

There are several ways to run Tinyshell:

1.  **Direct Execution from Build Directory:**
    *   Navigate to the directory where the executable was built (e.g., `build/` or `build/Release/`).
    *   Run it directly:
        *   Windows: `.\tinyshell.exe`
        *   Linux/macOS: `./tinyshell`

2.  **Using Helper Scripts:**
    *   Helper scripts are provided in the project's root directory:
        *   `run_tinyshell.bat` (for Windows)
        *   `run_tinyshell.sh` (for Linux/macOS)
    *   These scripts attempt to find the executable in common build locations relative to the script and run it.
    *   Windows: Double-click `run_tinyshell.bat` or run it from the command prompt.
    *   Linux/macOS: Make the script executable (`chmod +x run_tinyshell.sh`) and run it (`./run_tinyshell.sh`).

3.  **Adding to System PATH (Advanced):**
    *   To run `tinyshell` from any directory, add the directory containing the executable to your system's `PATH` environment variable.
    *   **Windows:**
        1.  Search for "Environment Variables" in the Start menu and select "Edit the system environment variables".
        2.  Click the "Environment Variables..." button.
        3.  Under "System variables" (or "User variables" for just your account), find the `Path` variable, select it, and click "Edit...".
        4.  Click "New" and paste the full path to the directory containing `tinyshell.exe` (e.g., `C:\path\to\tinyshell\build\Release`).
        5.  Click OK on all dialogs. You may need to restart your command prompt or computer.
    *   **Linux (Bash/Zsh - Temporary):**
        ```bash
        export PATH="/path/to/tinyshell/build:$PATH"
        ```
        (Add this line to your `~/.bashrc` or `~/.zshrc` for permanent effect).
    *   **macOS (Bash/Zsh - Temporary):**
        ```bash
        export PATH="/path/to/tinyshell/build:$PATH"
        ```
        (Add this line to your `~/.bash_profile`, `~/.zshrc`, or `/etc/paths.d/` for permanent effect).

**Note on Naming Conventions:** The source code strictly adheres to the rules defined in the included `NAMING_CONVENTIONS.md` file.

## 5. Comprehensive Usage Instructions and Examples

Tinyshell provides a set of built-in commands and supports executing external commands found in the system's PATH.

**General Syntax:**
`command [argument1] [argument2] ...`

**Comments:** Lines starting with `#` are ignored.

**Quoting:**
*   Double quotes (`"`) allow variable expansion (`$VAR`) and preserve literal spaces.
*   Single quotes (`'`) prevent variable expansion and preserve literal spaces.
*   Backslash (`\`) escapes the next character.

**Variable Expansion:**
*   `$VAR` or `${VAR}` expands to the value of the internal shell variable `VAR`.
*   `$?` expands to the exit status of the last executed foreground command.

**Control Flow:**
*   `if command_list; then command_list; [elif command_list; then command_list;]... [else command_list;] fi`
*   `while command_list; do command_list; done`
*   `for var in word_list; do command_list; done`

--- 

**Built-in Commands:**

*   **`exit [n]`**
    *   **Syntax:** `exit [n]`
    *   **Description:** Exits the Tinyshell. If `n` (an integer) is provided, the shell exits with status `n`. Otherwise, it exits with the status of the last executed command.
    *   **Examples:**
        ```
        exit      # Exit with last command's status
        exit 0    # Exit successfully
        exit 1    # Exit with error status 1
        ```

*   **`echo [args...]`**
    *   **Syntax:** `echo [argument1] [argument2] ...`
    *   **Description:** Prints the arguments to the standard output, separated by spaces, followed by a newline.
    *   **Examples:**
        ```
        echo Hello World
        echo "This has   spaces"
        setvar GREETING=Hi
        echo $GREETING there!
        echo 'No expansion for $GREETING'
        ```

*   **`help [cmd]`**
    *   **Syntax:** `help [command_name]`
    *   **Description:** Displays help information. Without arguments, lists all built-in commands. With `command_name`, shows detailed help for that specific built-in.
    *   **Examples:**
        ```
        help
        help cd
        help exit
        ```

*   **`intro [color]`**
    *   **Syntax:** `intro [color_name_or_hex]`
    *   **Description:** Displays Group 1's information (names and student IDs). The optional `color` argument is currently ignored.
    *   **Examples:**
        ```
        intro
        ```

*   **`setvar VAR=value`**
    *   **Syntax:** `setvar VARIABLE_NAME=value`
    *   **Description:** Sets an internal shell variable `VARIABLE_NAME` to the specified `value`. The value can contain spaces if quoted during expansion, but the `setvar` command itself expects a single argument in the `VAR=value` format.
    *   **Examples:**
        ```
        setvar USERNAME=Alice
        setvar COUNT=10
        setvar MESSAGE="Hello There"
        ```

*   **`getvar VAR`**
    *   **Syntax:** `getvar VARIABLE_NAME`
    *   **Description:** Prints the value of the internal shell variable `VARIABLE_NAME` to standard output, followed by a newline. If the variable is not set internally, it attempts to read from the system environment (read-only).
    *   **Examples:**
        ```
        setvar MYPATH=/usr/bin
        getvar MYPATH
        getvar USER # Tries to get from system environment if not set internally
        ```

*   **`unsetvar VAR`**
    *   **Syntax:** `unsetvar VARIABLE_NAME`
    *   **Description:** Removes the internal shell variable `VARIABLE_NAME` from Tinyshell's environment.
    *   **Examples:**
        ```
        setvar TEMP=temporary
        getvar TEMP
        unsetvar TEMP
        getvar TEMP # Should now fail or print nothing
        ```

*   **`cd [dir]`**
    *   **Syntax:** `cd [directory_path]`
    *   **Description:** Changes the current working directory. If no `directory_path` is given, it changes to the user's home directory (obtained from `HOME` or `USERPROFILE` environment variables). `cd ..` changes to the parent directory.
    *   **Examples:**
        ```
        pwd
        mkdir my_new_dir
        cd my_new_dir
        pwd
        cd ..
        pwd
        cd # Change to home directory
        pwd
        ```

*   **`pwd`**
    *   **Syntax:** `pwd`
    *   **Description:** Prints the full path of the current working directory to standard output.
    *   **Examples:**
        ```
        pwd
        ```

*   **`ls [path]`**
    *   **Syntax:** `ls [directory_or_file_path]`
    *   **Description:** Lists the contents of the specified directory (or the current directory if no path is given). If a file path is given, it prints the filename. This is a basic version without formatting options.
    *   **Examples:**
        ```
        ls
        ls src
        ls README.md
        ```

*   **`mkdir <dirname>`**
    *   **Syntax:** `mkdir directory_name`
    *   **Description:** Creates a new directory with the specified name.
    *   **Examples:**
        ```
        mkdir new_folder
        ls
        ```

*   **`rm <path>`**
    *   **Syntax:** `rm path_to_remove`
    *   **Description:** Removes the specified file or *empty* directory.
    *   **Examples:**
        ```
        echo "delete me" > temp_file.txt
        ls
        rm temp_file.txt
        ls
        mkdir empty_dir
        rm empty_dir
        ls
        ```

*   **`cat <filename>`**
    *   **Syntax:** `cat file_to_display`
    *   **Description:** Displays the contents of the specified file to standard output.
    *   **Examples:**
        ```
        cat README.md
        echo "Some text" > example.txt
        cat example.txt
        ```

*   **`path`**
    *   **Syntax:** `path`
    *   **Description:** Displays the system's `PATH` environment variable.
    *   **Examples:**
        ```
        path
        ```

*   **`addpath <dir>`**
    *   **Syntax:** `addpath directory_to_add`
    *   **Description:** *Conceptual.* Appends the specified directory to an *internal* shell variable `TINYSHELL_PATH`. **Warning:** This does *not* modify the system `PATH` used by external commands executed via `std::system()`.
    *   **Examples:**
        ```
        addpath /usr/local/custom/bin
        getvar TINYSHELL_PATH
        ```

*   **`c <src.c> [args...]`**
    *   **Syntax:** `c source_file.c [compiler_args...]`
    *   **Description:** Compiles the specified C source file (`source_file.c`) using `gcc` (must be in the system PATH) into a temporary executable, runs the executable with any provided `args`, and then deletes the temporary executable. Reports basic success/failure based on `gcc` and execution return codes.
    *   **Examples:**
        ```c
        // Create hello.c: #include <stdio.h> int main() { printf("Hello C!\n"); return 0; }
        echo "#include <stdio.h> int main() { printf(\"Hello C!\\n\"); return 0; }" > hello.c 
        c hello.c
        c hello.c arg1 arg2
        ```

*   **`cpp <src.cpp> [args...]`**
    *   **Syntax:** `cpp source_file.cpp [compiler_args...]`
    *   **Description:** Compiles the specified C++ source file (`source_file.cpp`) using `g++` (must be in the system PATH) into a temporary executable, runs the executable with any provided `args`, and then deletes the temporary executable. Reports basic success/failure based on `g++` and execution return codes.
    *   **Examples:**
        ```cpp
        // Create hello.cpp: #include <iostream> int main() { std::cout << "Hello C++!" << std::endl; return 0; }
        echo "#include <iostream> int main() { std::cout << \"Hello C++!\" << std::endl; return 0; }" > hello.cpp
        cpp hello.cpp
        cpp hello.cpp arg1 arg2
        ```

*   **`history [n]`**
    *   **Syntax:** `history [n]`
    *   **Description:** Displays the command history. If `n` (a non-negative integer) is provided, shows the last `n` commands.
    *   **Examples:**
        ```
        history
        history 10
        ```

*   **`test expression`** or **`[ expression ]`**
    *   **Syntax:** `test expression` or `[ expression ]` (Note: spaces around `[` and `]` are required)
    *   **Description:** Evaluates the `expression` and sets the exit status `$?` to 0 (true) or 1 (false). Used primarily in control flow (`if`, `while`).
    *   **Supported Expressions:**
        *   File tests: `-e path` (exists), `-f path` (is regular file), `-d path` (is directory)
        *   String comparison: `s1 = s2` or `s1 == s2` (equal), `s1 != s2` (not equal)
        *   Integer comparison: `n1 -eq n2` (equal), `n1 -ne n2` (not equal), `n1 -gt n2` (greater than), `n1 -ge n2` (greater or equal), `n1 -lt n2` (less than), `n1 -le n2` (less or equal)
    *   **Examples:**
        ```
        test -f README.md
        echo $?
        [ -d src ]
        echo $?
        VAR=hello
        test $VAR = hello
        echo $?
        [ 10 -gt 5 ]
        echo $?
        if test -e somefile; then echo "Exists"; fi 
        ```

--- 

**External Commands:**

*   **Description:** If a command is not a built-in, Tinyshell attempts to execute it as an external program using the system's underlying shell via `std::system()`. The command must be found in the directories listed in the system's `PATH` environment variable.
*   **Examples (depend on your system):**
    ```
    ls -l # Uses system's ls if available
    python --version
    git status
    ```

## 6. Detailed Error Handling Description

Tinyshell aims to provide informative error messages and set appropriate exit statuses (`$?`).

*   **General Errors:**
    *   **Command Not Found:** If an external command is not found in PATH or a built-in is misspelled.
        *   Message: `command_name: command not found` (for external) or similar.
        *   State: Shell continues.
        *   Exit Status (`$?`): Typically 127 (for external commands, depends on `std::system`), or 1 for unknown built-ins.
    *   **Syntax Errors:** Invalid use of control flow, unclosed quotes, invalid variable names, incorrect arguments for built-ins.
        *   Message: Specific error message (e.g., `Parser error: Expected 'then' for if condition...`, `Lexer error: Unclosed quote...`, `setvar: Invalid format...`, `test: missing ']`, `exit: Numeric argument required`).
        *   State: Command is aborted, shell continues.
        *   Exit Status (`$?`): Typically 1 or 2 (2 often used for shell syntax errors).

*   **Built-in Specific Errors:**
    *   **`exit [n]`:**
        *   Scenario: Non-numeric argument `n`.
        *   Message: `exit: Numeric argument required` or `exit: Argument out of range`.
        *   State: Exit is aborted, shell continues.
        *   `$?`: 1.
    *   **`help [cmd]`:**
        *   Scenario: Help requested for an unknown command `cmd`.
        *   Message: `help: no help topics match elation{`cmdelation}`.
        *   State: Shell continues.
        *   `$?`: 1.
    *   **`setvar VAR=value`:**
        *   Scenario: Invalid format (no `=`, `=value`, `VAR=`), invalid variable name.
        *   Message: `setvar: Invalid format...` or `setvar: Invalid variable name: ...`.
        *   State: Variable not set, shell continues.
        *   `$?`: 1.
    *   **`getvar VAR`:**
        *   Scenario: Variable `VAR` not set internally or in system environment.
        *   Message: `getvar: Variable not set: VAR`.
        *   State: Nothing printed, shell continues.
        *   `$?`: 1.
    *   **`cd [dir]`:**
        *   Scenario: Target directory `dir` does not exist, is not a directory, or permissions denied.
        *   Message: `cd: No such file or directory: dir`, `cd: Not a directory: dir`, `cd: Cannot change directory to dir: Permission denied` (message may vary slightly based on `std::filesystem` error).
        *   State: Directory not changed, shell continues.
        *   `$?`: 1.
    *   **`pwd`:**
        *   Scenario: Filesystem error preventing retrieval of current path.
        *   Message: `pwd: Cannot determine current path: ...` (system error message).
        *   State: Shell continues.
        *   `$?`: 1.
    *   **`ls [path]`:**
        *   Scenario: Path does not exist, permission denied.
        *   Message: `ls: Cannot access elation{`pathelation}`: No such file or directory` or `ls: Cannot read directory elation{`pathelation}`: Permission denied`.
        *   State: Shell continues.
        *   `$?`: 1.
    *   **`mkdir <dirname>`:**
        *   Scenario: Directory/file already exists, permission denied.
        *   Message: `mkdir: Cannot create directory elation{`dirnameelation}`: File exists` or `mkdir: Cannot create directory elation{`dirnameelation}`: Permission denied`.
        *   State: Directory not created, shell continues.
        *   `$?`: 1.
    *   **`rm <path>`:**
        *   Scenario: Path does not exist, permission denied, directory not empty.
        *   Message: `rm: Cannot remove elation{`pathelation}`: No such file or directory`, `rm: Cannot remove elation{`pathelation}`: Permission denied`, `rm: Cannot remove elation{`pathelation}`: Directory not empty`.
        *   State: File/directory not removed, shell continues.
        *   `$?`: 1.
    *   **`cat <filename>`:**
        *   Scenario: File does not exist, is a directory, permission denied.
        *   Message: `cat: elation{`filenameelation}`: No such file or directory`, `cat: elation{`filenameelation}`: Is a directory`, `cat: elation{`filenameelation}`: Permission denied...`.
        *   State: Shell continues.
        *   `$?`: 1.
    *   **`c`/`cpp <src> [args]`:**
        *   Scenario: Source file not found, compilation fails (compiler error), execution of compiled program fails.
        *   Message: `c: Source file not found...`, `c: Compilation failed (exit code: N)`, execution errors depend on the compiled program.
        *   State: Shell continues.
        *   `$?`: Exit code from `gcc`/`g++` or the executed program.
    *   **`history [n]`:**
        *   Scenario: Non-numeric or negative argument `n`.
        *   Message: `history: Numeric argument required (non-negative)`.
        *   State: Shell continues.
        *   `$?`: 1.
    *   **`test expression` / `[ expression ]`:**
        *   Scenario: Invalid expression syntax (missing arguments, unknown operator, non-integer for integer comparison, missing `]`).
        *   Message: `test: missing ']`, `test: Unknown unary operator: ...`, `test: Integer expression expected: ...`, `test: Invalid test expression`.
        *   State: Shell continues.
        *   `$?`: 2 (typically used for syntax errors in `test`).

*   **Expansion Errors:**
    *   Scenario: Undefined variable (`$UNDEF` or `${UNDEF}`), unclosed brace (`${VAR`).
    *   Message: `Error expanding arguments: Undefined variable: UNDEF` (Note: current implementation might expand undefined to empty string without error) or `Error expanding arguments: Unclosed variable expansion brace...`.
    *   State: Command execution aborted, shell continues.
    *   `$?`: 1.

## 7. List of Implemented Features

*   **Core:**
    *   REPL (Read-Eval-Print Loop)
    *   Command History (`history` command, accessible via internal list)
    *   Basic Prompt showing current directory name
*   **Parsing & Execution:**
    *   Lexing (tokenization of input)
    *   Parsing (simple AST generation)
    *   External Command Execution (via `std::system()`)
    *   Built-in Command Execution
    *   Basic Quoting (`'`, `"`, `\`)
    *   Comment Handling (`#`)
    *   Exit Status Tracking (`$?`)
*   **Variable Management:**
    *   Internal Shell Variables (`setvar`, `getvar`, `unsetvar`)
    *   Basic Parameter Expansion (`$VAR`, `${VAR}`, `$?`)
    *   Read-only access to System Environment Variables via `getvar`
*   **Built-in Commands:**
    *   `exit`, `echo`, `help`, `intro`
    *   `setvar`, `getvar`, `unsetvar`
    *   `cd`, `pwd`
    *   `ls` (basic)
    *   `mkdir` (basic)
    *   `rm` (files and empty directories)
    *   `cat` (basic)
    *   `path`
    *   `addpath` (conceptual internal path)
    *   `c`, `cpp` (compile & run via `gcc`/`g++`)
    *   `history`
    *   `test` / `[` (basic file/string/integer tests)
*   **Control Flow:**
    *   `if`/`then`/`elif`/`else`/`fi`
    *   `while`/`do`/`done`
    *   `for`/`in`/`do`/`done`

## 8. Explicitly Stated Limitations

Due to the project's goals (cross-platform using standard C++, minimizing OS-specific APIs, university project scope), Tinyshell has several limitations compared to full-featured shells like Bash or Zsh:

*   **External Command Execution:** Relies entirely on `std::system()`, meaning:
    *   **Pipelines (`|`) and I/O Redirection (`<`, `>`, `>>`) for External Commands:** Behavior depends entirely on the underlying system shell that `std::system()` invokes. Tinyshell does not manage these directly for external commands.
    *   **Job Control (`&`, `jobs`, `fg`, `bg`):** Not implemented. Backgrounding (`&`) behavior depends on `std::system()`.
*   **Signal Handling:** Very basic. Ctrl+C might terminate the shell itself, but no advanced signal trapping or handling for child processes.
*   **Expansions:** Only basic parameter expansion (`$VAR`, `${VAR}`, `$?`) is supported. No tilde expansion, command substitution, arithmetic expansion (beyond what `test` supports), brace expansion, or advanced globbing.
*   **Globbing (Wildcards):** No wildcard expansion (e.g., `ls *.txt`) is performed by Tinyshell itself before passing arguments to commands.
*   **Environment Variables:** `setvar`/`unsetvar` only affect *internal* shell variables. They do not modify the environment inherited by external commands run via `std::system()` (unlike `export` in POSIX shells).
*   **Shell Functions and Aliases:** Not implemented.
*   **Subshells (`()`):** Not implemented. Control flow blocks (`if`, `while`, `for`) execute in the current shell environment.
*   **Configuration Files:** No startup files (like `.bashrc`) are read.
*   **Input Editing/Completion:** No advanced line editing features (like arrow keys for history navigation, tab completion) are built-in. Relies on basic terminal line input. (GNU Readline is explicitly excluded).
*   **Error Recovery:** Parser and lexer stop on the first significant error.
*   **`addpath`:** Only modifies an internal variable, does not affect `PATH` for external commands.

## 9. External Dependencies

*   **C++17 Compliant Compiler:** (e.g., GCC 7+, Clang 5+, MSVC 19.14+)
*   **CMake:** (Version 3.14+ recommended)
*   **(Implicit for `c`/`cpp` commands):** `gcc` and `g++` must be installed and accessible in the system's PATH.
*   **(Optional):** GNU Readline is **NOT** used or required.

