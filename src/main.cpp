#include <algorithm>
#include <filesystem>
#include <fstream>

#include "Comparator.hpp"

namespace fs = std::filesystem;

int main(int argc, char** argv) {
  if (argc < 3 || (std::stod(argv[3]) < 0 || std::stod(argv[3]) > 100.0)) {
    std::cerr << "USAGE: ./comparator first_directory second_directory "
                 "similarity_threshold(from 0 to 100)";
    return 1;
  }
  fs::path dir1 = argv[1];
  fs::path dir2 = argv[2];
  double similarity_threshold = std::stod(argv[3]);

  Comparator comparator(dir1, dir2, similarity_threshold);
  comparator.CompareDirectories();
  comparator.PrintInConsole();
  return 0;
}
