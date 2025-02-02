#ifndef FILE_ENTRY_CPP
#define FILE_ENTRY_CPP
#include "File_entry.h"
#include "string_funcs.cpp"
#include <vector>
#include <fstream>
#include <string>
#include <string_view>
#include <sstream>
#include <iostream>
#include <ctime>
#include <chrono>
using namespace std;

FileEntry::FileEntry(std::string name): name(name), blank_lines(0), comment_lines(0), code_lines(0), time(999) {}
FileEntry::~FileEntry() {};
std::string FileEntry::get_name() const { return name; }
std::vector<int> FileEntry::get_statistics() {return std::vector<int>{blank_lines, comment_lines, code_lines, time};}

void FileEntry::process() {
    set_zero();
    
    std::fstream file = std::fstream(name, std::ios::in);
    if(!file.is_open()) {/*std::cout<<"file is not open\n";*/ throw "couldn't open file";}
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string line;
    auto start = std::chrono::high_resolution_clock::now();
    // std::cout<<"file "<<name<<" getting inside the loop\n";
    while (std::getline(buffer, line)) {
        TypeOfLine type = detect_type(line);
        // std::cout<<line<<"\t"<<type<<"\n";
        switch(type) {
            case TypeOfLine::BLANK:
                blank_lines++; break;
            case TypeOfLine::COMMENT:
                comment_lines++; break;
            case TypeOfLine::START_MULTILINE_COMMENT:
            //prefers comment over code in the same line
                while(!contains_end_of_comment(line)) {
                    comment_lines++;
                    std::getline(buffer, line);
                }
                comment_lines++;
                break;
            case TypeOfLine::CODE:
                code_lines++; break;

            default:
                throw InvalidType();
        }
    }
    // std::cout<<"file "<<name<<" getting out of the loop\n";
    auto finish = std::chrono::high_resolution_clock::now();
    buffer.clear();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
    time = duration;
    // file.close();
    
    
}

FileEntry::TypeOfLine FileEntry::detect_type(std::string line) {
    if (!contains_smth(line)) return TypeOfLine::BLANK;
    if (is_single_line_comment(line)) return TypeOfLine::COMMENT;
    if (starts_multiline_comment(line)) return TypeOfLine::START_MULTILINE_COMMENT;
    return TypeOfLine::CODE;
}

void FileEntry::set_zero() {
    // std::cout<<"called set_zero for "<<name<<"\n";
    blank_lines = 0;
    comment_lines = 0;
    code_lines = 0;
    time = 0;
}



#endif