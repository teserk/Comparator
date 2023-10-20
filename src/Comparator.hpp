//
// Created by tamirlan on 20.10.23.
//

#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

namespace fs = std::filesystem;

class Comparator {
 public:
  Comparator(const fs::path& dir1, const fs::path& dir2,
             double similarity_threshold)
      : dir1_(dir1), dir2_(dir2), similarity_threshold_(similarity_threshold) {}

  // Сравнивает две директории и заполняет какие файлы равны по фактору сходства
  void CompareDirectories();

  // Вывод в консоль
  void PrintInConsole();

 private:
  std::vector<std::pair<std::string, std::string>> equal_files_;
  std::vector<std::tuple<std::string, std::string, double>> similar_files_;
  fs::path dir1_;
  fs::path dir2_;
  double similarity_threshold_;

  // Сравнивает два файла и возвращает процент сходства
  static double CompareFiles(const fs::path& path1, const fs::path& path2);
};
