#include "../include/shell_core.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    // Suppress unused parameter warnings if argc/argv are not used
    (void)argc;
    (void)argv;

    // Set locale for potential wide character support if needed later
    // std::setlocale(LC_ALL, "");

    // Create the main shell core object
    g1_tinyshell::ShellCore tinyshell_core;

    // Start the Read-Eval-Print Loop (REPL)
    try
    {
        tinyshell_core.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Tinyshell: Unhandled exception: " << e.what() << std::endl;
        return 1; // Return error code on unhandled exception
    }
    catch (...)
    {
        std::cerr << "Tinyshell: Unknown unhandled exception." << std::endl;
        return 1;
    }

    // Exit status should be handled by the 'exit' builtin setting the shell core state
    // Retrieve the final intended exit code if needed (e.g., from environment $?)
    int final_exit_code = 0;
    try {
         auto exit_status_str = tinyshell_core.getEnvironment().getVariable("?");
         if (exit_status_str.has_value()) {
             final_exit_code = std::stoi(exit_status_str.value());
         }
    } catch (...) {
        // Ignore errors converting final exit status
    }


    return final_exit_code;
}

