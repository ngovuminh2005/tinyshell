#pragma once

#include "tinyshell_globals.hpp"
#include "environment.hpp"
#include <string>
#include <vector>

namespace g1_tinyshell
{

class Expansion
{
public:
    // Performs variable expansion on a single word/token.
    // Takes the word and the current environment.
    // Returns the expanded string or an error message.
    static std::string expandWord(const std::string& word, const Environment& environment, std::string& error_message);

    // Performs variable expansion on a list of words/arguments.
    // Modifies the list in place.
    // Returns true on success, false if an expansion error occurred.
    static bool expandArguments(std::vector<std::string>& arguments, const Environment& environment, std::string& error_message);

private:
    // Helper to handle $VAR and ${VAR} syntax within a word.
    static std::string performExpansion(const std::string& word, const Environment& environment, std::string& error_message);
};

}

