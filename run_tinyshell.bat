@echo off
setlocal

set "TS_EXE_PATH="

if exist ".\tinyshell.exe" (
    set "TS_EXE_PATH=.\tinyshell.exe"
) else if exist ".\build\tinyshell.exe" (
    set "TS_EXE_PATH=.\build\tinyshell.exe"
) else if exist ".\build\Release\tinyshell.exe" (
    set "TS_EXE_PATH=.\build\Release\tinyshell.exe"
) else if exist ".\build\Debug\tinyshell.exe" (
    set "TS_EXE_PATH=.\build\Debug\tinyshell.exe"
)

if defined TS_EXE_PATH (
    echo Starting Tinyshell (Group 1)...
    "%TS_EXE_PATH%"
) else (
    echo tinyshell.exe not found in common locations (., build\, build\Release\, build\Debug\) relative to this script.
    echo Please compile the project using CMake and ensure the tinyshell executable is accessible.
    pause
)

endlocal