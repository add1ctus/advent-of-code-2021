#include <fstream>
#include <iostream>
#include <numeric>
#include <optional>
#include <span>
#include <string_view>
#include <vector>

constexpr uint16_t kWindowSize = 3;
std::string kFilename = "inputs/1-2.txt";

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

std::vector<uint16_t> GetWindows(std::span<const uint16_t> numbers,
                                 uint16_t window_size) {
  uint16_t window_sum =
      std::reduce(numbers.begin(), numbers.begin() + window_size - 1, 0);

  std::vector<uint16_t> windows;
  for (size_t i = window_size - 1; i < numbers.size(); ++i) {
      window_sum += numbers[i];
      windows.push_back(window_sum);
      window_sum -= numbers[i - window_size + 1];
  }

  return windows;
}

int main() {
  std::vector<uint16_t> depths = ReadDepths(kFilename);
  std::vector<uint16_t> windows = GetWindows(depths, kWindowSize);
  uint16_t increases = CountIncreases(windows);
  std::cout << increases;
  return 0;
}