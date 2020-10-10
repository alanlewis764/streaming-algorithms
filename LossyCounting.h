//
// Created by Alan Lewis on 8/10/20.
//

#ifndef UNTITLED1_LOSSYCOUNTING_H
#define UNTITLED1_LOSSYCOUNTING_H


#include <cstdint>
#include <unordered_map>

class LossyCounting {
    uint32_t D = 0;
    uint32_t m = 0;
    std::unordered_map<uint64_t, uint32_t> trackedItems;
    double eps;
    double s;
    double k;
public:
    LossyCounting(double eps, double s);
    void update(uint64_t x);
    std::vector<uint64_t> output();

private:
    void maintenance();
};


#endif //UNTITLED1_LOSSYCOUNTING_H
