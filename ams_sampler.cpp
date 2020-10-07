//
// Created by Alan Lewis on 22/9/20.
//

#include <random>
#include "ams_sampler.h"

using namespace std;

ams_sampler::ams_sampler(uint32_t m, uint8_t k, uint32_t s, uint32_t r) : m(m), k(k), s(s),
                                                                          r(r) {}

ams_sampler::ams_sampler(uint8_t k) {
    this->k = k;
    this->m = 0;
    this->s = 0;
    this->r = 0;
}

void ams_sampler::update(uint32_t x) {
    // increment m
    m++;

    // generate a number uniformly at random between 0 and m
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distribution(0, 1);

    // happens with probability 1/m
    if (distribution(gen) < 1.0 / m) {
        s = x;
        r = 1;
    } else if (x == s) {
        r++;
    }
}

double ams_sampler::output() const {
    return m*(pow(r, k) - pow(r-1, k));
}
