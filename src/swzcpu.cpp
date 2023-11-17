#include "swzcpu.hpp"

// -*----------------------------------------------------------------*-
// -*- namespace::swzcpu                                            -*-
// -*----------------------------------------------------------------*-
namespace swzcpu{
// -
std::map<Register, i64> Computer::registers;
// -*-
void Computer::init_registers(){
    std::map<Register, i64>& result = Computer::registers;
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
}

// -*-
std::map<Instruction, i64> Computer::instructions;
// -*-
void Computer::init_instructions(){
    std::map<Instruction, i64>& result = Computer::instructions;
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

    
}

// -*- 0x00 00 00 00 00 00 00 FF

i64 Computer::firstByte = 0x00000000000000FF;
// -*-
Computer::Computer(std::vector<i64> code){
    if(Computer::instructions.empty()){
        Computer::init_instructions();
    }
    if(Computer::registers.empty()){
        Computer::init_registers();
    }
    this->m_size = code.size();
    this->m_memory = code;
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
    for(auto entry: this->instructions){
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

void Computer::execute(){
    switch(this->m_inst){
    case Instruction::clf:
        this->clear();
        break;
    case Instruction::cmp: // compare integers
        this->set(this->m_regs[this->m_dest], this->m_regs[this->m_src]);
        this->m_pc += 2;
        break;
    case Instruction::cmpi: // compare integers immediate
        this->set(this->m_regs[this->m_dest], this->m_src);
        this->m_pc += 2;
        break;
    case Instruction::cmpf: // compare float
        this->fset(
            this->m_fregs[this->m_dest-8],
            static_cast<f64>(this->m_fregs[this->m_src-8])
        );
        this->m_pc += 2;
        break;
    case Instruction::cmpfi: // compare float immediate
        this->fset(
            this->m_fregs[this->m_dest-8], static_cast<f64>(this->m_src)
        );
        this->m_pc += 2;
        break;
    case Instruction::mov: // move  integer data
        this->m_regs[this->m_dest] = this->m_regs[this->m_src];
        this->m_pc += 2;
        break;
    case Instruction::movf: // move float data
        this->m_fregs[this->m_dest-8] = this->m_fregs[this->m_src - 8];
        this->m_pc += 2;
        break;
    case Instruction::sti: // store integer data
        this->m_memory[this->m_dest] = this->m_regs[this->m_src];
        this->m_pc += 2;
        break;
    case Instruction::stf:  // store float data
        this->m_memory[this->m_dest] = static_cast<i64>(this->m_fregs[this->m_src-8]);
        this->m_pc += 2;
        break;
    case Instruction::ldi:  // load integer data
        this->m_regs[this->m_dest] = this->m_memory[this->m_src];
        this->m_pc += 2;
        break;
    case Instruction::ldf:  // load float data
        this->m_fregs[this->m_dest-8] = static_cast<f64>(this->m_memory[this->m_src]);
        this->m_pc += 2;
        break;
    case Instruction::lii:  // load immediate integer
        this->m_regs[this->m_dest] = this->m_src;
        this->m_pc += 2;
        break;
    case Instruction::lif:  // load immediate float
        this->m_fregs[this->m_dest-8] = static_cast<f64>(this->m_src);
        this->m_pc += 2;
        break;
    case Instruction::psh:  // push integer
        this->m_memory[--this->m_sp] = this->m_regs[this->m_memory[++this->m_pc]];
        break;
    case Instruction::pshf: // push float
        this->m_memory[--this->m_sp] = static_cast<i64>(
            this->m_fregs[this->m_memory[++this->m_pc]-8]
        );
        break;
    case Instruction::pop:
        this->m_regs[this->m_memory[++this->m_pc]] = this->m_memory[this->m_sp++];
        break;
    case Instruction::popf:
        this->m_fregs[this->m_memory[++this->m_pc]-8] = static_cast<f64>(
            this->m_memory[this->m_sp++]
        );
        break;
    case Instruction::inc:
        this->m_regs[this->m_dest]++;
        this->m_pc++;
        break;
    case Instruction::dec:
        this->m_regs[this->m_dest]--;
        this->m_pc++;
        break;
    case Instruction::add:
        this->m_regs[this->m_dest] += this->m_regs[this->m_src];
        this->m_pc += 2;
        break;
    case Instruction::sub:
        this->m_regs[this->m_dest] -= this->m_regs[this->m_src];
        this->m_pc += 2;
        break;
    case Instruction::mul:
        this->m_regs[this->m_dest] *= this->m_regs[this->m_src];
        this->m_pc += 2;
        break;
    case Instruction::div:
        this->m_regs[this->m_dest] /= this->m_regs[this->m_src];
        this->m_pc += 2;
        break;
    case Instruction::addf:
        this->m_fregs[this->m_dest -8] += this->m_fregs[this->m_src - 8];
        this->m_pc += 2;
        break;
    case Instruction::subf:
        this->m_fregs[this->m_dest-8] -= this->m_fregs[this->m_src-8];
        this->m_pc += 2;
        break;
    case Instruction::mulf:
        this->m_fregs[this->m_dest-8] *= this->m_fregs[this->m_src-8];
        this->m_pc += 2;
        break;
    case Instruction::divf:
        this->m_fregs[this->m_dest-8] /= this->m_fregs[this->m_src-8];
        this->m_pc += 2;
        break;
    case Instruction::jlz:
        if(this->m_ltz){
            this->m_pc = this->m_memory[++(this->m_pc)];
        }else{
            this->m_pc++;
        }
        break;
    case Instruction::jgz:
        if(this->m_gtz){
            this->m_pc = this->m_memory[++(this->m_pc)];
        }else{
            this->m_pc++;
        }
        break;
    case Instruction::jez:
        if(this->m_zero){
            this->m_pc = this->m_memory[++(this->m_pc)];
        }else{
            this->m_pc++;
        }
        break;
    case Instruction::jnz:
        if(!this->m_zero){
            this->m_pc = this->m_memory[++(this->m_pc)];
        }else{
            this->m_pc++;
        }
        break;
    case Instruction::jmp:
        this->m_pc = this->m_memory[++(this->m_pc)];
        break;
    case Instruction::shl:
        this->m_regs[this->m_dest] <<= this->m_regs[this->m_src];
        this->m_pc += 2;
        break;
    case Instruction::shr:
        this->m_regs[this->m_dest] >>= this->m_regs[this->m_src];
        this->m_pc += 2;
        break;
    case Instruction::band:
        this->m_regs[this->m_dest] &= this->m_regs[this->m_src];
        this->m_pc += 2;
        break;
    case Instruction::bor:
        this->m_regs[this->m_dest] |= this->m_regs[this->m_src];
        this->m_pc += 2;
        break;
    case Instruction::bnot:
        this->m_regs[this->m_dest] = ~this->m_regs[this->m_dest];
        this->m_pc++;
        break;
    case Instruction::bxor:
        this->m_regs[this->m_dest] ^= this->m_regs[this->m_src];
        this->m_pc += 2;
        break;
    case Instruction::land:
        this->m_regs[this->m_dest] = this->m_regs[this->m_dest] && this->m_regs[this->m_src];
        this->m_pc += 2;
        break;
    case Instruction::lor:
        this->m_regs[this->m_dest] = this->m_regs[this->m_dest] || this->m_regs[this->m_src];
        this->m_pc += 2;
        break;
    case Instruction::lnot:
        this->m_regs[this->m_dest] = !this->m_regs[this->m_dest];
        this->m_pc++;
        break;
    default: // Instruction::hlt is handled in run() method
        break;
    }
}

// -*-
void Computer::clear(){
    this->m_zero = 0;
    this->m_ltz = 0;
    this->m_gtz = 0;
}

// -*-
void Computer::set(i64 x, i64 y){
    i64 delta = x - y;
    this->m_zero = (delta == 0);
    this->m_ltz = (delta < 0);
    this->m_gtz = (delta > 0);
}

// -*-
void Computer::fset(f64 x, f64 y){
    f64 delta = x - y;
    this->m_zero = (delta == 0);
    this->m_ltz = (delta < 0);
    this->m_gtz = (delta > 0);
}

// -*----------------------------------------------------------------*-
}//-*- end::namespace::swzcpu                                       -*-
// -*----------------------------------------------------------------*-