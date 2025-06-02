#ifndef GLOBBING_HPP
#define GLOBBING_HPP

#include <string>
#include <vector>

// Function to perform filename globbing
// Takes a pattern (potentially with *, ?, [...]) and returns matching filenames.
std::vector<std::string> perform_globbing(const std::string& pattern);

// Helper function to match a single filename against a pattern (basic implementation)
// This might not be needed if using FindFirstFile directly with the pattern.
bool match_pattern(const std::string& text, const std::string& pattern);

#endif // GLOBBING_HPP

