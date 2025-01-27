#include <iostream>
#include <gtest/gtest.h>

#include "AnyType.h"
#include "AnyType.cpp"

TEST(AnyTypeTest, TestAssignment) {
    int pi = 5; double pd = 2.13;
    char pc = '?'; bool pb = true;
    AnyType a = pi; AnyType b = pd; AnyType c = pc; AnyType d = pb;

    EXPECT_EQ(pi, a.getInt());
    EXPECT_EQ(pd, b.getDouble());
    EXPECT_EQ(pc, c.getChar());
    EXPECT_EQ(pb, d.getBool());
}


TEST(AnyTypeTest, TestConstructorsAndTypes) {
    int pi = 5; double pd = 2.13;
    char pc = '?'; bool pb = true;
    AnyType a(pi); AnyType b(pd); AnyType c(pc); AnyType d(pb);

    EXPECT_EQ(AnyType::Type::INT, a.getType());
    EXPECT_EQ(AnyType::Type::DOUBLE, b.getType());
    EXPECT_EQ(AnyType::Type::CHAR, c.getType());
    EXPECT_EQ(AnyType::Type::BOOL, d.getType());
}

TEST(AnyTypeTest, TestTypeSafeAccess) {
    int pi = 5; 
    AnyType a(pi);
    EXPECT_NO_THROW(a.getInt());
    EXPECT_EQ(pi, a.getInt());
    EXPECT_THROW(a.getDouble(), AnyType::InvalidType);
    EXPECT_THROW(a.getChar(), AnyType::InvalidType);
    EXPECT_THROW(a.getBool(), AnyType::InvalidType);
}

TEST(AnyTypeTest, TestSwap) {
    int pi1 = 5, pi2 = 7; char pc = '?';
    AnyType a(pi1), b(pi2), c(pc);

    a.swap(b);
    EXPECT_EQ(AnyType::Type::INT, a.getType());
    EXPECT_EQ(AnyType::Type::INT, b.getType());
    EXPECT_EQ(pi2, a.getInt());
    EXPECT_EQ(pi1, b.getInt());

    a.swap(c);
    EXPECT_EQ(AnyType::Type::CHAR, a.getType());
    EXPECT_EQ(AnyType::Type::INT, c.getType());
    EXPECT_EQ(pi2, c.getInt());
    EXPECT_THROW(c.getChar(), AnyType::InvalidType);
    EXPECT_EQ(pc, a.getChar());
    EXPECT_THROW(a.getInt(), AnyType::InvalidType);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    
    return 0;
}