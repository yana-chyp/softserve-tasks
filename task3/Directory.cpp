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

Directory::Directory(std::string name): name(name) {}
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

std::map<std::string, std::vector<int>> Directory::process_files_mt(std::vector<std::string> files) const {
    std::map<std::string, std::vector<int>> project_stats;
    int n = files.size();
    std::thread ts[n];
    for (int i = 0; i<n; ++i) {
        FileEntry fentry(files[i]);
        ts[i] = std::thread(&FileEntry::process, &fentry);
        // auto time = fentry.process();
        auto file_stats = fentry.get_statistics();
        // file_stats.push_back(time);
        project_stats[files[i]] = file_stats;
    }

    for (int i = 0; i<n; ++i) {ts[i].join();}
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

void Directory::write_result_to_file(std::string filename, std::map<std::string, std::vector<int>>& prjsts) const {
    std::fstream file = std::fstream(filename, std::ios::out);
    if (!file.is_open()) {}
    for (auto prj: prjsts) {
        file<<prj.first<<"\t"
        <<"\n\tblank lines: "<<prj.second[0]
        <<"\n\tcomments: "<<prj.second[1]
        <<"\n\tcode lines: "<<prj.second[2]
        <<"\n\ttime: "<<prj.second[3]<<" ms\n";
    }
}





Directory::~Directory() {}

#endif