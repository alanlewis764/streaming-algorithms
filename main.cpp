#include <random>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include "ams_sampler.h"
#include "StickySampling.h"
using namespace std;


#define UNIVERSE_SIZE 4294967296


int main() {
    double s = 0.001;
    int N=0;
    cout << "hello" << endl;
    FILE *fin = fopen("/Users/alanlewis/CLionProjects/StreamComputingA2/zipf_z1_1.txt", "r");
    cout << "hello2" << endl;
    uint64_t data;
    unordered_map<uint64_t, uint64_t> map;
    StickySampling stickySampling(s, 0.0001, 0.1);
    while(fscanf(fin, "%lld\n", &data)!=EOF) {
        if (map.find(data) == map.end()) {
            map[data] = 1;
        } else {
            map[data]++;
        }
        stickySampling.update(data);
        N++;
    }
    unordered_set<uint64_t> mapOut;
    for (auto &pair: map) {
        if (pair.second > s*N) {
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
    cout << "STICKY SAMPLING: " << stickyOut.size() << endl;
    cout << "MAP SAMPLING:    " << mapOut.size() << endl;
    cout << "ERROR COUNT:     " << errorCount << endl;





    return 0;
}
