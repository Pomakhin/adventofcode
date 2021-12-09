#include <limits.h>
#include <stdint.h>

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct Card {};

std::vector<int> parseStrOfInts(const std::string &str, const char delim) {
    std::vector<int> result;
    std::istringstream ss(str);
    std::string substr;
    while (std::getline(ss, substr, delim)) {
        result.push_back(std::stoi(substr));
        // std::cout << result.back() << ' ';
    }
    // std::cout << '\n';
    return result;
}

std::vector<std::string> parseKeyLine(const std::string &str) {
    std::vector<std::string> result;
    std::string str_left = str.substr(0, str.find('|'));
    std::string str_right = str.substr(str.find('|') + 2);

    std::istringstream ss(str_left);
    std::string substr;
    while (std::getline(ss, substr, ' ')) {
        result.push_back(substr);
        // std::cout << result.back() << ' ';
    }
    std::cout << '\n';

    return result;
}
std::vector<std::string> parseEncodedLine(const std::string &str) {
    std::vector<std::string> result;
    std::string str_left = str.substr(0, str.find('|'));
    std::string str_right = str.substr(str.find('|') + 2);

    std::istringstream ss(str_right);
    std::string substr;
    while (std::getline(ss, substr, ' ')) {
        result.push_back(substr);
        // std::cout << result.back() << ' ';
    }
    std::cout << '\n';

    return result;
}
bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }

int decodeDigit(const std::string &encoded_digit,
                const std::vector<char> &scheme) {
    switch (encoded_digit.size()) {
        case 2:
            return 1;
        case 3:
            return 7;
        case 4:
            return 4;
        case 5:
            if (encoded_digit.find(scheme[2]) != std::string::npos &&
                encoded_digit.find(scheme[5]) != std::string::npos) {
                return 3;
            } else if (encoded_digit.find(scheme[1]) == std::string::npos) {
                return 2;
            } else {
                return 5;
            }
            break;
        case 6:
            if (encoded_digit.find(scheme[2]) == std::string::npos) {
                return 6;
            } else if (encoded_digit.find(scheme[4]) == std::string::npos) {
                return 9;
            } else {
                return 0;
            }
            break;
        case 7:
            return 8;
    }
    return -1000;
}

std::vector<char> findScheme(const std::vector<std::string> &key_values) {
    std::vector<char> result;
    std::vector<char> right_vertical;
    std::vector<char> horizontal;
    for (auto v : key_values) {
        switch (v.size()) {
            case 2:
                break;
            case 4:
                break;
            case 3:
                break;
            case 7:
                break;
        }
        if (v.size() == 2 || v.size() == 4 || v.size() == 3 || v.size() == 7) {
            total_count++;
        }
    }
    return result;
}

int main() {
    std::ifstream infile("input.txt");
    std::string temp_str;
    int total_count = 0;
    while (std::getline(infile, temp_str)) {
        // std::cout << temp_str << '\n';
        if (!temp_str.empty()) {
            std::string::iterator new_end =
                std::unique(temp_str.begin(), temp_str.end(), BothAreSpaces);
            temp_str.erase(new_end, temp_str.end());
            while (temp_str[0] == ' ') {
                temp_str.erase(0, 1);
            }
            std::vector<std::string> key_values = parseKeyLine(temp_str);
            std::vector<char> scheme = findScheme(key_values);
        }
    }
    std::cout << total_count;
}
