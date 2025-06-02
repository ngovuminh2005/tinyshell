#include "../include/expansion.hpp"
#include <sstream>
#include <cctype>

namespace g1_tinyshell
{

std::string Expansion::expandWord(const std::string& word, const Environment& environment, std::string& error_message)
{
    error_message = "";
    return performExpansion(word, environment, error_message);
}

bool Expansion::expandArguments(std::vector<std::string>& arguments, const Environment& environment, std::string& error_message)
{
    error_message = "";
    for (std::string& arg : arguments)
    {
        std::string current_error;
        std::string expanded_arg = performExpansion(arg, environment, current_error);
        if (!current_error.empty())
        {
            error_message = current_error;
            return false;
        }
        arg = expanded_arg;
    }
    return true;
}

std::string Expansion::performExpansion(const std::string& word, const Environment& environment, std::string& error_message)
{
    std::stringstream result_stream;

    for (size_t i = 0; i < word.length(); ++i)
    {
        if (word[i] == '\\')
        {
            if (i + 1 < word.length())
            {
                char next_char = word[i + 1];
                // Trong giai đoạn Expansion, \ chỉ có ý nghĩa đặc biệt nếu nó escape $, ", hoặc \
                // Các \ khác (ví dụ từ đường dẫn C:\Users mà Lexer đã giữ lại) sẽ không khớp điều kiện này.
                if (next_char == '$' || next_char == '"' || next_char == '\\')
                {
                    result_stream << next_char; // Ký tự được escape ($, ", \)
                }
                else
                {
                    // Nếu \ không escape $, ", hoặc \, nó là một phần của dữ liệu (ví dụ: \U trong C:\Users)
                    // Lexer đã phải đảm bảo rằng \ này được giữ lại đúng cách nếu nó không phải là \\ hoặc \"
                    // Vì vậy ở đây, chúng ta chỉ thêm \ và ký tự tiếp theo.
                    result_stream << '\\';
                    result_stream << next_char;
                }
                i++; // Đã xử lý next_char
            }
            else
            {
                result_stream << '\\'; // Dấu \ ở cuối từ
            }
        }
        else if (word[i] == '$')
        {
            std::string var_name;
            size_t start_pos = i + 1;

            if (start_pos < word.length() && word[start_pos] == '{')
            {
                start_pos++; // Bỏ qua '{'
                size_t end_brace_pos = word.find('}', start_pos);
                if (end_brace_pos == std::string::npos)
                {
                    error_message = "Unclosed variable expansion brace starting at index " + std::to_string(i);
                    return ""; // Lỗi mở rộng
                }
                var_name = word.substr(start_pos, end_brace_pos - start_pos);
                i = end_brace_pos; // Di chuyển index qua '}'
            }
            else if (start_pos < word.length() && word[start_pos] == '?')
            {
                 var_name = "?";
                 i = start_pos;
            }
            else
            {
                size_t current_pos = start_pos;
                while (current_pos < word.length() && (std::isalnum(word[current_pos]) || word[current_pos] == '_'))
                {
                    current_pos++;
                }
                if (current_pos == start_pos)
                {
                    result_stream << '$'; // $ đứng một mình hoặc theo sau bởi ký tự không hợp lệ cho tên biến
                    continue;
                }
                var_name = word.substr(start_pos, current_pos - start_pos);
                i = current_pos - 1; // Di chuyển index đến ký tự cuối của tên biến
            }

            std::optional<std::string> value = environment.getVariable(var_name);
            if (value.has_value())
            {
                result_stream << value.value();
            }
            // Nếu không có giá trị (biến không xác định), không thêm gì cả (mở rộng thành chuỗi rỗng)
        }
        else
        {
            result_stream << word[i]; // Ký tự bình thường
        }
    }
    return result_stream.str();
}

}