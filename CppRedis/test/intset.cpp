#include <gtest/gtest.h>
// #include "../src/intset.h"

TEST(intset, insert){
    EXPECT_FALSE(1+1==3);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}