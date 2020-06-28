#include <gtest/gtest.h>
#include "../src/intset.h"



// TEST(intset, init){
//     int i = 1;
//     char c = *((char*)&i);//取i的地址的低8位的所存储的值赋给c

 
//     EXPECT_TRUE(c == 1);   
// }


TEST(intset, all){
    IntSet is;
    int a[5] = {-1,2,3,7,5};
    int target = 3;
    EXPECT_TRUE(is.Size() == 0);
    EXPECT_TRUE(is.BlobSize() == sizeof(IntSet));
    for(int i = 0; i < 5; ++i)
        is.Insert(a[i]);
    EXPECT_TRUE(is.Size() == 5);
    EXPECT_TRUE(is.BlobSize() == sizeof(IntSet) + 5 * sizeof(uint16_t));
    // EXPECT_FALSE(is.Insert(5));
    // EXPECT_TRUE(is.Size() == 5);
    EXPECT_TRUE(is.Find(target) > 0);
    int64_t value;
    int pos = 2;
    is.Get(pos, &value);
    EXPECT_TRUE(value == target);
    is.Remove(3);
    EXPECT_FALSE(is.Find(3) == -1);
    
    EXPECT_TRUE(is.BlobSize() == sizeof(IntSet) + 4 * sizeof(uint16_t));
    is.Insert((int64_t)65536);
    EXPECT_TRUE(is.BlobSize() == sizeof(IntSet) + 4 * sizeof(uint16_t) + sizeof(uint32_t));
    std::cout << is << std::endl;
}



int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}