#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include "utils.h"


struct Range {
    unsigned long long Start;
    unsigned long long End;
};

bool DoRangesOverlap(const Range& r1, const Range& r2) {
    return std::max(r1.Start, r2.Start) <= std::min(r1.End, r2.End);
}

Range MergeRanges(const Range& r1, const Range& r2) {
    return {std::min(r1.Start, r2.Start), std::max(r1.End, r2.End)};
}

std::vector<Range> MergeOverlappingRanges(std::vector<Range>& ranges) {
    if (ranges.empty()) return {};

    // Sorting saves us from O(n^2) complexity
    std::sort(ranges.begin(), ranges.end(), [](const Range& a, const Range& b) {
        return a.Start < b.Start;
    });

    std::vector<Range> merged;
    merged.push_back(ranges[0]);

    for (size_t i = 1; i < ranges.size(); ++i) {
        if (DoRangesOverlap(merged.back(), ranges[i])) {
            merged.back() = MergeRanges(merged.back(), ranges[i]);
        } else {
            merged.push_back(ranges[i]);
        }
    }

    return merged;
}

unsigned long long Part1(std::istringstream& input) {
    unsigned long long ans = 0;
    std::string line;

    std::vector<Range> ranges;
    while (std::getline(input, line)) {
        if (line.empty()) break;
        auto parts = Split(line, "-");
        ranges.push_back({std::stoull(parts[0]), std::stoull(parts[1])});
    }
    // I dont even think we need this? But whatever, I like reducing the ranges if possible
    ranges = MergeOverlappingRanges(ranges);

    while (std::getline(input, line)) {
        unsigned long long num = std::stoull(line);
        for (const auto& range : ranges) {
            if (num >= range.Start && num <= range.End) {
                ans++;
                break;
            }
        }
    }

    return ans;
}

unsigned long long Part2(std::istringstream& input) {
    unsigned long long ans = 0;
    std::string line;

    std::vector<Range> ranges;
    while (std::getline(input, line)) {
        if (line.empty()) break;
        auto parts = Split(line, "-");
        ranges.push_back({std::stoull(parts[0]), std::stoull(parts[1])});
    }
    ranges = MergeOverlappingRanges(ranges);

    for (const auto& range : ranges) {
        ans += (range.End - range.Start + 1);
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
