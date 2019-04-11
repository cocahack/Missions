//
// Created by MCC on 11/04/2019.
//

#ifndef STEP2_CUSTOM_CPU_H
#define STEP2_CUSTOM_CPU_H

#include <cstdint>
#include "register.h"
#include "alu.h"

class cpu
{
private:
    reg *pc, *r;

public:
    cpu(){ pc = new reg, r = new reg[7]; }
    ~cpu(){delete[] r;}
};

#endif //STEP2_CUSTOM_CPU_H
