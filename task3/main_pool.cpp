#include "File_entry.h"
#include "File_entry.cpp"
#include "Directory.h"
#include "Directory.cpp"
#include "ThreadPool.h"
#include "ThreadPool.cpp"

int main() {
    // std::string path = "/home/pary/~projects/softserve/task 3 threads";
    std::string path = "/home/pary/~projects/include";
    Directory dir(path);
    auto files = dir.get_files();

    auto start_s = std::chrono::high_resolution_clock::now();
    auto prjsts_s = dir.process_files_st(files);
    auto finish_s = std::chrono::high_resolution_clock::now();
    auto duration_s = std::chrono::duration_cast<std::chrono::microseconds>(finish_s - start_s).count();
    std::cout<<"for single-threaded duration = "<<duration_s<<"\n\n";
    dir.write_result_to_file("prjstats_st.txt", prjsts_s);


    ThreadPool pool;
    auto start_p = std::chrono::high_resolution_clock::now();
    auto prjsts_p = dir.process_files_pl(files, pool);
    auto finish_p = std::chrono::high_resolution_clock::now();
    auto duration_p = std::chrono::duration_cast<std::chrono::microseconds>(finish_p - start_p).count();
    std::cout<<"for multi-threaded duration = "<<duration_p<<"\n\n";
    dir.write_result_to_file("prjstats_pl.txt", prjsts_p);


    return 0;
}