#include <gtest/gtest.h>
#include <src/Comparator.hpp>

namespace fs = std::filesystem;

TEST(Comparator, CompareFiles1) {
  fs::path temp_dir1 = fs::current_path() / "temp_dir1";
  fs::path temp_dir2 = fs::current_path() / "temp_dir2";
  fs::create_directory(temp_dir1);
  fs::create_directory(temp_dir2);
  fs::path temp_file1 = temp_dir1 / "file1.txt";
  fs::path temp_file2 = temp_dir2 / "file2.txt";
  std::ofstream file1(temp_file1);
  std::ofstream file2(temp_file2);
  file1 << "Test Content";
  file2 << "Test Content";
  file1.close();
  file2.close();

  double similarity = Comparator::CompareFiles(temp_file1, temp_file2);

  fs::remove(temp_file1);
  fs::remove(temp_file2);
  fs::remove(temp_dir1);
  fs::remove(temp_dir2);

  EXPECT_GT(similarity, 0.0);
}

TEST(Comparator, CompareFiles2) {
  fs::path temp_dir1 = fs::current_path() / "temp_dir1";
  fs::path temp_dir2 = fs::current_path() / "temp_dir2";
  fs::create_directory(temp_dir1);
  fs::create_directory(temp_dir2);
  fs::path temp_file1 = temp_dir1 / "file1.txt";
  fs::path temp_file2 = temp_dir2 / "file2.txt";
  std::ofstream file1(temp_file1);
  std::ofstream file2(temp_file2);
  file1 << "ABA";
  file2 << "B";
  file1.close();
  file2.close();

  double similarity = Comparator::CompareFiles(temp_file1, temp_file2);

  fs::remove(temp_file1);
  fs::remove(temp_file2);
  fs::remove(temp_dir1);
  fs::remove(temp_dir2);

  EXPECT_GT(similarity, 30);
}

TEST(Comparator, GetEqualFiles) {
  fs::path temp_dir1 = fs::current_path() / "temp_dir1";
  fs::path temp_dir2 = fs::current_path() / "temp_dir2";
  fs::create_directory(temp_dir1);
  fs::create_directory(temp_dir2);
  fs::path temp_file1 = temp_dir1 / "file1.txt";
  fs::path temp_file2 = temp_dir2 / "file2.txt";

  std::ofstream file1(temp_file1);
  std::ofstream file2(temp_file2);
  file1 << "Test Content";
  file2 << "Test Content";
  file1.close();
  file2.close();

  Comparator comparator(temp_dir1, temp_dir2, 0.0);
  comparator.CompareDirectories();

  auto equal_files = comparator.GetEqualFiles();

  EXPECT_FALSE(equal_files.empty());

  fs::remove(temp_file1);
  fs::remove(temp_file2);
  fs::remove(temp_dir1);
  fs::remove(temp_dir2);
}

TEST(Comparator, GetSimilarFiles) {
  fs::path temp_dir1 = fs::current_path() / "temp_dir1";
  fs::path temp_dir2 = fs::current_path() / "temp_dir2";
  fs::create_directory(temp_dir1);
  fs::create_directory(temp_dir2);
  fs::path temp_file1 = temp_dir1 / "file1.txt";
  fs::path temp_file2 = temp_dir2 / "file2.txt";

  std::ofstream file1(temp_file1);
  std::ofstream file2(temp_file2);
  file1 << "Test not content";
  file2 << "Test Content";
  file1.close();
  file2.close();

  Comparator comparator(temp_dir1, temp_dir2, 3.0);
  comparator.CompareDirectories();

  auto similar_files = comparator.GetSimilarFiles();

  EXPECT_FALSE(similar_files.empty());

  fs::remove(temp_file1);
  fs::remove(temp_file2);
  fs::remove(temp_dir1);
  fs::remove(temp_dir2);
}

TEST(Comparator, EmptyDirectories) {
  fs::path temp_dir1 = fs::current_path() / "empty_dir1";
  fs::path temp_dir2 = fs::current_path() / "empty_dir2";
  fs::create_directory(temp_dir1);
  fs::create_directory(temp_dir2);

  Comparator comparator(temp_dir1, temp_dir2, 0.0);
  comparator.CompareDirectories();

  auto equal_files = comparator.GetEqualFiles();
  auto similar_files = comparator.GetSimilarFiles();

  EXPECT_TRUE(equal_files.empty());
  EXPECT_TRUE(similar_files.empty());

  fs::remove(temp_dir1);
  fs::remove(temp_dir2);
}

TEST(Comparator, DifferentFiles) {
  fs::path temp_dir1 = fs::current_path() / "dir1";
  fs::path temp_dir2 = fs::current_path() / "dir2";
  fs::create_directory(temp_dir1);
  fs::create_directory(temp_dir2);
  fs::path temp_file1 = temp_dir1 / "file1.txt";
  fs::path temp_file2 = temp_dir2 / "file2.txt";

  std::ofstream file1(temp_file1);
  std::ofstream file2(temp_file2);
  file1 << "Content1";
  file2 << "Blahblah";
  file1.close();
  file2.close();

  Comparator comparator(temp_dir1, temp_dir2, 50);
  comparator.CompareDirectories();

  auto equal_files = comparator.GetEqualFiles();
  auto similar_files = comparator.GetSimilarFiles();

  EXPECT_TRUE(equal_files.empty());
  EXPECT_TRUE(similar_files.empty());

  fs::remove(temp_file1);
  fs::remove(temp_file2);
  fs::remove(temp_dir1);
  fs::remove(temp_dir2);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
