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
    Word add_impl(const Reg& r1, const Reg& r2)
    {
        return r1.get_value() + r2.get_value();
    }
    
    Word add_impl(const Reg& r1, const Word value)
    {
        return r1.get_value() + value;
    }

    Word sub_impl(const Reg& r1, const Reg& r2)
    {
        return (int16_t )r1.get_value() - (int16_t )r2.get_value();
    }

    Word sub_impl(const Reg& r1, const Word value)
    {
        return (int16_t )r1.get_value() - (int16_t )value;
    }
    
    Word and_impl(const Reg& r1, const Reg& r2)
    {
        return r1.get_value() & r2.get_value();
    }

    Word or_impl(const Reg& r1, const Reg& r2)
    {
        return r1.get_value() | r2.get_value();
    }
}
;

#endif //STEP2_ALU_H
