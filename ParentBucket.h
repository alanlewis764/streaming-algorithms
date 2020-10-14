//
// Created by Alan Lewis on 13/10/20.
//

#ifndef UNTITLED1_PARENTBUCKET_H
#define UNTITLED1_PARENTBUCKET_H

#include <cstdint>
//#include "ListItem.h"

class ListItem;

class ParentBucket {
public:
    ListItem *child;
    ParentBucket *next;
    ParentBucket *prev;
    uint64_t value;

    explicit ParentBucket(uint64_t value);


};


#endif //UNTITLED1_PARENTBUCKET_H
