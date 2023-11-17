#include "swzcpu.hpp"

// -*----------------------------------------------------------------*-
// -*- namespace::swzcpu                                            -*-
// -*----------------------------------------------------------------*-
namespace swzcpu{
// -
std::map<Register, i64> Computer::registers;
std::map<Instruction, i64> Computer::instructions;

// -*-
std::map<Register, i64> init_registers(){
    std::map<Register, i64> result;
    result[Register::r0] = static_cast<i64>(Register::r0);
    result[Register::r1] = static_cast<i64>(Register::r1);
    result[Register::r2] = static_cast<i64>(Register::r2);
    result[Register::r3] = static_cast<i64>(Register::r3);
    result[Register::r4] = static_cast<i64>(Register::r4);
    result[Register::r5] = static_cast<i64>(Register::r5);
    result[Register::r6] = static_cast<i64>(Register::r6);
    result[Register::r7] = static_cast<i64>(Register::r7);
    result[Register::f0] = static_cast<i64>(Register::f0);
    result[Register::f1] = static_cast<i64>(Register::f1);
    result[Register::f2] = static_cast<i64>(Register::f2);
    result[Register::f3] = static_cast<i64>(Register::f3);
    result[Register::f4] = static_cast<i64>(Register::f4);
    result[Register::f5] = static_cast<i64>(Register::f5);
    result[Register::f6] = static_cast<i64>(Register::f6);
    result[Register::f7] = static_cast<i64>(Register::f7);
    return result;
}


// -*----------------------------------------------------------------*-
}//-*- end::namespace::swzcpu                                       -*-
// -*----------------------------------------------------------------*-