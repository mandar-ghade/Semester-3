#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

enum Error {
    NO_COMMAS,
    TOO_MANY_COMMAS,
    NO_INTEGER_AFTER_COMMA,
};

void print_you_entered(std::string text) {
    std::cout << "You entered: " << text << "\n";
}

std::string get_title() {
    std::string title;
    std::cout << "Enter a title for the data:\n";
    getline(std::cin, title);
    print_you_entered(title);
    return title;
}

std::string get_column(int num) {
    std::string column_header;
    std::cout << "Enter the column " << num << " header:\n";
    getline(std::cin, column_header);
    print_you_entered(column_header);
    return column_header;
}

bool has_integer_after_comma(const std::string& str) {
    size_t i = str.find(',') + 1;
    while (i < str.size() && std::isspace(str[i])) i++;
    if (i >= str.size()) return false;
    std::string substr = str.substr(i, str.size() - i);
    try {
        int _ = std::stoi(substr);
        return true;
    } catch (std::invalid_argument) {
        return false;
    }
}

bool has_many_commas(const std::string& str) {
    int count = 0;
    for (char c: str) {
        if (c == ',') count++;
        if (count > 1) return true;
    }
    return false;
}

Error get_error(const std::string& str) {
    if (str.find(',') == std::string::npos) {
        return NO_COMMAS;
    } else if (has_many_commas(str)) {
        return TOO_MANY_COMMAS;
    } else if (!has_integer_after_comma(str)) {
        return NO_INTEGER_AFTER_COMMA;
    } else {
        throw std::runtime_error("?");
    }
}

bool check_valid_data_point(const std::string& point) {
    return point.find(',') != std::string::npos 
        && !has_many_commas(point) 
        && has_integer_after_comma(point);
}

std::pair<std::string, int> parse(const std::string& str) {
    size_t c_idx = str.find(',');
    if (c_idx == std::string::npos) {
        throw std::runtime_error("Comma not found");
    }
    std::string name = str.substr(0, c_idx++);
    while (c_idx < str.size() && std::isspace(str[c_idx])) c_idx++;
    std::string value_str = str.substr(c_idx, str.size() - c_idx);
    int value = 0;
    try {
        value = std::stoi(value_str);
    } catch (std::invalid_argument) {
        throw std::runtime_error("Integer not parsable");
    }
    return { name, value };
}

std::string err_type_to_string(Error err) {
    switch (err) {
        case NO_COMMAS: 
            return "Error: No comma in string.";
        case TOO_MANY_COMMAS:
            return "Error: Too many commas in input.";
        case NO_INTEGER_AFTER_COMMA:
            return "Error: Comma not followed by an integer.";
    }
}

std::string take_data_point() {
    std::string data;
    std::cout << "Enter a data point (-1 to stop input):\n";
    getline(std::cin, data);
    return data;
}

void view_as_table(
    const std::string& title,
    const std::string& column_1,
    const std::string& column_2,
    const std::vector<std::string> string_data,
    const std::vector<int> numeric_data
) {
    std::cout << std::right << std::setw(33) << title << '\n'
              << std::left << std::setw(20) << column_1 << '|'
              << std::right << std::setw(23) << column_2 << '\n'
              << std::setfill('-') << std::setw(45) << '\n';
    // assumes vector lengths are equal
    for (size_t row = 0; row < string_data.size(); row++) {
        std::cout << std::setfill(' ') 
                  << std::left << std::setw(20) << string_data[row] << '|' 
                  << std::right << std::setw(23) << numeric_data[row] << '\n';
    }
    std::cout << '\n';
}

void view_as_histogram(
    const std::vector<std::string> string_data,
    const std::vector<int> numeric_data
) {
    for (size_t row = 0; row < string_data.size(); row++) {
        std::cout << std::setfill(' ') << std::right << std::setw(20) << string_data[row] << ' '
                  << std::setfill('*') << std::setw(numeric_data[row] + 1) << '\n';
    }
}

int main()
{
   
   /* Overall flow of the program:
   Get some input for the title
   Get some input for column header #1
   Get some input for column header #2
   
   Until the user types "-1":
   Get input for a string
   Validate input
   If valid...
      Split
      Validate second half of input
      If also valid...
         Store separate pieces
   
   Print out data in table format
   
   Print out data in chart format
   */
// WRITE YOUR CODE HERE
    
    std::string title = get_title();
    std::string column_1 = get_column(1);
    std::string column_2 = get_column(2);
    std::vector<std::string> string_data;
    std::vector<int> int_data;
    while (true) {
        const std::string point = take_data_point();
        if (point == "-1") {
            break;
        }
        if (!check_valid_data_point(point)) {
            std::cout << err_type_to_string(get_error(point)) << '\n';
            continue;
        }
        auto output = parse(point);
        std::string name = output.first;
        int value = output.second;

        string_data.push_back(name);
        int_data.push_back(value);
        
        std::cout << "Data string: " << name << '\n'
                  << "Data integer: " << value << '\n';
    }
    std::cout << '\n';
    view_as_table(title, column_1, column_2, string_data, int_data);
    view_as_histogram(string_data, int_data);
}
