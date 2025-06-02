#pragma once

#include "tinyshell_globals.hpp"
#include <string>
#include <map>
#include <optional> // To return optional values for getVar

namespace g1_tinyshell
{

class Environment
{
public:
    Environment();

    // Sets or updates an internal shell variable.
    // Returns true on success, false on invalid variable name.
    bool setVariable(const std::string& variable_name, const std::string& value);

    // Gets the value of an internal shell variable.
    // Returns the value if found, std::nullopt otherwise.
    std::optional<std::string> getVariable(const std::string& variable_name) const;

    // Removes an internal shell variable.
    // Returns true if the variable existed and was removed, false otherwise.
    bool unsetVariable(const std::string& variable_name);

    // Retrieves the entire variable map (e.g., for expansion or debugging).
    const std::map<std::string, std::string>& getAllVariables() const;

    // Validates if a variable name is acceptable.
    static bool isValidVariableName(const std::string& variable_name);

private:
    std::map<std::string, std::string> m_variables;
    // Could add parent environment pointer for scoping later if needed
};

}

