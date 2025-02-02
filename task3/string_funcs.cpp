#ifndef STRING_FUNCS_CPP
#define STRING_FUNCS_CPP
#include <string>
#include <sstream>

bool contains_smth(std::string s) {
    for (int i = 0; i<s.length(); ++i) {
        if (s[i]!=' ') return true;
    }
    return false;
} 

bool is_single_line_comment(std::string s) {
    std::istringstream iss(s);
    char symbol1, symbol2; 
    iss>>symbol1>>symbol2;
    return (symbol1=='/' && symbol2=='/');
}

bool starts_multiline_comment(std::string s) {
    if (s.length()<2) return false;
    for (int i = 0; i<s.length()-1; ++i) {
        if (s[i]=='/' && s[i+1]=='*') return true;
    }
    return false;
}

//assume line contains only comment
//so there won't be any code after "*/"
bool contains_end_of_comment(std::string s) {
    if (s.length()<2) return false;
    for (int i = s.length()-1; i>0; --i) {
        if (s[i]=='/' && s[i-1]=='*') return true;
    }
    return false;
}

#endif