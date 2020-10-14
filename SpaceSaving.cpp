//
// Created by Alan Lewis on 10/10/20.
//

#include <vector>
#include "SpaceSaving.h"
using namespace std;

SpaceSaving::SpaceSaving(uint32_t t) : t(t) {}

void SpaceSaving::update(uint64_t x) {
    // if it is already being tracked then increment the counter
    if (trackedItems.find(x) != trackedItems.end()) {
        trackedItems[x]++;
    } else if (trackedItems.size() < t) {
        // add it to the tracked items with a count of 1
        trackedItems[x] = 1;
    } else {
        // remove item with least count, c and add x with out c + 1
        uint64_t minCount = UINT64_MAX;
        uint64_t minItem;
        for (auto &item: trackedItems) {
            if (item.second < minCount) {
                minItem = item.first;
                minCount = item.second;
            }
        }
        trackedItems.erase(minItem);
        trackedItems[x] = minCount + 1;
    }
}

vector<uint64_t> SpaceSaving::output() {
    vector<uint64_t> ret;
    for (const auto &item: trackedItems) {
        ret.push_back(item.first);
    }
    return ret;
}
