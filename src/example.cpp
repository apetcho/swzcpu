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
    void operator()(){}
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

    void print(const std::array<swzcpu::f64, 8>& vec);
};