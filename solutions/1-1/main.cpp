#include <fstream>
#include <iostream>
#include <optional>
#include <span>
#include <string_view>
#include <vector>

std::string kFilename = "inputs/1-1.txt";

std::vector<uint16_t> ReadDepths(std::string &filename) {
  std::ifstream file(filename);
  std::string line;
  std::vector<uint16_t> depths;
  while (std::getline(file, line)) {
    depths.push_back(std::stoi(line));
  }
  return depths;
}

uint16_t CountIncreases(std::span<const uint16_t> numbers) {
  std::optional<uint16_t> previous_number;
  uint16_t increases = 0;
  for (auto number : numbers) {
    if (previous_number.has_value()) {
      if (number > *previous_number) {
        increases++;
      }
    }
    previous_number = number;
  }
  return increases;
}

int main() {
  std::vector<uint16_t> depths = ReadDepths(kFilename);
  uint16_t increases = CountIncreases(depths);
  std::cout << increases;
  return 0;
}