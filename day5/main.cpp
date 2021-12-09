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

using namespace std;

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

struct Point {
    int x = 0;
    int y = 0;
};

struct Line {
    Point p1;
    Point p2;

    void print() {
        cout << "p1:" << p1.x << ',' << p1.y << " p2:" << p2.x << ',' << p2.y
             << '\n';
    }
};

Line parseLine(const std::string &str) {
    // std::cout << "parseLine: " << str << '\n';
    Line result;
    string p1str = str.substr(0, str.find('-') - 1);
    // cout << p1str << '\n';
    int p1x = stoi(p1str.substr(0, p1str.find(',')));
    int p1y = stoi(p1str.substr(p1str.find(',') + 1));
    result.p1.x = p1x;
    result.p1.y = p1y;
    string p2str = str.substr(str.find('>') + 2);
    // cout << p2str << '\n';
    int p2x = stoi(p2str.substr(0, p2str.find(',')));
    int p2y = stoi(p2str.substr(p2str.find(',') + 1));
    result.p2.x = p2x;
    result.p2.y = p2y;
    result.print();

    return result;
}

bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }

int main() {
    vector<vector<int>> field(1000, vector<int>(1000));
    std::ifstream infile("input.txt");
    std::string temp_str;
    int total_count = 0;
    int min = INT_MAX;
    int max = INT_MIN;
    while (std::getline(infile, temp_str)) {
        if (!temp_str.empty()) {
            std::string::iterator new_end =
                std::unique(temp_str.begin(), temp_str.end(), BothAreSpaces);
            temp_str.erase(new_end, temp_str.end());
            while (temp_str[0] == ' ') {
                temp_str.erase(0, 1);
            }
            Line l = parseLine(temp_str);
            if (l.p1.x > max) {
                max = l.p1.x;
            }
            if (l.p1.y > max) {
                max = l.p1.y;
            }
            if (l.p2.x > max) {
                max = l.p2.x;
            }
            if (l.p2.y > max) {
                max = l.p2.y;
            }
            if (l.p1.x < min) {
                min = l.p1.x;
            }
            if (l.p1.y < min) {
                min = l.p1.y;
            }
            if (l.p2.x < min) {
                min = l.p2.x;
            }
            if (l.p2.y < min) {
                min = l.p2.y;
            }
            if (l.p1.x == l.p2.x) {
                int b = std::min(l.p1.y, l.p2.y);
                int e = std::max(l.p1.y, l.p2.y);
                for (int y = b; y <= e; y++) {
                    field[y][l.p1.x]++;
                    if (field[y][l.p1.x] == 2) {
                        total_count++;
                    }
                }
            } else if (l.p1.y == l.p2.y) {
                int b = std::min(l.p1.x, l.p2.x);
                int e = std::max(l.p1.x, l.p2.x);
                for (int x = b; x <= e; x++) {
                    field[l.p2.y][x]++;
                    if (field[l.p2.y][x] == 2) {
                        total_count++;
                    }
                }
            } else {
                int x_b = std::min(l.p1.x, l.p2.x);
                int x_e = std::max(l.p1.x, l.p2.x);
                int y_b = std::min(l.p1.y, l.p2.y);
                int y_e = std::max(l.p1.y, l.p2.y);
                int x = l.p1.x;
                int y = l.p1.y;
                while (true) {
                    field[y][x]++;
                    if (field[y][x] == 2) {
                        total_count++;
                    }
                    if (x == l.p2.x || y == l.p2.y) {
                        break;
                    }
                    if (l.p1.x < l.p2.x) {
                        x++;
                    } else {
                        x--;
                    }
                    if (l.p1.y < l.p2.y) {
                        y++;
                    } else {
                        y--;
                    }
                }
            }
        }
    }
    cout << "min=" << min << " max=" << max << '\n';
    cout << total_count << '\n';
}
