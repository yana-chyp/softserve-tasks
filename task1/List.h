
#ifndef LIST_H
#define LIST_H

// #include <stdlib.h>
#include <string>
using std::string;

typedef char* t_element;

//array of pointers to strings (char*)
//end with nullptr (like '\0' for strings)
// dynamically resizable like vector
// pointer to the start of the array would be t_element*
// pointer to the constant place in memory 
//which holds the address of array would be t_element** 

void stringListInit(t_element** plist);
void stringListDestroy(t_element** list);
void stringListAdd(t_element** list, string str);  //will reallocate
void stringListRemove(t_element** list, string str);
int stringListSize(t_element* list); //won't change the address, 
                                    //could pass the address of the start
int stringListIndexOf(t_element* list, string str);
void stringListRemoveDuplicates(t_element** list);
void stringListReplaceInStrings(t_element* list, char* before, char* after);
void stringListSort(t_element* list, bool ascending);  //won't change the size

#endif
