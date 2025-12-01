#pragma once

#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> Split(const std::string& s,
                               const std::string& delimiter) {
  std::vector<std::string> result;

  size_t start = 0;
  size_t end = end = s.find(delimiter, start);
  while (end != std::string::npos) {
    auto substr = s.substr(start, end - start);
    if (!substr.empty()) {
      result.emplace_back(substr);
    }
    if (end == s.size() - 1) {
      break;
    }
    start = end + delimiter.size();
    end = s.find(delimiter, start);
  }
  auto substr = s.substr(start, end - start);
  if (!substr.empty()) {
    result.emplace_back(substr);
  }
  return result;
}

// Duplicate cin to two istreams for part 1 and 2
std::pair<std::istringstream, std::istringstream> ReadInput() {
  std::string input((std::istreambuf_iterator<char>(std::cin)),
                   std::istreambuf_iterator<char>());
  return std::make_pair<std::istringstream, std::istringstream>(std::istringstream(input), std::istringstream(input));
}
