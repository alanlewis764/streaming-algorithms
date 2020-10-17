//
// Created by Alan Lewis on 13/10/20.
//

#include <iostream>
#include <vector>
#include "SpaceSavingLinkedList.h"

using namespace std;

SpaceSavingLinkedList::SpaceSavingLinkedList(uint64_t t) : t(t) {
    smallestParentBucket = new ParentBucket(0);
}

void SpaceSavingLinkedList::update(uint64_t x) {
    // if x is already being tracked, then move it to a relevant parent bucket
    if (hashmap.find(x) != hashmap.end()) {
        ListItem *item = hashmap[x];
        increment(item);
    }
    // Otherwise add x to the tracked items
    else {
        // if an the number of tracked items is less than t, then add it to the bucket with a value 1
        if (numItems < t) {
            auto *item = new ListItem(x);
            hashmap[x] = item;
            // if the smallest parent bucket has a value of 1 then we can just add it to that bucket
            add(item);
            numItems++;
        }

        // Otherwise evict the items with the minimum count and add x with a count min_count + 1
        else {
            // What we can do here is change the ID of an item in the lowest bucket and increment the item
            ListItem *removedItem = smallestParentBucket->next->child;
            hashmap.erase(removedItem->ID);
            removedItem->ID = x;
            hashmap[x] = removedItem;
            removedItem->epsilon = removedItem->parentBucket->value;
            increment(removedItem);
        }
    }
}

void SpaceSavingLinkedList::add(ListItem *item) {
    if (smallestParentBucket->next != nullptr && smallestParentBucket->next->value == 1) {
        addToParent(smallestParentBucket->next, item);
    }
    // Otherwise we need to make a new Parent Bucket with the value 1 and add it to that bucket
    else {
        auto *newBucket = new ParentBucket(1);
        if (smallestParentBucket->next != nullptr) {
            smallestParentBucket->next->prev = newBucket;
            newBucket->next = smallestParentBucket->next;
        }
        smallestParentBucket->next = newBucket;
        newBucket->prev = smallestParentBucket;
        addToParent(newBucket, item);
    }
}

void SpaceSavingLinkedList::increment(ListItem *item) {
    ParentBucket *itemParent = item->parentBucket;
    // If a parent bucket already exists then just move it over and delete parent if it contains no more items
    if (itemParent->next!= nullptr && itemParent->value+1 == itemParent->next->value) {

        // if the next item is itself, then the item is the only item in the linked list, so parent bucket can be removed.
        if (item->next == item) {
            ParentBucket *prevParent = itemParent->prev;
            ParentBucket *nextParent = itemParent->next;
            prevParent->next = nextParent;
            nextParent->prev = prevParent;
            addToParent(nextParent, item);
            delete itemParent;
            return;
        }

        //otherwise we need to splice the child out of the linked list
        ListItem *tempListItem = item->next;
        splice(item);
        //add the tempListItem to the next parent item
        addToParent(item->parentBucket->next, tempListItem);
    }

    // if the item is the only item but the next parent is more than 1 unit away, then we can simply change the value of the bucket
    // and save us some hassle
    else if (item->next == item) {
        item->parentBucket->value++;
    }

    // otherwise we need to splice out the item, create a new parent and add it as the only item in that parent
    else {
        ListItem *temp = item->next;
        splice(item);
        item = temp;
        auto *newParent = new ParentBucket(itemParent->value+1);
        newParent->next = itemParent->next;
        newParent->prev = itemParent;
        addToParent(newParent, item);
        itemParent->next = newParent;
        if (newParent->next != nullptr) {
            newParent->next->prev = newParent;
        }
        item->parentBucket = newParent;
        item->next = item;
    }
}

void SpaceSavingLinkedList::splice(ListItem *item) {
    // we are going to swap the item and the next item so make sure that the parent isn't pointing to the next item
    if (item->parentBucket->child == item->next) {
        item->parentBucket->child = item;
    }
    // swap IDs with next and splice next out of the linked list
    uint64_t temp = item->ID;
    item->ID = item->next->ID;
    item->next->ID = temp;

    //update the hash map for ensure that the ID correspond to the changed pointers
    hashmap[item->ID] = item;
    hashmap[item->next->ID] = item->next;

    //Store item->next (which is now the original item to be removed) so that it can be added to parent->next
    item->next = item->next->next;
}

void SpaceSavingLinkedList::addToParent(ParentBucket *parent, ListItem *item) {
    // ensure that the item parent is the parent
    item->parentBucket = parent;
    // if there are no children then just add it as the only child
    if (parent->child == nullptr) {
        parent->child = item;
        item->next = item;
    }
    // Add it to the children linked list, the position doesn't matter...
    else {
        ListItem *temp = parent->child->next;
        parent->child->next = item;
        item->next = temp;
    }
}

unordered_map<uint64_t, uint64_t> SpaceSavingLinkedList::output(double threshold) {
    unordered_map<uint64_t, uint64_t> returnMap;
    for (auto const &pair: hashmap) {
        ListItem *item = pair.second;
        if (item->parentBucket->value >= threshold) {
            returnMap[item->ID] = item->parentBucket->value;
        }
    }
    return returnMap;
}


