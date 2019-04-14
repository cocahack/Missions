//
// Created by MCC on 10/04/2019.
//

#include "custom_memory.h"
#include <stdexcept>
#include <iostream>


Word Memory::peek(Double_word address)
{
    try {
        if(address < PROGRAM_TEXT_SIZE + PROGRAM_HEAP_SIZE){
            return access_two_bytes(address);
        }
        else {
            throw std::out_of_range(OOR_MSG);
        }
    } catch(const std::out_of_range& oor){
        std::cerr << "Memory access failed: " << oor.what() << "\n";
    }
}

void Memory::locate(Word *program, size_t len)
{
        for (auto i = 0; i < len; ++i) {
            *code = (Byte)program[i];
            *(code + 1) = program[i] >> 8;
            code += 2;
        }
}

Word Memory::fetch(Word program_count)
{
    return access_two_bytes(program_count * 2);
}

Word Memory::load(Word address)
{
    return access_two_bytes(PROGRAM_TEXT_SIZE + address);
}

void Memory::store(Word address, Word data)
{
    *(mem_array + PROGRAM_TEXT_SIZE + address) = (Byte)data;
    *(mem_array + PROGRAM_TEXT_SIZE + address + 1) = (data >> 8);
}

Word Memory::access_two_bytes(Double_word address)
{
    return (Word )(*(mem_array + address)) | (Word)(*(mem_array + address + 1) << 8);
}
