#include "swzcpu.hpp"

// -*----------------------------------------------------------------*-
// -*- namespace::swzcpu                                            -*-
// -*----------------------------------------------------------------*-
namespace swzcpu{
// -

// -*-
void Computer::init_registers(){
    std::map<Register, i64> result{};
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
    this->m_registers = result;
}

// -*-
void Computer::init_instructions(){
    std::map<Instruction, i64> result{};
    result[Instruction::clf] = static_cast<i64>(Instruction::clf);
    result[Instruction::cmp] = static_cast<i64>(Instruction::cmp);
    result[Instruction::cmpi] = static_cast<i64>(Instruction::cmpi);
    result[Instruction::cmpf] = static_cast<i64>(Instruction::cmpf);
    result[Instruction::cmpfi] = static_cast<i64>(Instruction::cmpfi);

    result[Instruction::mov] = static_cast<i64>(Instruction::mov);
    result[Instruction::movf] = static_cast<i64>(Instruction::movf);

    result[Instruction::sti] = static_cast<i64>(Instruction::sti);
    result[Instruction::stf] = static_cast<i64>(Instruction::stf);
    result[Instruction::ldi] = static_cast<i64>(Instruction::ldi);
    result[Instruction::ldf] = static_cast<i64>(Instruction::ldf);
    result[Instruction::lii] = static_cast<i64>(Instruction::lii);
    result[Instruction::lif] = static_cast<i64>(Instruction::lif);

    result[Instruction::psh] = static_cast<i64>(Instruction::psh);
    result[Instruction::pshf] = static_cast<i64>(Instruction::pshf);
    result[Instruction::pop] = static_cast<i64>(Instruction::pop);
    result[Instruction::popf] = static_cast<i64>(Instruction::popf);

    result[Instruction::inc] = static_cast<i64>(Instruction::inc);
    result[Instruction::dec] = static_cast<i64>(Instruction::dec);

    result[Instruction::add] = static_cast<i64>(Instruction::add);
    result[Instruction::sub] = static_cast<i64>(Instruction::sub);
    result[Instruction::mul] = static_cast<i64>(Instruction::mul);
    result[Instruction::div] = static_cast<i64>(Instruction::div);

    result[Instruction::jlz] = static_cast<i64>(Instruction::jlz);
    result[Instruction::jgz] = static_cast<i64>(Instruction::jgz);
    result[Instruction::jez] = static_cast<i64>(Instruction::jez);
    result[Instruction::jnz] = static_cast<i64>(Instruction::jnz);
    result[Instruction::jmp] = static_cast<i64>(Instruction::jmp);

    result[Instruction::shl] = static_cast<i64>(Instruction::shl);
    result[Instruction::shr] = static_cast<i64>(Instruction::shr);

    result[Instruction::band] = static_cast<i64>(Instruction::band);
    result[Instruction::bor] = static_cast<i64>(Instruction::bor);
    result[Instruction::bnot] = static_cast<i64>(Instruction::bnot);
    result[Instruction::bxor] = static_cast<i64>(Instruction::bxor);
    result[Instruction::land] = static_cast<i64>(Instruction::land);
    result[Instruction::lor] = static_cast<i64>(Instruction::lor);
    result[Instruction::lnot] = static_cast<i64>(Instruction::lnot);

    result[Instruction::hlt] = static_cast<i64>(Instruction::hlt);

    this->m_instructions = result;
}

// -*- 0x00 00 00 00 00 00 00 FF

i64 Computer::firstByte = 0x00000000000000FF;
// -*-
Computer::Computer(std::vector<i64> code){
    this->m_size = code.size();
    this->m_memory = code;
    this->init_registers();
    this->init_instructions();
    this->m_sp = this->m_size - 1;
    this->m_pc = -1;
    this->m_inst = Instruction::clf;
}

// -*-
void Computer::run(){
    while(this->m_inst != Instruction::hlt){
        this->fetch();
        this->execute();
    }
}

void Computer::set_instruction(){
    auto val = this->m_memory[this->m_pc] & Computer::firstByte;
    for(auto entry: this->m_instructions){
        if(entry.second == val){
            this->m_inst = entry.first;
            return;
        }
    }
}

// -*-
void Computer::fetch(){
    this->m_pc++;
    this->set_instruction();
    this->m_dest = this->m_memory[this->m_pc+1];
    this->m_src = this->m_memory[this->m_pc+2];
}

// -*----------------------------------------------------------------*-
}//-*- end::namespace::swzcpu                                       -*-
// -*----------------------------------------------------------------*-