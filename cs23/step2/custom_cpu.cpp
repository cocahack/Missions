//
// Created by MCC on 11/04/2019.
//

#include <cstdint>
#include "custom_cpu.h"
#include "util.h"
#include "custom_memory.h"

void Cpu::reset()
{
    auto length = len(registers);
    for(auto i=0; i < length; ++i){
        registers[i].store(0x0);
    }
    pc->store(0x0);
}

uint16_t Cpu::fetch(Memory *mem)
{
    auto ret = mem->fetch(pc->get_value());
    pc->store(pc->get_value() + 1);
    return ret;
}

void Cpu::execute(uint16_t instruction)
{

}

uint16_t *Cpu::dump()
{
    return nullptr;
}
