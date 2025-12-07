#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "utils.h"
#include <numeric>

unsigned long long Part1(std::istringstream& input) {
    unsigned long long ans = 0;
    std::string line;

    std::vector<std::pair<unsigned long long, unsigned long long>> problemAns;
    while (std::getline(input, line)) {
        std::stringstream ss(line);
        std::string word;
        int problemIndex = 0;
        while (ss >> word) {
            
            if (word == "+") {
                ans += problemAns[problemIndex].first;
            }
            else if (word == "*") {
                ans += problemAns[problemIndex].second;
            }
            else {
                unsigned long long val = std::stoull(word);
                if (problemAns.size() <= problemIndex) {
                    problemAns.push_back({val, val});
                } else {
                    problemAns[problemIndex].first += val;
                    problemAns[problemIndex].second *= val;
                }
            }
            problemIndex++;
        }
    }

    return ans;
}

// Probable performance improvements if we didnt do it column by column (i.e. per problem) bc we are then going through each line mulitple times, reading a subset of columns each time.
// Maybe change to do a vector of vectors of numbers, and iterate through the lines. Woudl require changing ComputeProblemAns since this assume we're working on a single set of column (range).
unsigned long long ComputeProblemAns(const std::vector<std::string>& lines, const std::pair<size_t, size_t>& range, char op) {
    const auto& [start, end] = range;
    // Each column is a number, and there are end - start + 1 columns
    std::vector<unsigned long long> nums(end - start + 1, 0);
    
    for (const auto& line : lines) {
        int numIndex = 0;
        for (int i = start; i <= end; i++) {
            if (line[i] == ' ') {
                numIndex++;
                continue;
            }
            nums[numIndex] = nums[numIndex] * 10 + (line[i] - '0');
            numIndex++;
        }
    }

    return op == '+' ? std::accumulate(nums.begin(), nums.end(), 0ULL) : 
                    std::accumulate(nums.begin(), nums.end(), 1ULL, std::multiplies<unsigned long long>());

}

unsigned long long Part2(std::istringstream& input) {
    unsigned long long ans = 0;
    std::string line;

    std::vector<std::string> lines;

    // For each problem (columns), store the largest index range for the numbers in that problem.
    // E.g.
    // 1   74  123
    //  23 12   43
    // 123 1   23
    // numIndices[0] = {0, 2}
    // numIndices[1] = {4, 5}
    // numIndices[2] = {7, 9}
    std::vector<std::pair<size_t, size_t>> numIndices;

    while (std::getline(input, line)) {
        int problemIndex = 0;
        if (line[0] != '+' && line[0] != '*') {
            lines.push_back(line);
        }
        for (int i = 0; i < line.size(); i++) {
            if (line[i] >= '0' && line[i] <= '9') {
                size_t start = i;
                while (i < line.size() && line[i] != ' ') {
                    i++;
                }
                size_t end = i - 1;
                if (numIndices.size() <= problemIndex) {
                    numIndices.push_back({start, end});
                } else {
                    numIndices[problemIndex].first = std::min(numIndices[problemIndex].first, start);
                    numIndices[problemIndex].second = std::max(numIndices[problemIndex].second, end);
                }
                problemIndex++;
            }
            if (line[i] == '+' || line[i] == '*') {
                ans += ComputeProblemAns(lines, numIndices[problemIndex], line[i]);
                problemIndex++;
            }
        }
    }
    
    return ans;
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
