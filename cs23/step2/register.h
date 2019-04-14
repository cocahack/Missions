//
// Created by MCC on 11/04/2019.
//

#ifndef STEP2_REGISTER_H
#define STEP2_REGISTER_H

#include <cstdint>
#include "constants.h"

class Reg
{
private:
    Word value;
public:
    Reg():value(0x0){}
    void store(Word value_){ value = value_; }
    Word get_value() const { return value; }
};


#endif //STEP2_REGISTER_H
