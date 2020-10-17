#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include "StickySampling.h"
#include "SpaceSavingLinkedList.h"
#include "LossyCounting.h"

using namespace std;


#define UNIVERSE_SIZE 4294967296

double calculate_precision(const unordered_set<uint64_t> &exact, const unordered_set<uint64_t> &estimates) {
    double actuallyFrequent = 0;
    for (auto item: estimates) {
        if (exact.find(item) != exact.end()) {
            actuallyFrequent++;
        }
    }
    return actuallyFrequent / estimates.size();
}

unordered_set<uint64_t> get_keyset(const unordered_map<uint64_t, uint64_t> &map) {
    unordered_set<uint64_t> keys;
    for (auto item: map) {
        keys.insert(item.first);
    }
    return keys;
}

int main() {
    double s = 0.001;
    double eps = s / 10;
    double delta = 0.05; //TODO: Test this out...
    int N = 0;
    int t = 1/s;
    cout << "hello" << endl;
    FILE *fin = fopen("/Users/alanlewis/CLionProjects/StreamComputingA2/zipf_z1_1.txt", "r");
    cout << "hello2" << endl;
    uint64_t data;
    unordered_map<uint64_t, uint64_t> exactMap;
    StickySampling stickySampling(s, eps, delta);
    SpaceSavingLinkedList spaceSavingLinkedList(t);
    LossyCounting lossyCounting(eps, s);

    while (fscanf(fin, "%lld\n", &data) != EOF) {
        if (exactMap.find(data) == exactMap.end()) {
            exactMap[data] = 1;
        } else {
            exactMap[data]++;
        }
        stickySampling.update(data);
        spaceSavingLinkedList.update(data);
        lossyCounting.update(data);
        N++;
    }
    unordered_set<uint64_t> exactSet;
    for (auto &pair: exactMap) {
        if (pair.second > s * N) {
            exactSet.insert(pair.first);
        }
    }

    cout << "Sticky Precision: " << calculate_precision(exactSet, get_keyset(stickySampling.output())) << endl;
    cout << "Lossy Precision:  " << calculate_precision(exactSet, get_keyset(lossyCounting.output())) << endl;
    cout << "Space Precision:  " << calculate_precision(exactSet, get_keyset(spaceSavingLinkedList.output(s*N))) << endl;


    return 0;
}
