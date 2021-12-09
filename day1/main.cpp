#include <limits.h>

#include <fstream>
#include <iostream>
#include <list>
#include <vector>

int main() {
    std::ifstream infile("input.txt");
    std::list<int> window;
    int depth = 0;
    int increase_count = 0;
    while (infile >> depth) {
        window.push_back(depth);
        if (window.size() >= 4) {
            if (window.back() > window.front()) {
                increase_count++;
            }
            window.pop_front();
        }
    }
    std::cout << increase_count;
}
