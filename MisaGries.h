//
// Created by Alan Lewis on 29/9/20.
//

#ifndef UNTITLED1_MISAGRIES_H
#define UNTITLED1_MISAGRIES_H


#include <unordered_map>

class MisaGries {
public:
    MisaGries(uint32_t t, uint32_t m);

    void update(uint32_t x);
    std::vector<uint32_t> output();

private:
    // universe size of 2^32 and max stream size 2^32
    std::unordered_map<uint32_t, uint32_t> countMap;
    uint32_t t;
    // size of the stream
    uint32_t m;
};

#endif //UNTITLED1_MISAGRIES_H
