//
// Created by MCC on 10/04/2019.
//

#include "custom_memory.h"
#include <stdexcept>
#include <iostream>


Word Memory::peek(Double_word address)
{
    assert(address < PROGRAM_TEXT_SIZE + PROGRAM_HEAP_SIZE);
    return mem_array[address];
}

void Memory::locate(Word *program, size_t len)
{
        for (auto i = 0; i < len; ++i) {
            *code = program[i];
            code++;
        }
}

Word Memory::fetch(Word program_count)
{
    return mem_array[program_count];
}

Word Memory::load(Word address)
{
    return mem_array[PROGRAM_TEXT_SIZE+address];
}

void Memory::store(Word address, Word data)
{
    *(mem_array + PROGRAM_TEXT_SIZE + address) = data;
}

Word Memory::access_two_bytes(Double_word address)
{
    return (Word )(*(mem_array + address)) | (Word)(*(mem_array + address + 1) << 8);
}
