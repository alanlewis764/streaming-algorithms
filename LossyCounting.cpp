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
    N++;
    b_current =  ceil(N/w);
    // if x is already tracked, increment the counter add it with count D+1
    if (trackedItems.find(x) != trackedItems.end()) {
        trackedItems[x].first++;
    } else {
        trackedItems[x] = {1, b_current-1};
    }

    // if D =/= floor m/k then update D and do maintenance
    if (N % w == 0) {
        maintenance();
    }


}

void LossyCounting::maintenance() {
    // delete all items that have a count D
    for (auto it = trackedItems.begin(); it != trackedItems.end(); /*update the iterator explicitly (not increment)*/) {
        if (it->second.first + it->second.second <= b_current) {
            trackedItems.erase(it);
        } else {
            ++it;
        }
    }
}

unordered_map<uint64_t, uint64_t> LossyCounting::output() {
    unordered_map<uint64_t, uint64_t> returnMap;
    for (auto const &pair: trackedItems) {
        uint64_t itemID = pair.first;
        uint32_t f = pair.second.first;
        if (f >= (s-eps) * N) {
            returnMap[itemID] = f;
        }
        return returnMap;
    }

}
