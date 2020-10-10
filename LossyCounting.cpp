//
// Created by Alan Lewis on 8/10/20.
//

#include <vector>
#include "LossyCounting.h"

using namespace std;

LossyCounting::LossyCounting(double eps, double s) : eps(eps), s(s) {
    k = 1 / eps;
}

void LossyCounting::update(uint64_t x) {
    m++;
    // if x is already tracked, increment the counter add it with count D+1
    if (trackedItems.find(x) != trackedItems.end()) {
        trackedItems[x]++;
    } else {
        trackedItems[x] = D + 1;
    }

    // if D =/= floor m/k then update D and do maintenance
    if (D != floor(m / k)) {
        D = (uint32_t) m / k;
        maintenance();
    }

}

void LossyCounting::maintenance() {
    // delete all items that have a count D
    for (auto it = trackedItems.begin(); it != trackedItems.end(); /*update the iterator explicitly (not increment)*/) {
        if (it->second <= D) {
            trackedItems.erase(it);
        } else {
            ++it;
        }
    }
}

vector<uint64_t> LossyCounting::output() {
    vector<uint64_t> out;
    //TODO Ask about paper implementation vs Lecture Slide implementation
    for (auto const &pair: trackedItems) {
        out.push_back(pair.first);
    }
    return out;
}
