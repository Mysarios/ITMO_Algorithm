#include "gtest/gtest.h"
#include "Dice_lib_1.h"
#include <map>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <chrono>

class DiceTest : public ::testing::Test {
protected:
    DiceGenerator generator;
    int test_count = 10000;
    void SetUp() override {
        srand(42);
    }
    
    void TearDown() override {
    }
};

TEST_F(DiceTest, ParseSingleDice) {
    // d6
    generator.new_dices("d6");
    std::string test_str = generator.get_string();
    EXPECT_EQ(test_str,"d6");
    
    // 2d6
    generator.new_dices("2d6");
    test_str = generator.get_string();
    EXPECT_EQ(test_str, "2d6");
    
    // 3d8+2
    generator.new_dices("3d8+2");
    test_str = generator.get_string();
    EXPECT_EQ(test_str, "3d8+2");
    
    // 1d10-1
    generator.new_dices("1d10-1");
    test_str = generator.get_string();
    EXPECT_EQ(test_str, "d10-1");
    
    // 5d20+10
    generator.new_dices("5d20+10");
    test_str = generator.get_string();
    EXPECT_EQ(test_str, "5d20+10");
    
    // dfgljkhldf
    generator.new_dices("indalid");
    test_str = generator.get_string();
    EXPECT_EQ(test_str, "");
}

TEST_F(DiceTest, ParseMultipleDices) {
    generator.new_dices("2d6,1d20");
    EXPECT_EQ(generator.count_dices(), 2);
    
    generator.new_dices("2d6+2,3d10-1,1d20");
    EXPECT_EQ(generator.count_dices(), 3);
    
    generator.new_dices("");
    EXPECT_EQ(generator.count_dices(), 0);
    
    generator.new_dices("d6");
    EXPECT_EQ(generator.count_dices(), 1);
}

TEST_F(DiceTest, GenerateValueBoundsForMultipleDices) {
    generator.new_dices("1d20,2d6+2");
    for (int i = 0; i < test_count; ++i) {
        int val = generator.generate_value();
        EXPECT_GE(val, 2);
        EXPECT_LE(val, 33);
    }
    generator.new_dices("3d6,1d8+1,2d4-1");
    for (int i = 0; i < test_count; ++i) {
        int val = generator.generate_value();
        EXPECT_GE(val, 0);
        EXPECT_LE(val, 28);
    }
}

TEST_F(DiceTest, ConsistencyBetweenGenerations) {
    DiceGenerator gen1, gen2;
    
    gen1.new_dices("2d6+2,1d20");
    gen2.new_dices("2d6+2,1d20");
    
    
    for (int i = 0; i < 100; ++i) {
        srand(123);
        int val1 = gen1.generate_value();
        srand(123);
        int val2 = gen2.generate_value();
        EXPECT_EQ(val1, val2);
    }
}

TEST_F(DiceTest, MixedFormatsTest) {
    generator.new_dices("d6,2d10+3,d20-1,5d4");
    EXPECT_EQ(generator.count_dices(), 4);
    
    for (int i = 0; i < test_count; ++i) {
        int val = generator.generate_value();
        EXPECT_GE(val, 2);
        EXPECT_LE(val, 59);
    }
}

class DiceFormatTest : public ::testing::TestWithParam<std::tuple<std::string, int, int>> {
protected:
    void SetUp() override {
        srand(42);
    }
};

TEST_F(DiceTest, EmptyAndResetTest) {
    generator.new_dices("2d6+2");
    EXPECT_EQ(generator.count_dices(), 1);
    
    generator.new_dices("");
    EXPECT_EQ(generator.count_dices(), 0);
    EXPECT_EQ(generator.generate_value(), 0);
    
    generator.new_dices("1d20");
    EXPECT_EQ(generator.count_dices(), 1);
    
    for (int i = 0; i < test_count; ++i) {
        int val = generator.generate_value();
        EXPECT_GE(val, 0);
        EXPECT_LE(val, 19);
    }
}
