#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "utils.h"
#include <queue>
#include <unordered_map>

struct JunctionBox { 
    unsigned long long x;
    unsigned long long y;
    unsigned long long z;
    size_t circuitId;
};

struct Distance {
    unsigned long long distance;
    size_t j1;
    size_t j2;

    bool operator<(const Distance& other) const {
        return distance > other.distance;
    }
};

unsigned long long Part1(std::istringstream& input) {
    unsigned long long ans = 1;
    std::string line;
    
    std::vector<JunctionBox> junctionBoxes;
    std::unordered_map<size_t, std::vector<size_t>> circuitToJunctions;
    std::priority_queue<Distance> distances;
    
    while (std::getline(input, line)) {
        auto coords = Split(line, ",");
        junctionBoxes.push_back({std::stoul(coords[0]), std::stoul(coords[1]), std::stoul(coords[2]), junctionBoxes.size()});
        circuitToJunctions[junctionBoxes.size() - 1] = {junctionBoxes.size() - 1};
    }

    for (size_t i = 0; i < junctionBoxes.size(); i++) {
        for (size_t j = i+1; j < junctionBoxes.size(); j++) {
            long long dx = (long long)junctionBoxes[i].x - (long long)junctionBoxes[j].x;
            long long dy = (long long)junctionBoxes[i].y - (long long)junctionBoxes[j].y;
            long long dz = (long long)junctionBoxes[i].z - (long long)junctionBoxes[j].z;
            unsigned long long dist = dx * dx + dy * dy + dz * dz;
            distances.push({dist, i, j});
        }
    }
    for (size_t i = 0; i < 1000; i++) {
        auto [distance, j1, j2] = distances.top();
        distances.pop();
        // std::cout << "Connecting " << j1 << " and " << j2 << std::endl;
        if (junctionBoxes[j1].circuitId == junctionBoxes[j2].circuitId) {
            continue;
        }
        // std::cout << "Connecting circuit " << junctionBoxes[j1].circuitId << " and " << junctionBoxes[j2].circuitId << std::endl;
        auto oldCircuitId = junctionBoxes[j2].circuitId;
        for (auto& junction : circuitToJunctions[junctionBoxes[j2].circuitId]) {
            circuitToJunctions[junctionBoxes[j1].circuitId].push_back(junction);
            junctionBoxes[junction].circuitId = junctionBoxes[j1].circuitId;
        }
        // std::cout << "Erasing circuit " << oldCircuitId << std::endl;
        circuitToJunctions.erase(oldCircuitId);
    }

    // Get the 3 largest circuits
    std::vector<size_t> circuitSizes;
    for (auto& circuit : circuitToJunctions) {
        circuitSizes.push_back(circuit.second.size());
    }
    std::sort(circuitSizes.begin(), circuitSizes.end(), std::greater<size_t>());
    ans = circuitSizes[0] * circuitSizes[1] * circuitSizes[2];

    return ans;
}

unsigned long long Part2(std::istringstream& input) {
    unsigned long long ans = 1;
    std::string line;
    
    std::vector<JunctionBox> junctionBoxes;
    std::unordered_map<size_t, std::vector<size_t>> circuitToJunctions;
    std::priority_queue<Distance> distances;
    
    while (std::getline(input, line)) {
        auto coords = Split(line, ",");
        junctionBoxes.push_back({std::stoul(coords[0]), std::stoul(coords[1]), std::stoul(coords[2]), junctionBoxes.size()});
        circuitToJunctions[junctionBoxes.size() - 1] = {junctionBoxes.size() - 1};
    }

    for (size_t i = 0; i < junctionBoxes.size(); i++) {
        for (size_t j = i+1; j < junctionBoxes.size(); j++) {
            long long dx = (long long)junctionBoxes[i].x - (long long)junctionBoxes[j].x;
            long long dy = (long long)junctionBoxes[i].y - (long long)junctionBoxes[j].y;
            long long dz = (long long)junctionBoxes[i].z - (long long)junctionBoxes[j].z;
            unsigned long long dist = dx * dx + dy * dy + dz * dz;
            distances.push({dist, i, j});
        }
    }


    while (!distances.empty()) {
        auto [distance, j1, j2] = distances.top();
        distances.pop();
        // std::cout << "Connecting " << j1 << " and " << j2 << std::endl;
        if (junctionBoxes[j1].circuitId == junctionBoxes[j2].circuitId) {
            continue;
        }
        // std::cout << "Connecting circuit " << junctionBoxes[j1].circuitId << " and " << junctionBoxes[j2].circuitId << std::endl;
        auto oldCircuitId = junctionBoxes[j2].circuitId;
        for (auto& junction : circuitToJunctions[junctionBoxes[j2].circuitId]) {
            circuitToJunctions[junctionBoxes[j1].circuitId].push_back(junction);
            junctionBoxes[junction].circuitId = junctionBoxes[j1].circuitId;
        }
        // std::cout << "Erasing circuit " << oldCircuitId << std::endl;
        circuitToJunctions.erase(oldCircuitId);

        if (circuitToJunctions.size() == 1) {
            ans = junctionBoxes[j1].x * junctionBoxes[j2].x;
            break;
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
