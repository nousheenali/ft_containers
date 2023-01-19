

#ifndef STACK_TEST_HPP
#define STACK_TEST_HPP

#include "../container_files/stack.hpp"
#include <iostream>
#include <exception>

template <typename STK>
void stack_tester(STK stck)
{
    std::cout << "Stack empty?TRUE(1)/FALSE(0): "<< stck.empty()<<std::endl;
    std::cout << "Pushing a values 3, 11 , 12 to stack..."<<std::endl;
    stck.push(3);
    stck.push(11);
    stck.push(12);
    std::cout << "Is stack empty?(1-TRUE/0-FALSE): "<< stck.empty()<<std::endl;
    std::cout << "Top value of stack: "<< stck.top()<<std::endl;
    stck.pop();
    std::cout << "Top value of stack: "<< stck.top()<<std::endl;
    std::cout << "empty: "<< stck.empty()<<std::endl;
}

#endif