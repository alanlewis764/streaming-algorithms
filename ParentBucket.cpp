//
// Created by Alan Lewis on 13/10/20.
//

#include "ParentBucket.h"

ParentBucket::ParentBucket(uint64_t value) : value(value),
                                                                                                      child(nullptr),
                                                                                                      next(nullptr),
                                                                                                      prev(nullptr) {}
