#ifndef RUN_TEST
#define RUN_TEST

#include "gtest/gtest.h"
#include <string>
#include <list>
#include "DatabaseRepository.h"

using namespace std;

string message1 = "Message 1";
string message2 = "Message 2";

TEST(database, add) {
    DatabaseRepository database;
    bool result = database.add(message1);
    ASSERT_TRUE(result);
}

TEST(database, getAll) {
    DatabaseRepository database;
    database.add(message1);
    vector<string> result = database.getAll();
    ASSERT_EQ(result.size(), 1);
    database.add(message2);
    result = database.getAll();
    ASSERT_EQ(result.size(), 2);
}

TEST(database, remove) {
    DatabaseRepository database;
    database.add(message1);
    vector<string> result = database.getAll();
    ASSERT_EQ(result.size(), 1);
    database.remove(message1);
    result = database.getAll();
    ASSERT_EQ(result.size(), 0);
}

TEST(database, clear) {
    DatabaseRepository database;
    database.add(message1);
    database.add(message2);
    vector<string> result = database.getAll();
    ASSERT_EQ(result.size(), 2);
    database.clear();
    result = database.getAll();
    ASSERT_EQ(result.size(), 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#endif