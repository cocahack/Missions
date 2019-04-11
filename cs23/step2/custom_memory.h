//
// Created by MCC on 10/04/2019.
//

#ifndef STEP2_CUSTOM_MEMORY_H
#define STEP2_CUSTOM_MEMORY_H

#include <cstdint>
#include "constants.h"

class Memory
{
private:
    uint8_t *mem_array, *code;

    uint16_t access_two_bytes(uint32_t address);
public:
    Memory()
    {
        mem_array = new uint8_t[PROGRAM_TEXT_SIZE + PROGRAM_HEAP_SIZE];
        code = mem_array + 0x0000;
    }

    ~Memory()
    {
        delete[] mem_array;
    }

    uint16_t peek(uint32_t address);
    void locate(uint16_t * program, size_t len);
    uint16_t fetch(uint16_t program_count);
    uint16_t load(uint16_t address);
    void store(uint16_t address, uint16_t data);
};

#endif //STEP2_CUSTOM_MEMORY_H
