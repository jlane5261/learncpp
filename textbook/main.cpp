#include<stdio.h>
#include<iostream>
#include<cmath>

void print_type_sizes() {
    std::cout << "the size of char is: " << sizeof(char) << std::endl;
    std::cout << "the size of int is: " << sizeof(int) << std::endl;
    std::cout << "the size of double is: " << sizeof(double) << std::endl;
    std::cout << "the size of string is: " << sizeof(std::string) << std::endl;
}

void arithmetic_operations() {
    double d = 2.2;
    int i = 7;
    std::cout << "double d is " << d << "; and int i is " << i << ";" << std::endl;
    d = d+i;
    std::cout << "(d=d+i) d added with i will be a double equal to: " << d << std::endl;
    i = d*i;
    std::cout << "(i=d*i) i multiplied with d will be truncated to an int, equal to: " << i << std::endl;
}

void types() {
    std::cout << "assigning auto types ...\n";
    auto b = true;
    auto ch = 'x';
    auto i = 16;
    auto d = 1.3;
    auto z = sqrt(i);
    std::cout << "all variable types are valid!\n";
}

bool accept_example() {
    int tries = 1;
    while (tries < 4) {
        std::cout << "do you want to proceed? ('y' or 'n')\n";
        char answer = 0;
        std::cin >> answer;

        switch (answer) {
            case 'y':
                return true;
            case 'n':
                return false;
            default:
                std::cout << "sorry, answer unclear. Try Again!\n";
                tries++;
        }
    }
    std::cout << "too many tries, gonna take that as a 'no'.\n";
    return false;
}

int main() {
    print_type_sizes();
    arithmetic_operations();
    types();
    accept_example();
}