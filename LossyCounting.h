//
// Created by Alan Lewis on 8/10/20.
//

#ifndef UNTITLED1_LOSSYCOUNTING_H
#define UNTITLED1_LOSSYCOUNTING_H


#include <cstdint>
#include <unordered_map>
#include <vector>

class LossyCounting {
    std::unordered_map<uint64_t, std::pair<uint32_t, uint32_t>> trackedItems;
    double eps;
    double s;
    uint32_t w = ceil(1/eps);
    uint32_t b_current = 1;
    uint32_t N = 0;
    double k;
public:
    LossyCounting(double eps, double s);
    void update(uint64_t x);
    std::unordered_map<uint64_t, uint64_t> output();

private:
    void maintenance();
};


#endif //UNTITLED1_LOSSYCOUNTING_H
