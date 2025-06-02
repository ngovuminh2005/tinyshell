cmake_minimum_required(VERSION 3.14) # Need 3.14+ for good C++17 support

project(TinyshellGroup1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find Threads package (needed for std::filesystem on some older GCC/libstdc++)
# Although C++17 should handle it, linking explicitly can help compatibility.
# find_package(Threads REQUIRED)

# --- Source Files ---
# Group source files for better organization in IDEs
file(GLOB SRC_FILES "src/*.cpp")

# --- Include Directories ---
include_directories(include)

# --- Executable Target ---
add_executable(tinyshell ${SRC_FILES})

# --- Link Libraries ---
# Link std::filesystem library if needed (CMake usually handles this for C++17 targets)
# On some older GCC versions, you might need -lstdc++fs explicitly.
# Check if the target platform needs explicit linking for filesystem
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
    # Older GCC might need explicit linking
    target_link_libraries(tinyshell PRIVATE stdc++fs)
endif()

# Link Threads if found and needed (might be required by filesystem implicitly)
# target_link_libraries(tinyshell PRIVATE Threads::Threads)

# --- Platform Specific Settings (Optional) ---
if(WIN32)
    # Windows specific settings if any
    # e.g., set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    # Linux/macOS specific settings
    # e.g., set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

# --- Installation (Optional) ---
# install(TARGETS tinyshell DESTINATION bin)

# --- Output Directory (Optional) ---
# Set output directory for executable (e.g., to build/)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Message indicating configuration is done
message(STATUS "Configuring Tinyshell (Group 1) for C++17")
message(STATUS "Source files: ${SRC_FILES}")
message(STATUS "Executable target: tinyshell")

