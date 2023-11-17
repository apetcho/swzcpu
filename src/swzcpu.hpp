#ifndef SWZCPU_H
#define SWZCPU_H

#include<cstdint>
#include<vector>
#include<array>
#include<map>

// -*----------------------------------------------------------------*-
// -*- namespace::swzcpu                                            -*-
// -*----------------------------------------------------------------*-
namespace swzcpu{
// -
using byte = std::uint8_t;
using u64 = std::uint64_t;
using i64 = std::int64_t;
using f64 = double;
// -

// -*-------------*-
// -*- Registers -*-
// -*-------------*-
enum class Register:i64{
    // -
    r0, r1, r2, r3, r4, r5, r6, r7,
    // -
    f0, f1, f2, f3, f4, f5, f6, f7,
};

static constexpr int MAX_REGISTERS = 16;

// -*-
enum class Instruction: i64{
    // -
    clf,
    // -
    cmp, cmpi, cmpf, cmpfi,
    // -
    mov, movf,
    // -
    sti, stf, ldi, ldf,
    // -
    lii, lif,
    // -
    psh, pop,
    pshf, popf,
    // -
    inc, dec,
    // -
    add, sub, mul, div,
    addf, subf, mulf, divf,
    // -
    jlz, jgz, jez, jnz, jmp,
    // -
    shl, shr,
    // -
    band, bor, bnot, bxor,
    land, lor, lnot,
    // -
    hlt,
};

static constexpr int NUM_INSTRUCTIONS = 42;

// -*--------------------*-
// -*- Computer i.e CPU -*-
// -*--------------------*-
class Computer{
private:
    std::vector<i64> m_memory;
    i64 m_size;

    // -*- registers
    i64 m_pc;
    i64 m_sp;
    std::array<i64, 8> m_regs;
    std::array<i64, 8> m_fregs;

    // -*- instructions
    Instruction m_inst;
    i64 m_dest;
    i64 m_src;

    // -*- flags
    i64 m_zero;
    i64 m_ltz;
    i64 m_gtz;

public:
    Computer(std::vector<i64> code);
    ~Computer() = default;
    void run();
    void fetch();
    void execute();
    void clear();
    void set(i64 a, i64 b);
    void fset(f64 a, f64 b);
    // -
private:
    static i64 firstByte;
    std::map<Register, i64> m_registers;
    std::map<Instruction, i64> m_instructions;

    void init_instructions();
    void init_registers();
    void set_instruction();
};

// -*----------------------------------------------------------------*-
}//-*- end::namespace::swzcpu
// -*----------------------------------------------------------------*-


#endif