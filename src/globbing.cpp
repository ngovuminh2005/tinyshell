#include "globbing.hpp"
#include <windows.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

bool match_pattern_simple(const char *text, const char *pattern) {
    while (*pattern) {
        if (*pattern == '?') {
            if (!*text) return false;
            text++;
            pattern++;
        } else if (*pattern == '*') {
            pattern++;
            if (!*pattern) return true;
            while (*text) {
                if (match_pattern_simple(text, pattern)) return true;
                text++;
            }
            return false;
        } else {
            if (*text != *pattern) return false;
            text++;
            pattern++;
        }
    }
    return !*text;
}

std::vector<std::string> perform_globbing(const std::string& pattern) {
    std::vector<std::string> matches;
    WIN32_FIND_DATAW find_data;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    std::wstring wpattern(pattern.begin(), pattern.end());

    hFind = FindFirstFileW(wpattern.c_str(), &find_data);

    if (hFind == INVALID_HANDLE_VALUE) {
        return matches;
    }

    do {
        if (wcscmp(find_data.cFileName, L".") != 0 && wcscmp(find_data.cFileName, L"..") != 0) {
            std::wstring wfilename = find_data.cFileName;
            int len = WideCharToMultiByte(CP_ACP, 0, wfilename.c_str(), -1, NULL, 0, NULL, NULL);
            if (len > 0) {
                 std::string filename(len - 1, 0);
                 WideCharToMultiByte(CP_ACP, 0, wfilename.c_str(), -1, &filename[0], len, NULL, NULL);
                 matches.push_back(filename);
            } else {
                 std::cerr << "Globbing Warning: Failed to convert filename." << std::endl;
            }
        }
    } while (FindNextFileW(hFind, &find_data) != 0);

    FindClose(hFind);
    std::sort(matches.begin(), matches.end());
    return matches;
}

bool match_pattern(const std::string& text, const std::string& pattern) {
     return match_pattern_simple(text.c_str(), pattern.c_str());
}