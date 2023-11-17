#include<iostream>

#include "swzcpu.hpp"

// -*-
struct Example{
    // -*-
    std::vector<swzcpu::i64> code;

    Example() = default;
    ~Example() = default;

    // -*- Make this a callable
    void operator()(){}
    // -*-
    
};