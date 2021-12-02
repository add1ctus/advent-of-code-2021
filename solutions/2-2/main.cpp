#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string kFilename = "inputs/2-1.txt";

std::vector<std::string> SplitBySpaces(std::string input_string) {
  std::stringstream ss(input_string);
  std::string word;
  std::vector<std::string> words;
  while (ss >> word) {
    words.push_back(word);
  }
  return words;
}

enum struct Direction { Forward, Down, Up };

struct Instruction {
  Instruction(std::string input_line) {
    std::vector<std::string> words = SplitBySpaces(input_line);
    if (words[0] == "forward") {
      direction = Direction::Forward;
    } else if (words[0] == "down") {
      direction = Direction::Down;
    } else if (words[0] == "up") {
      direction = Direction::Up;
    }
    distance = std::stoi(words[1]);
  }
  Direction direction;
  int32_t distance;
};

class Position {
public:
  void ApplyInstruction(const Instruction &instruction) {
    switch (instruction.direction) {
    case Direction::Forward: {
      horizontal += instruction.distance;
      depth += instruction.distance * aim;
      break;
    }
    case Direction::Up: {
      aim -= instruction.distance;
      break;
    }
    case Direction::Down: {
      aim += instruction.distance;
      break;
    }
    }
  }

  int32_t getDepth() { return depth; }

  int32_t getHorizontal() { return horizontal; }

private:
  int32_t depth = 0;
  int32_t horizontal = 0;
  int32_t aim = 0;
};

std::vector<Instruction> ReadInstructions(std::string &filename) {
  std::ifstream file(filename);
  std::string line;
  std::vector<Instruction> instructions;
  while (std::getline(file, line)) {
    instructions.emplace_back(line);
  }
  return instructions;
}

int main() {
  std::vector<Instruction> instructions = ReadInstructions(kFilename);
  Position position;
  for (const auto &instruction : instructions) {
    position.ApplyInstruction(instruction);
  }
  std::cout << position.getDepth() * position.getHorizontal();
  return 0;
}
