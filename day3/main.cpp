#include <limits.h>
#include <stdint.h>

#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

int main() {
    std::ifstream infile("input.txt");
    std::string value_str;
    std::vector<int> ones;
    ones.resize(12);
    int total_count = 0;
    std::list<uint64_t> data;
    while (infile >> value_str) {
        total_count++;
        int64_t value_int = 0;
        for (int i = 0; i < value_str.size(); i++) {
            if (value_str[value_str.size() - i - 1] == '1') {
                ones[i]++;
                value_int += (1 << i);
            }
        }
        data.push_back(value_int);
        std::cout << value_str << ' ' << value_int << '\n';
    }
    for (int i = 11; i >= 0; i--) {
        int ones_count = 0;
        for (uint64_t v : data) {
            if (v & (1 << i)) {
                ones_count++;
            }
        }
        bool keep_ones = ones_count * 2 < data.size();
        for (auto it = data.begin(); it != data.end();) {
            if ((*it) & (1 << i)) {
                if (keep_ones) {
                    ++it;
                } else {
                    it = data.erase(it);
                }
            } else {
                if (keep_ones) {
                    it = data.erase(it);
                } else {
                    ++it;
                }
            }
        }
        std::cout << "data.size() = " << data.size() << '\n';
        if (data.size() == 1) {
            break;
        }
    }

    std::cout << data.size() << " " << data.front();
}
