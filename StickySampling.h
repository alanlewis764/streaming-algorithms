//
// Created by Alan Lewis on 6/10/20.
//

#ifndef UNTITLED1_STICKYSAMPLING_H
#define UNTITLED1_STICKYSAMPLING_H


#include <unordered_map>
#include <vector>
#include <random>
#include <ctime>

class StickySampling {
    std::random_device rd;
    std::mt19937 rng;
    std::uniform_real_distribution<double> dist;
    double s;
    double eps;
    double delta;
    double r = 1;
    double t = 1/eps*log((1/s)*(1/delta));
    uint32_t N = 0;
    uint32_t itemsSinceMaintenance = 0;
    // set of pairs where first denotes the item and second denotes the count
    std::unordered_map<std::uint64_t, std::uint64_t> freqMap;


public:
    StickySampling(double s, double eps, double delta);
    void update(uint64_t x);
    std::unordered_map<uint64_t, uint64_t> output();

private:
    void maintenance();
};




#endif //UNTITLED1_STICKYSAMPLING_H
