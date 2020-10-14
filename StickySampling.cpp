//
// Created by Alan Lewis on 6/10/20.
//

#include <random>
#include "StickySampling.h"

using namespace std;

StickySampling::StickySampling(double s, double eps, double delta) : s(s), eps(eps), delta(delta), rng(rd()),
                                                                     dist(uniform_real_distribution<>(0, 1)) {
    rng.seed(time(nullptr));
}

void StickySampling::update(uint64_t x) {

    // if it exists already in the frequency map then we increment the frequency
    if (freqMap.find(x) != freqMap.end()) {
        freqMap[x]++;
    }
    // Otherwise we add the element to the map with a probability of 1/r
    else {
        double num = dist(rng);
        if (num < 1.0 / r) {
            freqMap[x] = 1;
        }
    }
    N++;
    itemsSinceMaintenance++;
    double threshold = r == 1 ? 2 * t : r * t;
    if (itemsSinceMaintenance >= threshold) {
        r *= 2;
        itemsSinceMaintenance = 0;
        maintenance();
    }

}

void StickySampling::maintenance() {
    for (auto it = freqMap.begin(); it != freqMap.end(); /*update the iterator explicitly (not increment)*/) {
        bool erased = false;
        while (dist(rng) < 0.5) {
            it->second--;
            if (it->second == 0) {
                freqMap.erase(it);
                erased = true;
                break;
            }
        }
        if (!erased) {
            ++it;
        }
    }
}

std::vector<uint64_t> StickySampling::output() {
    vector<uint64_t> out;
    for (auto const &pair: freqMap) {
        if (pair.second >= (s - eps) * N) {
            out.push_back(pair.first);
        }
    }
    return out;
}
