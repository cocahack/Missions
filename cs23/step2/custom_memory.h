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
    Byte *mem_array, *code;

    Word access_two_bytes(uint32_t address);
public:
    Memory()
    {
        mem_array = new Byte[PROGRAM_TEXT_SIZE + PROGRAM_HEAP_SIZE];
        code = mem_array;
    }

    ~Memory()
    {
        delete[] mem_array;
    }

    Word peek(Double_word address);
    void locate(Word* program, size_t len);
    Word fetch(Word program_count);
    Word load(Word address);
    void store(Word address, Word data);
};

#endif //STEP2_CUSTOM_MEMORY_H
