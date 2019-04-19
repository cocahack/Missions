#include <iostream>
#include <memory>
#include "custom_memory.h"
#include "util.h"
#include "custom_cpu.h"

int main() {

    std::unique_ptr<Memory> memory {new Memory};
    std::unique_ptr<Cpu> cpu {new Cpu(memory.get())};

    memory->store(0xA2, 444);
//    memory->peek(0x20000); // Assertion failed

    Word program[6] = {
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
        std::cout << (int16_t)*(reg_dump.get()+i) << "\n";
    }

    std::cout << (int16_t)memory->peek(0x100A2) << "\n";
    std::cout << (int16_t)memory->peek(0x100A4) ;


    return 0;
}