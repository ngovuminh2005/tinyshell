# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 4.0

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\build"

# Include any dependencies generated for this target.
include CMakeFiles/tinyshell.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/tinyshell.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/tinyshell.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tinyshell.dir/flags.make

CMakeFiles/tinyshell.dir/codegen:
.PHONY : CMakeFiles/tinyshell.dir/codegen

CMakeFiles/tinyshell.dir/src/builtins.cpp.obj: CMakeFiles/tinyshell.dir/flags.make
CMakeFiles/tinyshell.dir/src/builtins.cpp.obj: CMakeFiles/tinyshell.dir/includes_CXX.rsp
CMakeFiles/tinyshell.dir/src/builtins.cpp.obj: C:/Users/Ngo\ Vu\ Minh/Desktop/New\ folder/csv_read/OS/tinyshell/src/builtins.cpp
CMakeFiles/tinyshell.dir/src/builtins.cpp.obj: CMakeFiles/tinyshell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tinyshell.dir/src/builtins.cpp.obj"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tinyshell.dir/src/builtins.cpp.obj -MF CMakeFiles\tinyshell.dir\src\builtins.cpp.obj.d -o CMakeFiles\tinyshell.dir\src\builtins.cpp.obj -c "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\builtins.cpp"

CMakeFiles/tinyshell.dir/src/builtins.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tinyshell.dir/src/builtins.cpp.i"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\builtins.cpp" > CMakeFiles\tinyshell.dir\src\builtins.cpp.i

CMakeFiles/tinyshell.dir/src/builtins.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tinyshell.dir/src/builtins.cpp.s"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\builtins.cpp" -o CMakeFiles\tinyshell.dir\src\builtins.cpp.s

CMakeFiles/tinyshell.dir/src/environment.cpp.obj: CMakeFiles/tinyshell.dir/flags.make
CMakeFiles/tinyshell.dir/src/environment.cpp.obj: CMakeFiles/tinyshell.dir/includes_CXX.rsp
CMakeFiles/tinyshell.dir/src/environment.cpp.obj: C:/Users/Ngo\ Vu\ Minh/Desktop/New\ folder/csv_read/OS/tinyshell/src/environment.cpp
CMakeFiles/tinyshell.dir/src/environment.cpp.obj: CMakeFiles/tinyshell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tinyshell.dir/src/environment.cpp.obj"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tinyshell.dir/src/environment.cpp.obj -MF CMakeFiles\tinyshell.dir\src\environment.cpp.obj.d -o CMakeFiles\tinyshell.dir\src\environment.cpp.obj -c "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\environment.cpp"

CMakeFiles/tinyshell.dir/src/environment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tinyshell.dir/src/environment.cpp.i"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\environment.cpp" > CMakeFiles\tinyshell.dir\src\environment.cpp.i

CMakeFiles/tinyshell.dir/src/environment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tinyshell.dir/src/environment.cpp.s"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\environment.cpp" -o CMakeFiles\tinyshell.dir\src\environment.cpp.s

CMakeFiles/tinyshell.dir/src/executor.cpp.obj: CMakeFiles/tinyshell.dir/flags.make
CMakeFiles/tinyshell.dir/src/executor.cpp.obj: CMakeFiles/tinyshell.dir/includes_CXX.rsp
CMakeFiles/tinyshell.dir/src/executor.cpp.obj: C:/Users/Ngo\ Vu\ Minh/Desktop/New\ folder/csv_read/OS/tinyshell/src/executor.cpp
CMakeFiles/tinyshell.dir/src/executor.cpp.obj: CMakeFiles/tinyshell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/tinyshell.dir/src/executor.cpp.obj"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tinyshell.dir/src/executor.cpp.obj -MF CMakeFiles\tinyshell.dir\src\executor.cpp.obj.d -o CMakeFiles\tinyshell.dir\src\executor.cpp.obj -c "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\executor.cpp"

CMakeFiles/tinyshell.dir/src/executor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tinyshell.dir/src/executor.cpp.i"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\executor.cpp" > CMakeFiles\tinyshell.dir\src\executor.cpp.i

CMakeFiles/tinyshell.dir/src/executor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tinyshell.dir/src/executor.cpp.s"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\executor.cpp" -o CMakeFiles\tinyshell.dir\src\executor.cpp.s

CMakeFiles/tinyshell.dir/src/expansion.cpp.obj: CMakeFiles/tinyshell.dir/flags.make
CMakeFiles/tinyshell.dir/src/expansion.cpp.obj: CMakeFiles/tinyshell.dir/includes_CXX.rsp
CMakeFiles/tinyshell.dir/src/expansion.cpp.obj: C:/Users/Ngo\ Vu\ Minh/Desktop/New\ folder/csv_read/OS/tinyshell/src/expansion.cpp
CMakeFiles/tinyshell.dir/src/expansion.cpp.obj: CMakeFiles/tinyshell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/tinyshell.dir/src/expansion.cpp.obj"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tinyshell.dir/src/expansion.cpp.obj -MF CMakeFiles\tinyshell.dir\src\expansion.cpp.obj.d -o CMakeFiles\tinyshell.dir\src\expansion.cpp.obj -c "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\expansion.cpp"

CMakeFiles/tinyshell.dir/src/expansion.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tinyshell.dir/src/expansion.cpp.i"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\expansion.cpp" > CMakeFiles\tinyshell.dir\src\expansion.cpp.i

CMakeFiles/tinyshell.dir/src/expansion.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tinyshell.dir/src/expansion.cpp.s"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\expansion.cpp" -o CMakeFiles\tinyshell.dir\src\expansion.cpp.s

CMakeFiles/tinyshell.dir/src/globbing.cpp.obj: CMakeFiles/tinyshell.dir/flags.make
CMakeFiles/tinyshell.dir/src/globbing.cpp.obj: CMakeFiles/tinyshell.dir/includes_CXX.rsp
CMakeFiles/tinyshell.dir/src/globbing.cpp.obj: C:/Users/Ngo\ Vu\ Minh/Desktop/New\ folder/csv_read/OS/tinyshell/src/globbing.cpp
CMakeFiles/tinyshell.dir/src/globbing.cpp.obj: CMakeFiles/tinyshell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/tinyshell.dir/src/globbing.cpp.obj"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tinyshell.dir/src/globbing.cpp.obj -MF CMakeFiles\tinyshell.dir\src\globbing.cpp.obj.d -o CMakeFiles\tinyshell.dir\src\globbing.cpp.obj -c "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\globbing.cpp"

CMakeFiles/tinyshell.dir/src/globbing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tinyshell.dir/src/globbing.cpp.i"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\globbing.cpp" > CMakeFiles\tinyshell.dir\src\globbing.cpp.i

CMakeFiles/tinyshell.dir/src/globbing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tinyshell.dir/src/globbing.cpp.s"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\globbing.cpp" -o CMakeFiles\tinyshell.dir\src\globbing.cpp.s

CMakeFiles/tinyshell.dir/src/job_ctl.cpp.obj: CMakeFiles/tinyshell.dir/flags.make
CMakeFiles/tinyshell.dir/src/job_ctl.cpp.obj: CMakeFiles/tinyshell.dir/includes_CXX.rsp
CMakeFiles/tinyshell.dir/src/job_ctl.cpp.obj: C:/Users/Ngo\ Vu\ Minh/Desktop/New\ folder/csv_read/OS/tinyshell/src/job_ctl.cpp
CMakeFiles/tinyshell.dir/src/job_ctl.cpp.obj: CMakeFiles/tinyshell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/tinyshell.dir/src/job_ctl.cpp.obj"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tinyshell.dir/src/job_ctl.cpp.obj -MF CMakeFiles\tinyshell.dir\src\job_ctl.cpp.obj.d -o CMakeFiles\tinyshell.dir\src\job_ctl.cpp.obj -c "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\job_ctl.cpp"

CMakeFiles/tinyshell.dir/src/job_ctl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tinyshell.dir/src/job_ctl.cpp.i"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\job_ctl.cpp" > CMakeFiles\tinyshell.dir\src\job_ctl.cpp.i

CMakeFiles/tinyshell.dir/src/job_ctl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tinyshell.dir/src/job_ctl.cpp.s"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\job_ctl.cpp" -o CMakeFiles\tinyshell.dir\src\job_ctl.cpp.s

CMakeFiles/tinyshell.dir/src/lexer.cpp.obj: CMakeFiles/tinyshell.dir/flags.make
CMakeFiles/tinyshell.dir/src/lexer.cpp.obj: CMakeFiles/tinyshell.dir/includes_CXX.rsp
CMakeFiles/tinyshell.dir/src/lexer.cpp.obj: C:/Users/Ngo\ Vu\ Minh/Desktop/New\ folder/csv_read/OS/tinyshell/src/lexer.cpp
CMakeFiles/tinyshell.dir/src/lexer.cpp.obj: CMakeFiles/tinyshell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/tinyshell.dir/src/lexer.cpp.obj"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tinyshell.dir/src/lexer.cpp.obj -MF CMakeFiles\tinyshell.dir\src\lexer.cpp.obj.d -o CMakeFiles\tinyshell.dir\src\lexer.cpp.obj -c "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\lexer.cpp"

CMakeFiles/tinyshell.dir/src/lexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tinyshell.dir/src/lexer.cpp.i"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\lexer.cpp" > CMakeFiles\tinyshell.dir\src\lexer.cpp.i

CMakeFiles/tinyshell.dir/src/lexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tinyshell.dir/src/lexer.cpp.s"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\lexer.cpp" -o CMakeFiles\tinyshell.dir\src\lexer.cpp.s

CMakeFiles/tinyshell.dir/src/main.cpp.obj: CMakeFiles/tinyshell.dir/flags.make
CMakeFiles/tinyshell.dir/src/main.cpp.obj: CMakeFiles/tinyshell.dir/includes_CXX.rsp
CMakeFiles/tinyshell.dir/src/main.cpp.obj: C:/Users/Ngo\ Vu\ Minh/Desktop/New\ folder/csv_read/OS/tinyshell/src/main.cpp
CMakeFiles/tinyshell.dir/src/main.cpp.obj: CMakeFiles/tinyshell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/tinyshell.dir/src/main.cpp.obj"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tinyshell.dir/src/main.cpp.obj -MF CMakeFiles\tinyshell.dir\src\main.cpp.obj.d -o CMakeFiles\tinyshell.dir\src\main.cpp.obj -c "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\main.cpp"

CMakeFiles/tinyshell.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tinyshell.dir/src/main.cpp.i"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\main.cpp" > CMakeFiles\tinyshell.dir\src\main.cpp.i

CMakeFiles/tinyshell.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tinyshell.dir/src/main.cpp.s"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\main.cpp" -o CMakeFiles\tinyshell.dir\src\main.cpp.s

CMakeFiles/tinyshell.dir/src/parser_ast.cpp.obj: CMakeFiles/tinyshell.dir/flags.make
CMakeFiles/tinyshell.dir/src/parser_ast.cpp.obj: CMakeFiles/tinyshell.dir/includes_CXX.rsp
CMakeFiles/tinyshell.dir/src/parser_ast.cpp.obj: C:/Users/Ngo\ Vu\ Minh/Desktop/New\ folder/csv_read/OS/tinyshell/src/parser_ast.cpp
CMakeFiles/tinyshell.dir/src/parser_ast.cpp.obj: CMakeFiles/tinyshell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/tinyshell.dir/src/parser_ast.cpp.obj"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tinyshell.dir/src/parser_ast.cpp.obj -MF CMakeFiles\tinyshell.dir\src\parser_ast.cpp.obj.d -o CMakeFiles\tinyshell.dir\src\parser_ast.cpp.obj -c "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\parser_ast.cpp"

CMakeFiles/tinyshell.dir/src/parser_ast.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tinyshell.dir/src/parser_ast.cpp.i"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\parser_ast.cpp" > CMakeFiles\tinyshell.dir\src\parser_ast.cpp.i

CMakeFiles/tinyshell.dir/src/parser_ast.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tinyshell.dir/src/parser_ast.cpp.s"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\parser_ast.cpp" -o CMakeFiles\tinyshell.dir\src\parser_ast.cpp.s

CMakeFiles/tinyshell.dir/src/shell_core.cpp.obj: CMakeFiles/tinyshell.dir/flags.make
CMakeFiles/tinyshell.dir/src/shell_core.cpp.obj: CMakeFiles/tinyshell.dir/includes_CXX.rsp
CMakeFiles/tinyshell.dir/src/shell_core.cpp.obj: C:/Users/Ngo\ Vu\ Minh/Desktop/New\ folder/csv_read/OS/tinyshell/src/shell_core.cpp
CMakeFiles/tinyshell.dir/src/shell_core.cpp.obj: CMakeFiles/tinyshell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/tinyshell.dir/src/shell_core.cpp.obj"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tinyshell.dir/src/shell_core.cpp.obj -MF CMakeFiles\tinyshell.dir\src\shell_core.cpp.obj.d -o CMakeFiles\tinyshell.dir\src\shell_core.cpp.obj -c "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\shell_core.cpp"

CMakeFiles/tinyshell.dir/src/shell_core.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tinyshell.dir/src/shell_core.cpp.i"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\shell_core.cpp" > CMakeFiles\tinyshell.dir\src\shell_core.cpp.i

CMakeFiles/tinyshell.dir/src/shell_core.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tinyshell.dir/src/shell_core.cpp.s"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\shell_core.cpp" -o CMakeFiles\tinyshell.dir\src\shell_core.cpp.s

CMakeFiles/tinyshell.dir/src/signal_event.cpp.obj: CMakeFiles/tinyshell.dir/flags.make
CMakeFiles/tinyshell.dir/src/signal_event.cpp.obj: CMakeFiles/tinyshell.dir/includes_CXX.rsp
CMakeFiles/tinyshell.dir/src/signal_event.cpp.obj: C:/Users/Ngo\ Vu\ Minh/Desktop/New\ folder/csv_read/OS/tinyshell/src/signal_event.cpp
CMakeFiles/tinyshell.dir/src/signal_event.cpp.obj: CMakeFiles/tinyshell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/tinyshell.dir/src/signal_event.cpp.obj"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tinyshell.dir/src/signal_event.cpp.obj -MF CMakeFiles\tinyshell.dir\src\signal_event.cpp.obj.d -o CMakeFiles\tinyshell.dir\src\signal_event.cpp.obj -c "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\signal_event.cpp"

CMakeFiles/tinyshell.dir/src/signal_event.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tinyshell.dir/src/signal_event.cpp.i"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\signal_event.cpp" > CMakeFiles\tinyshell.dir\src\signal_event.cpp.i

CMakeFiles/tinyshell.dir/src/signal_event.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tinyshell.dir/src/signal_event.cpp.s"
	C:\Strawberry\c\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\src\signal_event.cpp" -o CMakeFiles\tinyshell.dir\src\signal_event.cpp.s

# Object files for target tinyshell
tinyshell_OBJECTS = \
"CMakeFiles/tinyshell.dir/src/builtins.cpp.obj" \
"CMakeFiles/tinyshell.dir/src/environment.cpp.obj" \
"CMakeFiles/tinyshell.dir/src/executor.cpp.obj" \
"CMakeFiles/tinyshell.dir/src/expansion.cpp.obj" \
"CMakeFiles/tinyshell.dir/src/globbing.cpp.obj" \
"CMakeFiles/tinyshell.dir/src/job_ctl.cpp.obj" \
"CMakeFiles/tinyshell.dir/src/lexer.cpp.obj" \
"CMakeFiles/tinyshell.dir/src/main.cpp.obj" \
"CMakeFiles/tinyshell.dir/src/parser_ast.cpp.obj" \
"CMakeFiles/tinyshell.dir/src/shell_core.cpp.obj" \
"CMakeFiles/tinyshell.dir/src/signal_event.cpp.obj"

# External object files for target tinyshell
tinyshell_EXTERNAL_OBJECTS =

tinyshell.exe: CMakeFiles/tinyshell.dir/src/builtins.cpp.obj
tinyshell.exe: CMakeFiles/tinyshell.dir/src/environment.cpp.obj
tinyshell.exe: CMakeFiles/tinyshell.dir/src/executor.cpp.obj
tinyshell.exe: CMakeFiles/tinyshell.dir/src/expansion.cpp.obj
tinyshell.exe: CMakeFiles/tinyshell.dir/src/globbing.cpp.obj
tinyshell.exe: CMakeFiles/tinyshell.dir/src/job_ctl.cpp.obj
tinyshell.exe: CMakeFiles/tinyshell.dir/src/lexer.cpp.obj
tinyshell.exe: CMakeFiles/tinyshell.dir/src/main.cpp.obj
tinyshell.exe: CMakeFiles/tinyshell.dir/src/parser_ast.cpp.obj
tinyshell.exe: CMakeFiles/tinyshell.dir/src/shell_core.cpp.obj
tinyshell.exe: CMakeFiles/tinyshell.dir/src/signal_event.cpp.obj
tinyshell.exe: CMakeFiles/tinyshell.dir/build.make
tinyshell.exe: CMakeFiles/tinyshell.dir/linkLibs.rsp
tinyshell.exe: CMakeFiles/tinyshell.dir/objects1.rsp
tinyshell.exe: CMakeFiles/tinyshell.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable tinyshell.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\tinyshell.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tinyshell.dir/build: tinyshell.exe
.PHONY : CMakeFiles/tinyshell.dir/build

CMakeFiles/tinyshell.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\tinyshell.dir\cmake_clean.cmake
.PHONY : CMakeFiles/tinyshell.dir/clean

CMakeFiles/tinyshell.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell" "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell" "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\build" "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\build" "C:\Users\Ngo Vu Minh\Desktop\New folder\csv_read\OS\tinyshell\build\CMakeFiles\tinyshell.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/tinyshell.dir/depend

