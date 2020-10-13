//
// Created by Alan Lewis on 10/10/20.
//

#ifndef UNTITLED1_SPACESAVING_H
#define UNTITLED1_SPACESAVING_H

#include <cstdint>
#include <unordered_map>



class SpaceSaving {
    uint32_t t;
    std::unordered_map<uint64_t, uint64_t> trackedItems;
public:
    explicit SpaceSaving(uint32_t t);
    void update(uint64_t x);
    std::vector<uint64_t> output();

};


#endif //UNTITLED1_SPACESAVING_H
