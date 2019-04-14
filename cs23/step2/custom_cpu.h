//
// Created by MCC on 11/04/2019.
//

#ifndef STEP2_CUSTOM_CPU_H
#define STEP2_CUSTOM_CPU_H

#include <cstdint>
#include <memory>
#include "register.h"
#include "alu.h"
#include "custom_memory.h"



class Cpu
{
private:
    Reg *pc, *registers;
    Memory* mem_ptr;
    ALU* alu;

//    bool check_reg_num(Byte reg_num);

    void load_from_reg(Byte dst_reg, Byte base_reg, Byte offset_reg);
    void load_from_offset(Byte dst_reg, Byte base_reg, Byte offset);

    void store_from_reg(Byte src_reg, Byte base_reg, Byte offset_reg);
    void store_from_offset(Byte src_reg, Byte base_reg, Byte offset);

    void and_reg(Byte dst_reg, Byte lhs_reg, Byte rhs_reg);
    void or_reg(Byte dst_reg, Byte lhs_reg, Byte rhs_reg);

    void add_reg(Byte dst_reg, Byte lhs_reg, Byte rhs_reg);
    void add_value(Byte dst_reg, Byte operand_reg, Byte value);

    void sub_reg(Byte dst_reg, Byte lhs_reg, Byte rhs_reg);
    void sub_value(Byte dst_reg, Byte operand_reg, Byte value);

    void move_value(Byte dst_reg, Word value);

    void execute_internally(Word instruction);

public:
    Cpu(Memory* mem_ptr_):mem_ptr(mem_ptr_), pc(new Reg), registers(new Reg[8]), alu(new ALU){};
    ~Cpu(){delete[] registers;}

    void reset();
    Word fetch();
    void execute(size_t len);
    std::unique_ptr<Word []> dump();
};

#endif //STEP2_CUSTOM_CPU_H
