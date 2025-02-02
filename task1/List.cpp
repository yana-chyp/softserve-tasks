#ifndef LIST_CPP
#define LIST_CPP

#include "List.h"
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>


typedef char* t_element;
void stringListInit(t_element** plist) {
    // plist = (t_element***)malloc(sizeof(char**));
    *plist = (t_element*)malloc(sizeof(t_element));
    *plist[0] = nullptr;
}

void stringListDestroy(t_element** plist) {
    //?
    for(auto pelem = *plist; *pelem!=nullptr; ++pelem) {
        free(*pelem);
    }
    free(plist);
}

int stringListSize(t_element* list) {
    int size = 0;
    for (auto pelem = list; *pelem!=nullptr; ++pelem) {++size;}
    return size;
}

void stringListAdd(t_element** plist, std::string str) {
    int oldSize = stringListSize(*plist);   
    // std::cout<<"size = "<<oldSize<<"\n";
    t_element* newList = (t_element*)realloc(*plist, (oldSize+2)*sizeof(t_element));
    t_element pnewElem =  (t_element)malloc(str.length()+1);
    // *pnewElem = (char*)malloc(str.length()+1);
    // pnewElem = str.c_str()
    strcpy(pnewElem, str.c_str());
    newList[oldSize] = pnewElem;
    newList[oldSize+1] = nullptr;
    *plist = newList;
}

void stringListRemove(t_element** plist, std::string str) {
    int oldSize = stringListSize(*plist);
    int numOccur = 0;
    for (t_element* pelem = *plist; *pelem!=nullptr; ++pelem) {
        if (strcmp(str.c_str(), *pelem)==0) ++numOccur;
    }
    if (numOccur==0) return;
    t_element* newList = (t_element*)malloc((oldSize-numOccur+1)*sizeof(t_element));
    int index = 0;
    for (t_element* pelem = *plist; *pelem!=nullptr; ++pelem) {
        if (strcmp(str.c_str(), *pelem)!=0) {
            // std::cout<<index<<"\t"<<**pelem<<"\t"<<*pelem<<"\n";
            newList[index] = *pelem;
            ++index;
        }
        else free(*pelem);
    }
    newList[index] = nullptr;
    free(*plist);
    *plist = newList;
}

int stringListIndexOf(t_element* list, std::string str) {
    int index = 0;
    for (t_element* pelem = list; *pelem!=nullptr; ++pelem) {
        if (strcmp(str.c_str(), *pelem)==0) return index;
        ++index;
    }
    return -1;
}

void stringListRemoveDuplicates(t_element** plist) {
    int oldSize = stringListSize(*plist);
    int num_unique = 0;
    for (auto pelem = *plist; pelem!=*plist+oldSize; ++pelem) {
        if (!*pelem) continue;
        // std::cout<<pelem<<"\t"<<*pelem<<" is unique\n";
        ++num_unique;
        
        for (auto pelem2 = pelem+1; pelem2!=*plist+oldSize; ++pelem2) { 
            if (!*pelem2) continue;
            // std::cout<<pelem2<<"\t"<<*pelem2<<" is pelem2\n";
            if (strcmp(*pelem, *pelem2)==0) {free(*pelem2); *pelem2 = nullptr;}
        }
    }

    t_element* newList = (t_element*)malloc((num_unique+1)*sizeof(t_element));
    int index = 0;
    for (auto pelem = *plist; pelem!=*plist+oldSize; ++pelem) {
        if (*pelem) newList[index++] = *pelem;
    }
    newList[index] = nullptr;
    free(*plist);
    *plist = newList;
}

void stringListReplaceInStrings(t_element* list, t_element before, t_element after) {
    for (auto pelem = list; *pelem!=nullptr; ++pelem) {
        if (strcmp(*pelem, before)==0) {
            free(*pelem);
            t_element pAfter = (t_element)malloc(sizeof(t_element));
            strcpy(pAfter, after);
            list[pelem-list] = pAfter;
        }
    }
}

void quicksort(t_element* list, int first, int last, bool ascending) {
  if (first<last) {
    t_element pivot = (list[last]);
    int i = first-1; int j = last;
    for (;;) {
      if (ascending) {
        while (i<=last && strcmp((list[++i]), pivot)<0) ;
        while (j>=1 && strcmp((list[--j]), pivot)>=0) ;
      }
      else {
        while (i<=last && strcmp((list[++i]), pivot)>0) ;
        while (j>=1 && strcmp((list[--j]), pivot)<=0) ;
      }
      if (i>=j) break;
        std::swap(list[i], list[j]);
    }
    std::swap(list[i], list[last]);

    quicksort(list, first, i-1, ascending);
    quicksort(list, i+1, last, ascending);
  }
}

void stringListSort(t_element* list, bool ascending) {
    quicksort(list, 0, stringListSize(list)-1, ascending);
}

#endif
