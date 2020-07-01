#include <gtest/gtest.h>
#include "../src/intset.h"


TEST(intset, all){
    IntSet is;
    int a[5] = {3,22,-3,7,5};
    int target = 3;
    EXPECT_TRUE(is.Size() == 0);
    EXPECT_TRUE(is.BlobSize() == sizeof(IntSet));
    for(int i = 0; i < 5; ++i)
        is.Insert(a[i]);
    EXPECT_TRUE(is.Size() == 5);
    EXPECT_TRUE(is.BlobSize() == sizeof(IntSet) + 5 * sizeof(uint16_t));
    EXPECT_TRUE(is.Find(3) == 1);
    int64_t value;
    int pos = 1;
    is.Get(pos, &value);
    EXPECT_TRUE(value == target);
    is.Remove(3);
    EXPECT_TRUE(is.Find(3) == -1);
    
    EXPECT_TRUE(is.BlobSize() == sizeof(IntSet) + 4 * sizeof(uint16_t));
    is.Insert((int64_t)65536);
    EXPECT_TRUE(is.BlobSize() == sizeof(IntSet) + 4 * sizeof(uint16_t) + sizeof(uint32_t));

    std::cout << is ;
}



int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}