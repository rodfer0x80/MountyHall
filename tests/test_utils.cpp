#include "utils.hpp"
#include <filesystem>
#include <gtest/gtest.h>

namespace fs = std::filesystem;

class EnsureDirectoryExistsTest : public ::testing::Test {
protected:
  std::string testDir;

  void SetUp() override {
    testDir = "./data/test_temp_dir";
    if (fs::exists(testDir)) {
      fs::remove_all(testDir);
    }
  }

  void TearDown() override {
    if (fs::exists(testDir)) {
      fs::remove_all(testDir);
    }
  }
};

TEST_F(EnsureDirectoryExistsTest, CreatesDirectoryIfNotExists) {
  ASSERT_FALSE(fs::exists(testDir));

  ensure_directory_exists(testDir);

  ASSERT_TRUE(fs::exists(testDir));
  ASSERT_TRUE(fs::is_directory(testDir));
}

TEST_F(EnsureDirectoryExistsTest, DoesNothingIfDirectoryAlreadyExists) {
  fs::create_directory(testDir);

  ASSERT_TRUE(fs::exists(testDir));
  ASSERT_TRUE(fs::is_directory(testDir));

  ensure_directory_exists(testDir);

  ASSERT_TRUE(fs::exists(testDir));
  ASSERT_TRUE(fs::is_directory(testDir));
}
