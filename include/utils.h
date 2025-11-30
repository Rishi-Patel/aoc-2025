#pragma once

#include <string>
#include <vector>

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
