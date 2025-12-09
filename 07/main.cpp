#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "utils.h"
#include <queue>
#include <stack>

unsigned long long Part1(std::istringstream& input) {
    unsigned long long ans = 0;
    std::string line;
    std::vector<std::string> map;

    std::queue<std::pair<int, int>> toDo;

    int y = 0;
    while (std::getline(input, line)) {
        map.push_back(line);
        size_t start = line.find('S');
        if (start != std::string::npos) {
            toDo.push({y, start});
        }
        y++;
    }
    while (!toDo.empty()) {
        auto [y, x] = toDo.front();
        while (y < map.size()) {
            if (map[y][x] == '|') {
                break;
            }
            map[y][x] = '|';
            y++;
            if (y == map.size()) {
                break;
            }
            if (map[y][x] == '^') {
                ans++;
                if (map[y][x+1] != '|') {
                    toDo.push({y, x+1});
                }
                x = x-1;
                if (map[y][x] == '|') {
                    break;
                }
            }
        }
        toDo.pop();
    }
  
    return ans;
}

unsigned long long Part2(std::istringstream& input) {
    unsigned long long ans = 0;
    std::string line;

    std::vector<std::string> map;
    std::vector<std::vector<unsigned long long>> memo;
    std::stack<std::pair<int, int>> toDo;

    std::pair<int, int> startPos;
    int y = 0;
    while (std::getline(input, line)) {
        map.push_back(line);
        memo.push_back(std::vector<unsigned long long>(line.size(), 0));
        size_t start = line.find('S');
        if (start != std::string::npos) {
            toDo.push({y, start});
            startPos = std::make_pair(y, start);
        }
        y++;
    }
    // Populate memo
    while (!toDo.empty()) {
        auto [y, x] = toDo.top();
        toDo.pop();

        if (memo[y][x] > 0) {
            continue;
        }

        if (y + 1 == map.size()) {
            memo[y][x] = 1;
            continue;
        }
        // Split beam
        if (map[y+1][x] == '^') {
            if (memo[y+1][x-1] > 0 && memo[y+1][x+1] > 0) {
                memo[y][x] = memo[y+1][x-1] + memo[y+1][x+1];
            }
            else {
                // Push current node back, then push dependencies
                // Since its a stack, dependencies will be processed before current node
                toDo.push({y, x});
                if (memo[y+1][x-1] == 0) {
                    toDo.push({y+1, x-1});
                }
                if (memo[y+1][x+1] == 0) {
                    toDo.push({y+1, x+1});
                }
            }
        }
        // Move down
        else {
            if (memo[y+1][x] > 0) {
                memo[y][x] = memo[y+1][x];
            }
            else {
                // Push current node back, then push dependencies
                // Since its a stack, dependencies will be processed before current node
                toDo.push({y, x});
                toDo.push({y+1, x});
            }
        }
    }
      
    return memo[startPos.first][startPos.second];
}


int main(int argc, char* argv[]) {
    auto [part1_input, part2_input] = ReadInput();
    
    auto start1 = std::chrono::high_resolution_clock::now();
    unsigned long long part1_answer = Part1(part1_input);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::cout << "Part 1\tAnswer: " << part1_answer << "\tTime: " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count() << " µs" << std::endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    unsigned long long part2_answer = Part2(part2_input);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::cout << "Part 2\tAnswer: " << part2_answer << "\tTime: " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count() << " µs" << std::endl;
    return 0;
}
