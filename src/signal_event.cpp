#include "signal_event.hpp"
#include <windows.h>
#include <iostream>

// Global variable to store the PID of the current foreground process
// Needs careful management, potentially thread-local if shell becomes multi-threaded
static DWORD g_foreground_pid = 0;

// Console Control Handler function
BOOL WINAPI console_ctrl_handler(DWORD ctrl_type) {
    switch (ctrl_type) {
        case CTRL_C_EVENT:
            // std::cerr << "Ctrl+C received. Foreground PID: " << g_foreground_pid << std::endl;
            if (g_foreground_pid != 0) {
                // Attempt to send Ctrl+C to the foreground process group.
                // GenerateConsoleCtrlEvent can target a process group (if PID is 0, sends to all attached to console).
                // Sending to a specific PID might not work as expected for console events.
                // A common approach is to send it to the console group the child might belong to.
                // If the child created its own console or detached, this might not work.
                // Simpler/more direct: Try terminating the specific process.
                
                // Option 1: Try GenerateConsoleCtrlEvent (might not reliably interrupt specific child)
                // if (!GenerateConsoleCtrlEvent(CTRL_C_EVENT, g_foreground_pid)) { // Sending to specific PID often fails
                // if (!GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0)) { // Send to console group
                //     std::cerr << "Warning: Failed to send Ctrl+C event. Error: " << GetLastError() << std::endl;
                // }

                // Option 2: Terminate the specific process (more forceful)
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, g_foreground_pid);
                if (hProcess != NULL) {
                    if (!TerminateProcess(hProcess, 1)) { // Use exit code 1 for termination
                        // std::cerr << "Warning: Failed to terminate process " << g_foreground_pid << ". Error: " << GetLastError() << std::endl;
                    }
                    CloseHandle(hProcess);
                } else {
                   // std::cerr << "Warning: Failed to open process " << g_foreground_pid << " for termination. Error: " << GetLastError() << std::endl;
                }
                // Prevent the shell itself from terminating
                return TRUE; 
            }
            // If no foreground process, let the default handler (shell termination) proceed?
            // Or ignore Ctrl+C if shell is idle?
            // Returning TRUE prevents shell termination.
            return TRUE; 

        // Handle other events if necessary (CTRL_BREAK_EVENT, CTRL_CLOSE_EVENT, etc.)
        case CTRL_BREAK_EVENT:
             // Similar handling to CTRL_C?
             if (g_foreground_pid != 0) {
                 // Terminate logic as above
                 HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, g_foreground_pid);
                 if (hProcess != NULL) {
                     TerminateProcess(hProcess, 1);
                     CloseHandle(hProcess);
                 }
                 return TRUE;
             }
             return TRUE; // Prevent shell termination

        case CTRL_CLOSE_EVENT:
             // Shell is closing, maybe clean up jobs?
             // std::cerr << "Shell closing..." << std::endl;
             return FALSE; // Allow default handler to close

        case CTRL_LOGOFF_EVENT:
        case CTRL_SHUTDOWN_EVENT:
             // System is shutting down
             return FALSE; // Allow default handler

        default:
            return FALSE; // Let the default handler process other events
    }
}

void initialize_signal_handling() {
    if (!SetConsoleCtrlHandler(console_ctrl_handler, TRUE)) {
        std::cerr << "Error: Could not set console control handler. Error code: " << GetLastError() << std::endl;
        // Handle error appropriately, maybe exit shell?
    }
}

void set_foreground_pid(DWORD pid) {
    // In a real implementation, might need mutex/critical section if accessed from multiple threads
    g_foreground_pid = pid;
}

void clear_foreground_pid() {
    g_foreground_pid = 0;
}

