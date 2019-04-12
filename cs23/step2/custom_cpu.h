//
// Created by MCC on 11/04/2019.
//

#ifndef STEP2_CUSTOM_CPU_H
#define STEP2_CUSTOM_CPU_H

#include <cstdint>
#include "register.h"
#include "alu.h"
#include "custom_memory.h"

class Cpu
{
private:
    Reg *pc, *registers;



public:
    Cpu(){ pc = new Reg, registers = new Reg[7]; }
    ~Cpu(){delete[] registers;}

    void reset();
    uint16_t fetch(Memory* mem);
    void execute(uint16_t instruction);
    uint16_t* dump();
};

#endif //STEP2_CUSTOM_CPU_H
