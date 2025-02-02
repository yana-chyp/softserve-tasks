#ifndef FILE_ENTRY_H
#define FILE_ENTRY_H
#include <string>
#include <vector>
#include <exception>

class FileEntry {
    public:
        enum TypeOfLine {BLANK, COMMENT, CODE, START_MULTILINE_COMMENT};
        struct InvalidType: public std::exception {};
    private:
    //local path
        std::string name;
        int blank_lines;
        int comment_lines;
        int code_lines;
        int time;

        TypeOfLine detect_type(std::string line);
        void set_zero();
    public:
        //assume line can't content both comment and code
        FileEntry(std::string name);

        //needed?
        FileEntry(FileEntry&&) = default;

        ~FileEntry();

        std::string get_name() const;
        std::vector<int> get_statistics();
        void process();

};

#endif