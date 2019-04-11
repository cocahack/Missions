#include <iostream>
#include "custom_memory.h"
#define print(content) std::cout << std::hex << content << "\n";
#define len(arr) sizeof arr / sizeof arr[0]
int main() {

    Memory *memory = new Memory();

    uint16_t program_counter = 0x0;

    uint16_t program_code[3] = {0x1111, 0x4444, 0x3333};
    memory->locate(program_code, len(program_code));

    for(auto i = 0; i < 3; ++i) {
        print(memory->fetch(program_counter));
        program_counter++;
    }

    print(memory->peek(2));

    memory->store(0x5000, 0x5555);

    print(memory->load(0x5000));

    print(memory->peek(0x15000));
    print(memory->peek(0x3));
    print(memory->peek(0x20000));


    delete memory;
    return 0;
}