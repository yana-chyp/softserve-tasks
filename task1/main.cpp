#include "List.h"
#include "List.cpp"
#include <iostream>
using namespace std;

typedef char* t_element;
int main() {
    t_element** const plist = (t_element**)malloc(sizeof(t_element*));
    std::cout<<"plist: "<<plist<<"\n";

    stringListInit(plist);
    std::cout<<"plist: "<<plist<<"\n";
    std::cout<<"*plist: "<<*plist<<"\n";

    for (auto elem = *plist; *elem!=nullptr; ++elem) {
        std::cout<<*elem<<"\n";
    }
    std::cout<<"out of the loop\n";
    std::cout<<"size = "<<stringListSize(*plist)<<"\n";

    stringListAdd(plist, "hello");
    stringListAdd(plist, "world");
    stringListAdd(plist, "back");
    stringListAdd(plist, "I'm");
    stringListAdd(plist, "flight");
    stringListAdd(plist, "going");
    stringListAdd(plist, "back");
    stringListAdd(plist, "to");
    stringListAdd(plist, "505");
    stringListAdd(plist, "if it's a ");
    stringListAdd(plist, "seven-hour");
    stringListAdd(plist, "side");
    stringListAdd(plist, "flight");
    stringListAdd(plist, "flight");
    stringListAdd(plist, "or");
    stringListAdd(plist, "a");
    stringListAdd(plist, "forty-five-minute");
    stringListAdd(plist, "drive");
    stringListAdd(plist, "505");
    stringListAdd(plist, "world");
    stringListAdd(plist, "smile");
    stringListAdd(plist, "505");

for (auto elem = *plist; *elem!=nullptr; ++elem) {
        std::cout<<*elem<<"\n";
    }
std::cout<<"out of the loop\n";
    std::cout<<"size = "<<stringListSize(*plist)<<"\n";



    // std::cout<<"\nplist: "<<plist<<"\n";
    // std::cout<<"*plist: "<<*plist<<"\n";
    // std::cout<<"size = "<<stringListSize(*plist)<<"\n";

    stringListRemove(plist, "I'm");
    // std::cout<<"\nplist: "<<plist<<"\n";
    // std::cout<<"*plist: "<<*plist<<"\n";
    std::cout<<"size = "<<stringListSize(*plist)<<"\n";
    stringListRemove(plist, "to");
    // std::cout<<"\nplist: "<<plist<<"\n";
    // std::cout<<"*plist: "<<*plist<<"\n";
    std::cout<<"size = "<<stringListSize(*plist)<<"\n";
    stringListRemove(plist, "drive");
    // std::cout<<"\nplist: "<<plist<<"\n";
    // std::cout<<"*plist: "<<*plist<<"\n";
    std::cout<<"size = "<<stringListSize(*plist)<<"\n";


    stringListReplaceInStrings(*plist, "audience", "imagination");
    stringListReplaceInStrings(*plist, "back", "lion");

    std::cout<<"before sorting:\n";
    for (auto elem = *plist; *elem!=nullptr; ++elem) std::cout<<*elem<<"\n";


    stringListSort(*plist, true);

    // std::cout<<"size = "<<stringListSize(*plist)<<"\n";
    std::cout<<"after sorting:\n";
    for (auto elem = *plist; *elem!=nullptr; ++elem) std::cout<<*elem<<"\n";
    
    

    std::cout<<"index of '505' = "<<stringListIndexOf(*plist, "505")<<"\n";
    std::cout<<"index of 'minute' = "<<stringListIndexOf(*plist, "minute")<<"\n";
    
    // auto size = stringListSize(*plist);
    // for (auto pelem = *plist; pelem!=*plist+size; ++pelem) {
    //         std::cout<<pelem<<"\t"<<*pelem<<" is pelem\n";
    // }

    stringListRemoveDuplicates(plist);
    for (auto pelem = *plist; *pelem!=nullptr; ++pelem) std::cout<<*pelem<<"\n";


    stringListDestroy(plist);

    return 0;
}