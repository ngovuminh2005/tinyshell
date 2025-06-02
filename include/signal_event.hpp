#ifndef SIGNAL_EVENT_HPP
#define SIGNAL_EVENT_HPP

#include <windows.h>

// Function to initialize console control handling
void initialize_signal_handling();

// Function to set the PID of the current foreground process group leader
// Windows doesn't have process groups exactly like POSIX, so this usually targets the direct child.
void set_foreground_pid(DWORD pid);

// Function to clear the foreground PID when no foreground process is running
void clear_foreground_pid();

#endif // SIGNAL_EVENT_HPP

