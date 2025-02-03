#ifndef DIRECTORY_CPP
#define DIRECTORY_CPP

#include <filesystem>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include "Directory.h"
#include "File_entry.h"
#include "ThreadPool.h"
#include <thread>
#include <iostream>

namespace fs = std::filesystem;

Directory::Directory(std::string name): name(name), blank_lines(0), comment_lines(0), code_lines(0), time(0) {}
std::string Directory::get_name() const {return name;}

std::vector<std::string> Directory::get_files() const {
    std::vector<std::string> files;
    for (const auto& entry: fs::directory_iterator(name)) {
        if (entry.is_regular_file() /*&& check_extension(entry)*/) {
            if (std::find(extensions.begin(), extensions.end(), entry.path().extension())!=extensions.end()) 
                files.push_back(entry.path());
        } 
        else if (entry.is_directory()) {
            Directory dirIn(entry.path());
            auto filesIn = dirIn.get_files();
            files.insert(files.end(), filesIn.begin(), filesIn.end());
        }
    }

    // std::sort(files.begin(), files.end());
    return files;
}

std::map<std::string, std::vector<int>> Directory::process_files_st(std::vector<std::string> files) const {
    std::map<std::string, std::vector<int>> project_stats;
    for (auto file: files) {
        // std::cout<<file<<std::endl;
        FileEntry fentry(file);
        fentry.process();
        auto file_stats = fentry.get_statistics();
        // file_stats.push_back(time);
        project_stats[file] = file_stats;
    }
    return project_stats;
}


std::map<std::string, std::vector<int>> Directory::process_files_pl(std::vector<std::string> files, ThreadPool& pool) const {
    std::map<std::string, std::vector<int>> project_stats;
    int n = files.size();
    std::mutex mtxf;
    for (int i = 0; i<n; ++i) {
        std::string name = files[i];
        pool.add_task([name, &project_stats, &mtxf]() {
                // std::cout<<name<<std::endl;

                FileEntry fentry(name); 
                fentry.process();

                std::unique_lock<std::mutex> lock(mtxf);
                project_stats[name] = fentry.get_statistics();
                // std::cout<<std::this_thread::get_id()<<std::endl;
            }
        );
        // auto file_stats = fentry.get_statistics();
        // project_stats[files[i]] = file_stats;
    }

    // pool.wait_queue_empty();
    pool.wait_and_join_all();

    return project_stats;
}


void Directory::process_dir_pl(std::vector<std::string> files, ThreadPool & pool) {
    this->set_zero();
    this->num_of_files = files.size();
    auto start = std::chrono::high_resolution_clock::now();
    auto prjsts = this->process_files_pl(files, pool);
    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

    for (auto flst: prjsts) {
        this->blank_lines += flst.second[0];
        this->comment_lines += flst.second[1];
        this->code_lines += flst.second[2];
    }
    this->time = duration;

}

void Directory::process_dir_st(std::vector<std::string> files) {
    this->set_zero();
    this->num_of_files = files.size();
    auto start = std::chrono::high_resolution_clock::now();
    auto prjsts = this->process_files_st(files);
    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

    for (auto flst: prjsts) {
        this->blank_lines += flst.second[0];
        this->comment_lines += flst.second[1];
        this->code_lines += flst.second[2];
    }
    this->time = duration;

}

std::vector<int> Directory::get_all_statistics() {
    return {num_of_files, blank_lines, comment_lines, code_lines, time};
}


void Directory::write_result_to_file(std::string filename) const {
    std::fstream file = std::fstream(filename, std::ios::out);
    if (!file.is_open()) {throw "couldn't open file";}
    file<<"number of processed files: "<<num_of_files<<"\n";
    file<<"number of blank lines: "<<blank_lines<<"\n";
    file<<"number of comment lines: "<<comment_lines<<"\n";
    file<<"number of code lines: "<<code_lines<<"\n";
    file<<"time: "<<time<<"\n";
}

Directory::~Directory() {
    name = ""; 
    blank_lines = 0; comment_lines = 0; code_lines = 0; 
    time = 0;
}

void Directory::set_zero() {
    blank_lines = 0;
    comment_lines = 0;
    code_lines = 0;
    time = 0;
}

#endif