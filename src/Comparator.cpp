//
// Created by tamirlan on 20.10.23.
//

#include "Comparator.hpp"

void Comparator::CompareDirectories() {
  for (const auto& entry1 : fs::directory_iterator(dir1_)) {
    if (!fs::is_regular_file(entry1)) {
      continue;
    }
    for (const auto& entry2 : fs::directory_iterator(dir2_)) {
      if (!fs::is_regular_file(entry2)) {
        continue;
      }
      double similarity = CompareFiles(entry1.path(), entry2.path());
      if (similarity >= 100.0) {
        equal_files_.emplace_back(entry1.path(), entry2.path());
      } else if (similarity >= similarity_threshold_) {
        similar_files_.emplace_back(entry1.path(), entry2.path(), similarity);
      }
    }
  }
}

void Comparator::PrintInConsole() {
  std::cout << "Equal files:" << std::endl;
  for (const auto& [file1, file2] : equal_files_) {
    std::cout << file1 << " - " << file2 << std::endl;
  }
  std::cout << std::endl;

  std::cout << "Similar files:" << std::endl;
  for (const auto& [file1, file2, similarity] : similar_files_) {
    std::cout << file1 << " - " << file2 << " - " << similarity << "%"
              << std::endl;
  }
  std::cout << std::endl;

  std::cout << "Files only in dir1:" << std::endl;
  for (const auto& file : fs::directory_iterator(dir1_)) {
    bool only_in_dir1 = true;
    for (const auto& [file1, file2] : equal_files_) {
      if (file1 == file.path()) {
        only_in_dir1 = false;
      }
    }
    for (const auto& [file1, file2, similarity] : similar_files_) {
      if (file1 == file.path()) {
        only_in_dir1 = false;
      }
    }
    if (only_in_dir1) {
      std::cout << file.path() << std::endl;
    }
  }
  std::cout << std::endl;

  std::cout << "Files only in dir2:" << std::endl;
  for (const auto& file : fs::directory_iterator(dir2_)) {
    bool only_in_dir2 = true;
    for (const auto& [file1, file2] : equal_files_) {
      if (file2 == file.path()) {
        only_in_dir2 = false;
      }
    }
    for (const auto& [file1, file2, similarity] : similar_files_) {
      if (file2 == file.path()) {
        only_in_dir2 = false;
      }
    }
    if (only_in_dir2) {
      std::cout << file.path() << std::endl;
    }
  }
  std::cout << std::endl;
}

double Comparator::CompareFiles(const fs::path& path1, const fs::path& path2) {
  std::ifstream file1(path1, std::ios::binary);
  std::ifstream file2(path2, std::ios::binary);

  if (!file1 || !file2) {
    return 0.0;
  }

  std::vector<char> content1(std::istreambuf_iterator<char>(file1), {});
  std::vector<char> content2(std::istreambuf_iterator<char>(file2), {});

  unsigned long max_size = std::max(content1.size(), content2.size());
  unsigned long min_size = std::min(content1.size(), content2.size());

  if (max_size == 0) {
    return 0.0;
  }

  unsigned long matching_bytes = 0;
  for (unsigned long i = 0; i < min_size; ++i) {
    if (content1[i] == content2[i]) {
      matching_bytes++;
    }
  }

  return static_cast<double>(matching_bytes) / max_size * 100.0;
}