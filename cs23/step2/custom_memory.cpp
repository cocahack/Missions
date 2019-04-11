//
// Created by MCC on 10/04/2019.
//

#include "custom_memory.h"
#include <stdexcept>
#include <iostream>


uint16_t Memory::peek(uint32_t address)
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

void Memory::locate(uint16_t *program, size_t len)
{
        for (auto i = 0; i < len; ++i) {
            *code = (uint8_t)program[i];
            *(code + 1) = program[i] >> 8;
            code += 2;
        }
}

uint16_t Memory::fetch(uint16_t program_count)
{
    return access_two_bytes(program_count * 2);
}

uint16_t Memory::load(uint16_t address)
{
    return access_two_bytes(PROGRAM_TEXT_SIZE + address);
}

void Memory::store(uint16_t address, uint16_t data)
{
    *(mem_array + PROGRAM_TEXT_SIZE + address) = (uint8_t)data;
    *(mem_array + PROGRAM_TEXT_SIZE + address + 1) = (data >> 8);
}

uint16_t Memory::access_two_bytes(uint32_t address)
{
    return (uint16_t )(*(mem_array + address)) | (uint16_t)(*(mem_array + address + 1) << 8);
}
