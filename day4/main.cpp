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
bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }

int main() {
    std::ifstream infile("input.txt");
    std::string first_str;
    std::getline(infile, first_str);
    std::vector<int> moves = parseStrOfInts(first_str, ',');
    std::string temp_str;
    std::vector<std::pair<std::vector<int>, int>> seqs;
    std::unordered_map<int, std::list<int>> m;
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
            std::vector<int> row = parseStrOfInts(temp_str, ' ');
            total_count += row.size();
            seqs.push_back({row, 0});
            std::cout << "row: ";
            for (auto v : row) {
                m[v].push_back(seqs.size() - 1);
                std::cout << v << ' ';
            }
            std::cout << '\n';
        }
        if (seqs.size() % 5 == 0 && seqs.size() % 10 != 0) {
            int cached_seq_size = seqs.size();
            for (int j = 0; j < 5; j++) {
                std::vector<int> column;
                for (int i = cached_seq_size - 5; i < cached_seq_size; i++) {
                    // std::cout << "i = " << i << " j = " << j
                    //           << " seqs[i].first[j] = " << seqs[i].first[j]
                    //           << '\n';
                    column.push_back(seqs[i].first[j]);
                }
                seqs.push_back({column, 0});
                std::cout << "column: ";
                for (auto v : column) {
                    m[v].push_back(seqs.size() - 1);
                    std::cout << v << ' ';
                }
                std::cout << '\n';
            }
        }
    }
    std::cout << seqs.size() << '\n';
    std::cout << total_count << '\n';

    bool is_found = false;
    int winner_id = -1;
    int win_move = -1;
    std::set<int> track_of_winners;
    for (int i = 0; i < 100; i++)
    {
        track_of_winners.insert(i);
    }
    for (auto move : moves) {
        if (is_found) {
            break;
        }
        std::cout << "move : " << move << '\n';
        auto it = m.find(move);
        if (it != m.end()) {
            for (auto seq_id : (*it).second) {
                seqs[seq_id].second++;
                if (seqs[seq_id].second >= 5 && track_of_winners.find(seq_id / 10) != track_of_winners.end()) {
                    track_of_winners.erase(seq_id / 10);
                    if (track_of_winners.empty())
                    {
                        is_found = true;
                        winner_id = seq_id / 10;
                        win_move = move;
                        std::cout << "WINNER! " << seq_id / 10 << '\n';
                        break;
                    }
                }
            }
        }
    }
    if (is_found) {
        std::set<int> winner_values;
        for (int i = winner_id * 10; i < winner_id * 10 + 5; i++) {
            for (auto v : seqs[i].first) {
                winner_values.insert(v);
            }
        }
        for (auto move : moves) {
            winner_values.erase(move);
            if (move == win_move) {
                break;
            }
        }
        int sum = 0;
        for (auto v : winner_values)
        {
            sum += v;
        }
        int result = sum * win_move;
        std::cout << "result = " << result << '\n';
    }

}
