//
// Created by MCC on 11/04/2019.
//

#ifndef STEP2_REGISTER_H
#define STEP2_REGISTER_H

#include <cstdint>

class reg
{
private:
    uint16_t value;
public:
    reg():value(0x0){}
    void store(uint16_t value_){ value = value_; }
    uint16_t get_value() { return value; }
};


#endif //STEP2_REGISTER_H
