//
// Created by Alan Lewis on 13/10/20.
//

#ifndef UNTITLED1_SPACESAVINGLINKEDLIST_H
#define UNTITLED1_SPACESAVINGLINKEDLIST_H

#include <cstdint>
#include <unordered_map>
#include "ListItem.h"
#include "ParentBucket.h"

class SpaceSavingLinkedList {
    uint64_t t;
    uint64_t numItems = 0;
    ParentBucket *smallestParentBucket;
    std::unordered_map<uint64_t, ListItem*> hashmap;
public:
    explicit SpaceSavingLinkedList(uint64_t t);
    void update(uint64_t x);
    std::unordered_map<uint64_t, uint64_t> output(double support);

private:
    void increment(ListItem* item);
    void splice(ListItem* item);
    void addToParent(ParentBucket *parent, ListItem *item);
    void add(ListItem *item);
};


#endif //UNTITLED1_SPACESAVINGLINKEDLIST_H
