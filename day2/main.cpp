#include <limits.h>

#include <fstream>
#include <iostream>
#include <list>
#include <stdint.h>
#include <string>
#include <vector>

int main() {
    std::ifstream infile("input.txt");
    int64_t result;
    std::string value_str;
    while (infile >> value_str) {
        int64_t value_int = 0; 
        for (int i = 0; i < value_str.size(); i++)
        {
            if (value_str[value_str.size() - i - 1] == '1')
            {
                value_int += (i << 1);
            }
        }
    }
    std::cout << result;
}
