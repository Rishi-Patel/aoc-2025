#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "utils.h"


// For part 1, an invalid is is one where the first half is equal to the second half
bool IsInvalidID_Part1(unsigned long long id) {
    auto idStr = std::to_string(id);
    size_t len = idStr.length();
    if (len % 2 != 0) {
        return false;
    }
    return idStr.substr(0, len / 2) == idStr.substr(len / 2);
}


unsigned long long Part1(std::istringstream& input) {
    std::string line;
    std::getline(input, line);
    
    std::vector<std::string> ranges = Split(line, ",");
    
    unsigned long long invalidSum = 0;
    
    for (const auto& range : ranges) {
        unsigned long long start = std::stoull(range.substr(0, range.find("-")));
        unsigned long long end = std::stoull(range.substr(range.find("-") + 1));
        // idk man, feel like theres a smarter way to do this but lets just check every id
        for (unsigned long long id = start; id <= end; id++) {
            if (IsInvalidID_Part1(id)) {
                invalidSum += id;
            }
        }
    }
    
    return invalidSum;
}

// For part 2, its a more generalized version of the part 1 check. Instead of checking if the first half == second half,
// check each substring from length 1 to half the length is repeated. If any of them are, then the id is invalid.
bool IsInvalidID_Part2(unsigned long long id) {
    auto idStr = std::to_string(id);
    for (int repeatedSegmentLen = 1; repeatedSegmentLen <= idStr.length() / 2; repeatedSegmentLen++) {
        if (idStr.length() % repeatedSegmentLen != 0) {
            continue;
        }
        bool isRepeat = true;
        for (int i = repeatedSegmentLen; i < idStr.length(); i += repeatedSegmentLen) {
            isRepeat &= idStr.substr(i-repeatedSegmentLen, repeatedSegmentLen) == idStr.substr(i, repeatedSegmentLen);
            if (!isRepeat) {
                break;
            }
        }
        if (isRepeat) {
            return true;
        }
    }
    return false;
}

unsigned long long Part2(std::istringstream& input) {
    std::string line;
    std::getline(input, line);
    
    std::vector<std::string> ranges = Split(line, ",");
    
    unsigned long long invalidSum = 0;
    
    for (const auto& range : ranges) {
        unsigned long long start = std::stoull(range.substr(0, range.find("-")));
        unsigned long long end = std::stoull(range.substr(range.find("-") + 1));
        // idk man, feel like theres a smarter way to do this but lets just check every id
        for (unsigned long long id = start; id <= end; id++) {
            if (IsInvalidID_Part2(id)) {
                invalidSum += id;
            }
        }
    }
    
    return invalidSum;
}

int main(int argc, char* argv[]) {
    auto [part1_input, part2_input] = ReadInput();
    
    auto start = std::chrono::high_resolution_clock::now();
    unsigned long long part1_answer = Part1(part1_input);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::cout << "Part 1\tAnswer: " << part1_answer << "\tTime: " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start).count() << " µs" << std::endl;

    unsigned long long part2_answer = Part2(part2_input);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::cout << "Part 2\tAnswer: " << part2_answer << "\tTime: " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - end1).count() << " µs" << std::endl;
    return 0;
}
