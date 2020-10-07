//
// Created by Alan Lewis on 29/9/20.
//

#include <vector>
#include "MisaGries.h"
using namespace std;

MisaGries::MisaGries(uint32_t t, uint32_t m) : t(t), m(m) {}

void MisaGries::update(uint32_t x) {
    m++;
    if (countMap.find(x) != countMap.end()) {
        //increment the counter for x
        countMap[x]++;
    } else if (countMap.size() < t-1){
        // add x to the countMap with a count of 1
        countMap[x] = 1;
    } else {
        // decrease the count of all values and remove any which have a count of zero
        for (auto it = countMap.begin(); it!=countMap.end(); /*update the iterator explicitly (not increment)*/) {
            it->second--;
            if (it->second==0) {
                countMap.erase(it);
            } else {
                ++it;
            }
        }
    }
}

vector<uint32_t> MisaGries::output() {
     vector<uint32_t> candidates;
     for (auto &elem: countMap) {
         candidates.push_back(elem.first);
     }
     return candidates;
}


