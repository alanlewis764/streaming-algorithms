//
// Created by Alan Lewis on 13/10/20.
//

#ifndef UNTITLED1_LISTITEM_H
#define UNTITLED1_LISTITEM_H

#include <cstdint>
//#include "ParentBucket.h"

class ParentBucket;

class ListItem {
public:
    uint64_t ID;
    uint64_t epsilon;
    ListItem *next;
    ParentBucket *parentBucket;
    bool evicted = false;

    explicit ListItem(uint64_t id);
};


#endif //UNTITLED1_LISTITEM_H
