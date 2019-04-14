//
// Created by MCC on 11/04/2019.
//

#include <cstdint>
#include "custom_cpu.h"
#include "util.h"
#include "custom_memory.h"
#include <memory>
typedef void (Cpu::*fn)(Byte, Byte, Byte);

void Cpu::reset()
{
    auto length = len(registers);
    for(auto i=0; i < length; ++i){
        registers[i].store(0x0);
    }
    pc->store(0x0);
}

Word Cpu::fetch()
{
    auto ret = mem_ptr->fetch(pc->get_value());
    pc->store(pc->get_value() + 1);
    return ret;
}

void Cpu::execute_internally(Word raw_inst)
{
    static fn ops[] = {nullptr, &Cpu::load_from_reg, &Cpu::load_from_offset,
                &Cpu::store_from_reg, &Cpu::store_from_offset,
                &Cpu::and_reg, &Cpu::or_reg,
                &Cpu::add_reg, &Cpu::add_value,
                &Cpu::sub_reg, &Cpu::sub_value};

    Byte op = (raw_inst >> 12),
            dst_reg = ( raw_inst >> 9 ) & (0x7),
            second_reg = (raw_inst >> 6) & (0x7),
            padding = (raw_inst >> 3) & (0x7);
    Word offset = (padding & 0x4 ) == 0x4 ? raw_inst & 0x1F : raw_inst & 0x7;

//    try {
//        if(padding != 0x0 && padding != 0x4){
//            throw
//        }
        if(op == 0xD){
            Word move_to = raw_inst & 0x1FF;
            move_value(dst_reg, move_to);
        } else {
            auto instruction_func = ops[op];
            (this->*instruction_func)(dst_reg, second_reg, offset);
        }
//    } catch (){
//
//    }


}

std::unique_ptr<Word []> Cpu::dump()
{
    auto len = sizeof registers / sizeof registers[0];
    auto reg_values = std::make_unique<Word[]>(len);
    for(auto i = 0; i < len; ++i){
        reg_values[i] = registers[i].get_value();
    }
    return reg_values;
}

void Cpu::load_from_reg(Byte dst_reg, Byte base_reg, Byte offset_reg)
{
    auto address = registers[base_reg].get_value() + registers[offset_reg].get_value();
    registers[dst_reg].store(mem_ptr->peek(address));
}

void Cpu::load_from_offset(Byte dst_reg, Byte base_reg, Byte offset)
{
    auto address = registers[base_reg].get_value() + offset;
    registers[dst_reg].store(mem_ptr->peek(address));
}

void Cpu::store_from_reg(Byte src_reg, Byte base_reg, Byte offset_reg)
{
    auto address = registers[base_reg].get_value() + registers[offset_reg].get_value();
    mem_ptr->store(address, registers[src_reg].get_value());
}

void Cpu::store_from_offset(Byte src_reg, Byte base_reg, Byte offset)
{
    auto address = registers[base_reg].get_value() + offset;
    mem_ptr->store(address, registers[src_reg].get_value());
}

void Cpu::and_reg(Byte dst_reg, Byte lhs_reg, Byte rhs_reg)
{
    auto result = alu->and_impl(registers[lhs_reg], registers[rhs_reg]);
    registers[dst_reg].store(result);
}

void Cpu::or_reg(Byte dst_reg, Byte lhs_reg, Byte rhs_reg)
{
    auto result = alu->or_impl(registers[lhs_reg], registers[rhs_reg]);
    registers[dst_reg].store(result);
}

void Cpu::add_reg(Byte dst_reg, Byte lhs_reg, Byte rhs_reg)
{
    auto result = alu->add_impl(registers[lhs_reg], registers[rhs_reg]);
    registers[dst_reg].store(result);
}

void Cpu::add_value(Byte dst_reg, Byte operand_reg, Byte value)
{
    auto result = alu->add_impl(registers[operand_reg], value);
    registers[dst_reg].store(result);

}

void Cpu::sub_reg(Byte dst_reg, Byte lhs_reg, Byte rhs_reg)
{
    auto result = alu->sub_impl(registers[lhs_reg], registers[rhs_reg]);
    registers[dst_reg].store(result);
}

void Cpu::sub_value(Byte dst_reg, Byte operand_reg, Byte value)
{
    auto result = alu->add_impl(registers[operand_reg], value);
    registers[dst_reg].store(result);
}

void Cpu::move_value(Byte dst_reg, Word value)
{
    registers[dst_reg].store(value);
}

void Cpu::execute(size_t len)
{
    while(len--) {
        execute_internally(fetch());
    }
}
