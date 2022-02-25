#include "spreadsheet.hpp"

#include "gtest/gtest.h"
#include "spreadsheet_test.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
