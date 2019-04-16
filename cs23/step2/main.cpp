#include <iostream>
#include <memory>
#include "custom_memory.h"
#include "util.h"
#include "custom_cpu.h"

int main() {

    std::unique_ptr<Memory> memory {new Memory};
    std::unique_ptr<Cpu> cpu {new Cpu(memory.get())};

//    uint16_t program_counter = 0x0;
//
//    uint16_t program_code[3] = {0x1111, 0x4444, 0x3333};
//    memory->locate(program_code, len(program_code));
//
//    for(auto i = 0; i < 3; ++i) {
//        print(memory->fetch(program_counter));
//        program_counter++;
//    }
//
//    print(memory->peek(2));
//
//    memory->store(0x5000, 0x5555);
//
//    print(memory->load(0x5000));
//
//    print(memory->peek(0x15000));
//    print(memory->peek(0x3));
//    print(memory->peek(0x20000));
//
//
//    cpu->reset();

    memory->store(0xA2, 444);

    uint16_t program[6] = {
            0xDA02,
            0xD8A0,
            0x1305,
            0x8464,
            0x9642,
            0x4724
    };

    memory->locate(program, len(program));
    cpu->execute(len(program));

    auto reg_dump = cpu->dump();

    for(int i=1; i<=7; ++i){
        std::cout << (int16_t )*(reg_dump.get()+i) << "\n";
    }

    std::cout << (int16_t)memory->peek(0x100A2) << "\n";
    std::cout << (int16_t)memory->peek(0x100A4) ;


    return 0;
}