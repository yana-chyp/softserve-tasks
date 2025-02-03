#include <iostream>
#include <gtest/gtest.h>

#include "File_entry.h"
#include "File_entry.cpp"
#include "Directory.h"
#include "Directory.cpp"
#include "ThreadPool.h"
#include "ThreadPool.cpp"


// class DirectoryTestFixture: public testing::Test {
//     protected:
//         Directory dir;
//         const std::vector<std::string> extensions = {".h", ".hpp", ".c", ".cpp"};
//         std::vector<std::string> files;

//     public:
//         void SetUp() override;
// };

//tests rely on the directory to be the same
//test on '/~projects/include/ which contains some libraries 
//and files with wrong extensions,
//total size of the folder is around 132 Mb 

// DirectoryTestFixture::DirectoryTestFixture() {}


// void DirectoryTestFixture::SetUp() {
//     std::string path = "/home/pary/~projects/include";
//     dir = Directory(path);
//     files = dir.get_files();
// }


TEST(DirectoryTest, TestExtensions) {
    const std::vector<std::string> extensions = {".h", ".hpp", ".c", ".cpp"};
    std::string path = "/home/pary/~projects/include";
    Directory dir(path);
    auto files = dir.get_files();
    for (auto file: files) {
        std::filesystem::path pfile = file;
        ASSERT_TRUE(std::find(extensions.begin(), extensions.end(), pfile.extension()) != extensions.end());
    }
}


//this test uses constants 
//which were the output from both single- and multithread methods
TEST(DirectoryTest, TestStatisticsForMultiThrd) {
    int num_of_files = 4252;
    int num_blank = 93225;
    int num_comment = 168332;
    int num_code = 554729;

    std::string path = "/home/pary/~projects/include";
    Directory dir(path);
    auto files = dir.get_files();

    ThreadPool pool;
    dir.process_dir_pl(files, pool);
    auto stat = dir.get_all_statistics();
    ASSERT_EQ(num_of_files, stat[0]);
    ASSERT_EQ(num_blank, stat[1]);
    ASSERT_EQ(num_comment, stat[2]);
    ASSERT_EQ(num_code, stat[3]);
    
}

TEST(DirectoryTest, TestStatisticsForSingleThrd) {
    int num_of_files = 4252;
    int num_blank = 93225;
    int num_comment = 168332;
    int num_code = 554729;

    std::string path = "/home/pary/~projects/include";
    Directory dir(path);
    auto files = dir.get_files();

    dir.process_dir_st(files);
    auto stat = dir.get_all_statistics();
    ASSERT_EQ(num_of_files, stat[0]);
    ASSERT_EQ(num_blank, stat[1]);
    ASSERT_EQ(num_comment, stat[2]);
    ASSERT_EQ(num_code, stat[3]);
    
}


//expect multithread to take less time,
//but it can depend on the size of the files
//if files are small overhead for threads can be too big
//tested on large folder
//multi gives about 1.5 times less time than single
TEST(DirectoryTest, TestCompareTimeForMultiAndSingleThrd) {
    std::string path = "/home/pary/~projects/include";
    Directory dir(path);
    auto files = dir.get_files();

    auto start_s = std::chrono::high_resolution_clock::now();
    dir.process_dir_st(files);
    auto stop_s = std::chrono::high_resolution_clock::now();
    auto duration_s = std::chrono::duration_cast<std::chrono::microseconds>(stop_s - start_s).count();
    std::cout<<"single: "<<duration_s<<std::endl;
    
    ThreadPool pool;
    auto start_m = std::chrono::high_resolution_clock::now();
    dir.process_dir_pl(files, pool);
    auto stop_m = std::chrono::high_resolution_clock::now();
    auto duration_m = std::chrono::duration_cast<std::chrono::microseconds>(stop_m - start_m).count();
    std::cout<<"multi: "<<duration_m<<std::endl;
    EXPECT_TRUE(duration_s > duration_m);
}





int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    
    return 0;
}