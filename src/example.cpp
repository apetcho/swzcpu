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
        this->print(cpu.registers());
        std::cout << std::endl;
        std::cout << "-*--------------------------------------*-\n";
        std::cout << "-*- F L O A T I N G  R E G I S T E R S -*-\n";
        std::cout << "-*--------------------------------------*-\n";
        this->print(cpu.fregisters());
        std::cout << std::endl;
    }

private:
    // -*-
    void print(const std::vector<swzcpu::i64>& vec){
        for(auto item: vec){
            std::cout << std::dec << item << " ";
        }
        std::cout << std::endl;
    }

    // -*-
    void print(const std::array<swzcpu::i64, 8>& vec){
        for(auto item: vec){
            std::cout << std::dec << item << " ";
        }
        std::cout << std::endl;
    }

    // -*-
    void print(const std::array<swzcpu::f64, 8>& vec){
        for(auto item: vec){
            std::cout << std::dec << item << " ";
        }
        std::cout << std::endl;
    }
};