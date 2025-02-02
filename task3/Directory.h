#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <filesystem>
#include <string>
#include <vector>
#include <map>
#include "ThreadPool.h" 

namespace fs = std::filesystem;

class Directory {
    private:
    //local path
        std::string name;
        const std::vector<std::string> extensions = {".h", ".hpp", ".c", ".cpp"};
        // bool check_extension(fs::directory_entry& entry) const;
    public:
        Directory(std::string name);
        ~Directory();
        std::string get_name() const;
        //getting files is recursive going through inner directories
        std::vector<std::string> get_files() const;
        std::map<std::string, std::vector<int>> process_files_st(std::vector<std::string> files) const;
        std::map<std::string, std::vector<int>> process_files_mt(std::vector<std::string> files) const;
        std::map<std::string, std::vector<int>> process_files_pl(std::vector<std::string> files, ThreadPool & pool) const;


        void write_result_to_file(std::string filename, std::map<std::string, std::vector<int>>& prjsts) const;
};


#endif