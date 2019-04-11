//
// Created by MCC on 11/04/2019.
//

#ifndef STEP2_ALU_H
#define STEP2_ALU_H

#include <cstdint>
#include "register.h"

class alu
{
public:
    uint16_t add_impl(const reg& r1, const reg& r2);
    uint16_t sub_impl(const reg& r1, const reg& r2);
    uint16_t and_impl(const reg& r1, const reg& r2);
    uint16_t or_impl(const reg& r1, const reg& r2);
};

#endif //STEP2_ALU_H
