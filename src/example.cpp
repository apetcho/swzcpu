#include<iostream>
#include<iomanip>
#include "swzcpu.hpp"

// -*-
struct Example{
    // -*-
    std::vector<swzcpu::i64> code;

    Example() = default;
    ~Example() = default;
    Example(std::vector<swzcpu::i64> vec): code{vec}{}

    // -*- Make this a callable
    void operator()(){
        std::cout << "-*--------------------------------------*-\n";
        std::cout << "-*-      I N S T R U C T I O N S       -*-\n";
        std::cout << "-*--------------------------------------*-\n";
        this->print(this->code);
        std::cout << std::endl;
        swzcpu::Computer cpu(this->code);
        cpu.run();
        std::cout << std::endl;
        std::cout << "-*--------------------------------------*-\n";
        std::cout << "-*-          R E G I S T E R S         -*-\n";
        std::cout << "-*--------------------------------------*-\n";
        this->print(cpu.get_registers());
        std::cout << std::endl;
        std::cout << "-*--------------------------------------*-\n";
        std::cout << "-*- F L O A T I N G  R E G I S T E R S -*-\n";
        std::cout << "-*--------------------------------------*-\n";
        this->print(cpu.get_fregisters());
        std::cout << std::endl;
    }

private:
    // -*-
    void print(const std::vector<swzcpu::i64>& vec){
        for(auto item: vec){
            std::cout << "0x" << std::setw(16) << std::setfill('0') << std::hex << item << "\n";
        }
        std::cout << std::endl;
    }

    // -*-
    void print(const std::array<swzcpu::i64, 8>& vec){
        for(auto item: vec){
            std::cout << "0x" << std::setw(16) << std::setfill('0') << std::hex << item << "\n";
        }
        std::cout << std::endl;
    }

    // -*-
    void print(const std::array<swzcpu::f64, 8>& vec){
        for(auto item: vec){
            std::cout << "0x" << std::setw(16) << std::setfill('0') << std::hex << item << "\n";
        }
        std::cout << std::endl;
    }
};

// -*-
int main(int argc, char **argv){
    using namespace swzcpu;
    Computer::init_registers();
    Computer::init_instructions();
    std::vector<i64> code = {
        // - lii r0, 1
        Computer::instructions[Instruction::lii],
        Computer::registers[Register::r0],
        1,
        // - lii, r1, 5
        Computer::instructions[Instruction::lii],
        Computer::registers[Register::r1],
        5,
        // - lii r2, 1
        Computer::instructions[Instruction::lii],
        Computer::registers[Register::r2],
        1,
        // - mul, r0, r1
        Computer::instructions[Instruction::mul],
        Computer::registers[Register::r0],
        Computer::registers[Register::r1],
        // - sub, r1, r2
        Computer::instructions[Instruction::sub],
        Computer::registers[Register::r1],
        Computer::registers[Register::r2],
        // - jnz, 8
        Computer::instructions[Instruction::jnz], 8,
        // - hlt
        Computer::instructions[Instruction::hlt]
    };

    // -*-
    Example app(code);
    app();

    return EXIT_SUCCESS;
}