#include <random>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include "ams_sampler.h"
#include "StickySampling.h"
#include "SpaceSavingLinkedList.h"
#include "SpaceSaving.h"
using namespace std;


#define UNIVERSE_SIZE 4294967296
double calculate_precision(const unordered_set<uint64_t>& exact, const unordered_set<uint64_t>& estimates) {
    double actuallyFrequent = 0;
    for (auto item: estimates) {
        if (exact.find(item) != exact.end()) {
            actuallyFrequent++;
        }
    }
    return actuallyFrequent/estimates.size();
}

int main() {
    double s = 0.001;
    double eps = s/10;
    double delta = 0.05; //TODO: Test this out...
    int N = 0;
    cout << "hello" << endl;
    FILE *fin = fopen("/Users/alanlewis/CLionProjects/StreamComputingA2/zipf_z1_1.txt", "r");
    cout << "hello2" << endl;
    uint64_t data;
    unordered_map<uint64_t, uint64_t> map;
    StickySampling stickySampling(s, 0.0001, 0.1);
    SpaceSavingLinkedList spaceSavingLinkedList(10);
    SpaceSaving spaceSaving(10);
    while (fscanf(fin, "%lld\n", &data) != EOF) {
        if (map.find(data) == map.end()) {
            map[data] = 1;
        } else {
            map[data]++;
        }
        spaceSavingLinkedList.update(data);
        stickySampling.update(data);
        spaceSaving.update(data);
        N++;
    }
    unordered_set<uint64_t> mapOut;
    for (auto &pair: map) {
        if (pair.second > s * N) {
            mapOut.insert(pair.first);
        }
    }
    int errorCount = 0;
    vector<uint64_t> stickyOut = stickySampling.output();
    for (auto f: stickyOut) {
        if (mapOut.find(f) == mapOut.end()) {
            errorCount++;
        }
    }
    vector<pair<uint64_t, uint64_t>> sortedElements(map.begin(), map.end());
    std::sort(sortedElements.begin(), sortedElements.end(),[](auto &left, auto &right) {
        return left.second > right.second;
    });
    sortedElements.resize(10);
    cout << "Top elements: " << endl;
    for (auto e: sortedElements) {
        cout << "(" << e.first << "," << e.second << ")" << " ";
    }
    cout << endl;

    cout << "STICKY SAMPLING: " << stickyOut.size() << endl;
    cout << "MAP SAMPLING:    " << mapOut.size() << endl;
    cout << "ERROR COUNT:     " << errorCount << endl;


    return 0;
}
