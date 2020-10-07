//
// Created by Alan Lewis on 22/9/20.
//

#ifndef UNTITLED1_AMS_SAMPLER_H
#define UNTITLED1_AMS_SAMPLER_H


#include <cstdint>

class ams_sampler {
    uint32_t m, r, s;
    uint8_t k;
public:
    ams_sampler(uint32_t m, uint8_t k, uint32_t s, uint32_t r);
    explicit ams_sampler(uint8_t k);

    void update(uint32_t x);

    double output() const;
};


#endif //UNTITLED1_AMS_SAMPLER_H
