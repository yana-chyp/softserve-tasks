#include <iostream>
#include <gtest/gtest.h>

#include "List.h"
#include "List.cpp"

class StringListTestFixture: public testing::Test {
    protected:
        t_element*** plist;
    public:
        void SetUp() override;
};

void StringListTestFixture::SetUp() {
    plist = (t_element***)malloc(sizeof(char**));

    stringListInit(plist);
}

TEST_F(StringListTestFixture, TestSizeOfEmpty) {
    ASSERT_EQ(0, stringListSize(*plist));
}

TEST_F(StringListTestFixture, TestSizeAfterAdd) {
    stringListAdd(plist, "test");
    ASSERT_EQ(1, stringListSize(*plist));
    stringListAdd(plist, "test");
    ASSERT_EQ(2, stringListSize(*plist));
}

TEST_F(StringListTestFixture, TestIndexOf) {
    std::string t1 = "test1", t2 = "test2", t3 = "test3";
    stringListAdd(plist, t1);
    stringListAdd(plist, t2);
    stringListAdd(plist, t3);
    stringListAdd(plist, t1);

    ASSERT_EQ(0, stringListIndexOf(*plist, t1));
    ASSERT_EQ(1, stringListIndexOf(*plist, t2));
    ASSERT_EQ(2, stringListIndexOf(*plist, t3));
}

TEST_F(StringListTestFixture, TestAdd) {
    std::string t = "test";
    stringListAdd(plist, t);
    ASSERT_EQ(0, strcmp(***plist, t.c_str()));
}

TEST_F(StringListTestFixture, TestRemove) {
    std::string t1 = "test1", t2 = "test2", t3 = "test3", t4 = "test4", t5 = "test5";
    stringListAdd(plist, t1);
    stringListAdd(plist, t2);
    stringListAdd(plist, t3);
    stringListAdd(plist, t1);
    stringListAdd(plist, t5);
    stringListAdd(plist, t3);
    stringListAdd(plist, t4);
    stringListAdd(plist, t1);

    stringListRemove(plist, t1);

    bool containst1 = false;
    for (auto pelem = *plist; *pelem!=nullptr; ++pelem) {
        if (strcmp(**pelem, t1.c_str())==0) containst1 = true; break;
    }
    ASSERT_FALSE(containst1);

}

TEST_F(StringListTestFixture, TestRemoveDuplicates) {
    std::string t1 = "test1", t2 = "test2", t3 = "test3", t4 = "test4", t5 = "test5";
    stringListAdd(plist, t1);
    stringListAdd(plist, t2);
    stringListAdd(plist, t3);
    stringListAdd(plist, t1);
    stringListAdd(plist, t5);
    stringListAdd(plist, t3);
    stringListAdd(plist, t4);
    stringListAdd(plist, t1);

    stringListRemoveDuplicates(plist);
    for (auto pelem = *plist; *pelem!=nullptr; ++pelem) {
        int count = 1;
        for (auto pelem2 = pelem+1; *pelem2!=nullptr; ++pelem2) {
            if (strcmp(**pelem, **pelem2)==0) {++count; break;} 
        }
        ASSERT_EQ(1, count);
    }
}

TEST_F(StringListTestFixture, TestReplaceInStrings) {
    std::string t = "test", t1 = "test1", t2 = "test2", t3 = "test3", t4 = "test4", t5 = "test5";
    stringListAdd(plist, t1);
    stringListAdd(plist, t2);
    stringListAdd(plist, t3);
    stringListAdd(plist, t1);
    stringListAdd(plist, t5);
    stringListAdd(plist, t3);
    stringListAdd(plist, t4);
    stringListAdd(plist, t1);
    int indexesOft1[] = {0, 3, 7}; int n = 3;

    stringListReplaceInStrings(*plist, "test1", "test");
    for (int i: indexesOft1) {
        std::cout<<*plist<<"\t"<<(*plist)[i]<<"\t"<<*((*plist)[i])<<"\n";
        ASSERT_EQ(0, strcmp(*((*plist)[i]), t.c_str()));
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    
    return 0;
}