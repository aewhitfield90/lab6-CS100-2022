#ifndef __SPREADSHEET_TEST_HPP__
#define __SPREADSHEET_TEST_HPP__

#include "gtest/gtest.h"

#include "select.hpp"
#include "spreadsheet.cpp"
#include <string>
#include <sstream>

TEST(AddtoSheet, Normal) {
    Spreadsheet sheet;
    std::stringstream test;
    sheet.set_column_names({ "First","Last","Age","Major" });
    sheet.add_row({ "Amanda","Andrews","22","business" });
    sheet.print_selection(test);
    EXPECT_EQ(test.str(), "Amanda Andrews 22 business \n");
    }
    
TEST(Matching, Empty) {
    Spreadsheet sheet;
    std::stringstream test;
    sheet.set_column_names({ "First","Last","Age","Major" });
    sheet.add_row({ "","","","" });
    sheet.print_selection(test);
    EXPECT_EQ(test.str(), "    \n");
}

TEST(Contains, ContainsCat) {
    Spreadsheet sheet;
    std::stringstream test;
    sheet.set_column_names({ "First","Last","Age","Major" });
    sheet.add_row({ "Yo","decat","hello","huh" });
    sheet.set_selection(new Select_Contains(&sheet, "Last", "cat"));
    sheet.print_selection(test);
    EXPECT_EQ(test.str(), "Yo decat hello huh \n");
}

TEST(Contains, ContainsCat2) {
    Spreadsheet sheet;
    std::stringstream test;
    sheet.set_column_names({ "First","Last","Age","Major" });
    sheet.add_row({ "Yo","deCat","hello","huh" });
    sheet.add_row({ "test","test","test","test" });
    sheet.set_selection(new Select_Contains(&sheet, "Last", "cat"));
    sheet.print_selection(test);
    EXPECT_EQ(test.str(), "");
}

TEST(Contains, Containsapple) {
    Spreadsheet sheet;
    std::stringstream test;
    sheet.set_column_names({ "First","Last","Age","Major" });
    sheet.add_row({ "test","test","Apple","test" });
    sheet.add_row({ "test","test","apple","test" });
    sheet.add_row({ "test","test","Snapple","test" });
    sheet.set_selection(new Select_Contains(&sheet, "Age", "apple"));
    sheet.print_selection(test);
    EXPECT_EQ(test.str(), "test test apple test \ntest test Snapple test \n");
}   

TEST(UserQuery, ColumnDoesNotExist) {
    Spreadsheet sheet;
    sheet.set_column_names({ "First","Last","Age","Major" });
    int test = sheet.get_column_by_name("height");
    EXPECT_EQ(test, -1);
}

TEST(Columns, DoubleColumns) {
    Spreadsheet sheet;
    std::stringstream test;
    sheet.set_column_names({ "First","First","Age","Major" });
    sheet.add_row({ "1st","2nd","test","test" });
    sheet.add_row({ "3rd","4th","test","test" });
    sheet.set_selection(new Select_Contains(&sheet, "First", "1st"));
    sheet.print_selection(test);
    EXPECT_EQ(test.str(), "1st 2nd test test \n");
}

TEST(Columns, DoubleColumns2) {
    Spreadsheet sheet;
    std::stringstream test;
    sheet.set_column_names({ "First","First","Age","Major" });
    sheet.add_row({ "1st","2nd","test","test" });
    sheet.add_row({ "3rd","4th","test","test" });
    sheet.set_selection(new Select_Contains(&sheet, "First", "2nd"));
    sheet.print_selection(test);
    EXPECT_EQ(test.str(), "1st 2nd test test \n");
}

 
    #endif //__SPREADSHEET_TEST_HPP__
