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

double Comparator::CompareFiles(const fs::path& path1, const fs::path& path2) {
  std::ifstream file1(path1, std::ios::binary);
  std::ifstream file2(path2, std::ios::binary);

  if (!file1.is_open() || !file2.is_open()) {
    std::cerr << "Ошибка открытия файлов." << std::endl;
    return 0.0;
  }

  std::string content1(std::istreambuf_iterator<char>(file1), {});
  std::string content2(std::istreambuf_iterator<char>(file2), {});

  int max_size = std::max(content1.size(), content2.size());
  return (1 - (static_cast<double>(LevensteinDistance(content1, content2)) /
         max_size)) * 100;
}

size_t Comparator::LevensteinDistance(const std::string& str1,
                                      const std::string& str2) {
  size_t len1 = str1.length();
  size_t len2 = str2.length();

  std::vector<std::vector<size_t>> ans_at_pos(len1 + 1,
                                              std::vector<size_t>(len2 + 1, 0));

  for (size_t i = 0; i <= len1; ++i) {
    for (size_t j = 0; j <= len2; ++j) {
      if (i == 0) {
        ans_at_pos[i][j] = j;
      } else if (j == 0) {
        ans_at_pos[i][j] = i;
      } else {
        size_t substitution_cost = (str1[i - 1] != str2[j - 1]) ? 1 : 0;
        ans_at_pos[i][j] = std::min(
            std::min(ans_at_pos[i - 1][j] + 1, ans_at_pos[i][j - 1] + 1),
            ans_at_pos[i - 1][j - 1] + substitution_cost);
      }
    }
  }

  return ans_at_pos[len1][len2];
}

void Comparator::PrintInConsole() {
  PrintEqualFiles();
  std::cout << std::endl;

  PrintSimilar();
  std::cout << std::endl;

  PrintOnlyInDir1();
  std::cout << std::endl;

  PrintOnlyInDir2();
  std::cout << std::endl;
}

void Comparator::PrintEqualFiles() {
  std::cout << "Equal files:" << std::endl;
  for (const auto& [file1, file2] : equal_files_) {
    std::cout << file1 << " - " << file2 << std::endl;
  }
}

void Comparator::PrintSimilar() {
  std::cout << "Similar files:" << std::endl;
  for (const auto& [file1, file2, similarity] : similar_files_) {
    std::cout << file1 << " - " << file2 << " - " << similarity << "%"
              << std::endl;
  }
}

void Comparator::PrintOnlyInDir1() {
  std::cout << "Files only in dir1:" << std::endl;
  for (const auto& file : fs::directory_iterator(dir1_)) {
    bool only_in_dir1 = true;
    for (const auto& [file1, file2] : equal_files_) {
      if (file1 == file) {
        only_in_dir1 = false;
      }
    }
    for (const auto& [file1, file2, similarity] : similar_files_) {
      if (file1 == file) {
        only_in_dir1 = false;
      }
    }
    if (only_in_dir1) {
      std::cout << file.path() << std::endl;
    }
  }
}

void Comparator::PrintOnlyInDir2() {
  std::cout << "Files only in dir2:" << std::endl;
  for (const auto& file : fs::directory_iterator(dir2_)) {
    bool only_in_dir2 = true;
    for (const auto& [file1, file2] : equal_files_) {
      if (file2 == file) {
        only_in_dir2 = false;
      }
    }
    for (const auto& [file1, file2, similarity] : similar_files_) {
      if (file2 == file) {
        only_in_dir2 = false;
      }
    }
    if (only_in_dir2) {
      std::cout << file.path() << std::endl;
    }
  }
}

std::vector<std::pair<fs::directory_entry, fs::directory_entry>>
Comparator::GetEqualFiles() const {
  return equal_files_;
}

std::vector<std::tuple<fs::directory_entry, fs::directory_entry, double>>
Comparator::GetSimilarFiles() const {
  return similar_files_;
}
