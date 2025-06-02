#include "../include/environment.hpp"
#include <cstdlib> // For getenv
#include <cctype>  // For isalnum

namespace g1_tinyshell
{

Environment::Environment()
{
    // Initialize with some common environment variables if needed,
    // but primarily manage internal shell variables.
    // Example: Load PATH from system environment initially?
    // For simplicity, start with an empty internal environment.
}

bool Environment::setVariable(const std::string& variable_name, const std::string& value)
{
    if (!isValidVariableName(variable_name))
    {
        return false;
    }
    m_variables[variable_name] = value;
    return true;
}

std::optional<std::string> Environment::getVariable(const std::string& variable_name) const
{
    // First, check internal variables
    auto it = m_variables.find(variable_name);
    if (it != m_variables.end())
    {
        return it->second;
    }

    // Second, check system environment variables (read-only access)
    // Note: This makes system env vars accessible but not modifiable via setvar/unsetvar
    const char* env_value = std::getenv(variable_name.c_str());
    if (env_value != nullptr)
    {
        return std::string(env_value);
    }

    // Variable not found in internal or system environment
    return std::nullopt;
}

bool Environment::unsetVariable(const std::string& variable_name)
{
    if (!isValidVariableName(variable_name))
    {
        return false; // Or maybe allow unsetting invalid names?
                      // Sticking to valid names for consistency.
    }
    auto it = m_variables.find(variable_name);
    if (it != m_variables.end())
    {
        m_variables.erase(it);
        return true;
    }
    return false; // Variable did not exist in the internal map
}

const std::map<std::string, std::string>& Environment::getAllVariables() const
{
    return m_variables;
}

// Basic validation: starts with letter or underscore, followed by letters, numbers, or underscore.
bool Environment::isValidVariableName(const std::string& variable_name)
{
    if (variable_name.empty())
    {
        return false;
    }
    if (!std::isalpha(variable_name[0]) && variable_name[0] != '_')
    {
        return false;
    }
    for (size_t i = 1; i < variable_name.length(); ++i)
    {
        if (!std::isalnum(variable_name[i]) && variable_name[i] != '_')
        {
            return false;
        }
    }
    // Add checks for reserved names if necessary
    return true;
}

}

