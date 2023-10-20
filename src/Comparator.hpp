//
// Created by tamirlan on 20.10.23.
//

#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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

  // Получить одинаковые файлы
  std::vector<std::pair<fs::directory_entry, fs::directory_entry>>
  GetEqualFiles() const;

  // Получить одинаковые файлы
  std::vector<std::tuple<fs::directory_entry, fs::directory_entry, double>>
  GetSimilarFiles() const;

  // Сравнивает два файла и возвращает процент сходства
  static double CompareFiles(const fs::path& path1, const fs::path& path2);

 private:
  std::vector<std::pair<fs::directory_entry, fs::directory_entry>> equal_files_;
  std::vector<std::tuple<fs::directory_entry, fs::directory_entry, double>>
      similar_files_;
  fs::path dir1_;
  fs::path dir2_;
  double similarity_threshold_;

  // Расстояние Левенштейна, нужно для сравнения файлов
  static size_t LevensteinDistance(const std::string& str1,
                                   const std::string& str2);

  // Выводит в консоль одинаковые файлы
  void PrintEqualFiles();

  // Выводит в консоль похожие файлы
  void PrintSimilar();

  // Выводит в консоль файлы которые есть только в 1 директории
  void PrintOnlyInDir1();

  // Выводит в консоль файлы которые есть только в 2 директории
  void PrintOnlyInDir2();
};
