//
// Created by MCC on 11/04/2019.
//

#ifndef STEP2_ALU_H
#define STEP2_ALU_H

#include <cstdint>
#include "register.h"

class ALU
{
public:
    uint16_t add_impl(const reg& r1, const reg& r2)
    {
        return r1.get_value() + r2.get_value();
    }

    uint16_t sub_impl(const reg& r1, const reg& r2)
    {
        return r1.get_value() - r2.get_value();
    }

    uint16_t and_impl(const reg& r1, const reg& r2)
    {
        return r1.get_value() & r2.get_value();
    }

    uint16_t or_impl(const reg& r1, const reg& r2)
    {
        return r1.get_value() | r2.get_value();
    }
};

#endif //STEP2_ALU_H
