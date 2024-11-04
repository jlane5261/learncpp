// W3 C++ Tutorial
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>

// #define INFO_MODE

int main() {
    #ifdef INFO_MODE
    // Check variable sizes
        std::cout << "Size of bool: " << sizeof(bool) << " Bytes" << std::endl;
        std::cout << "Size of char: " << sizeof(char) << " Bytes" << std::endl;
        std::cout << "Size of short: " << sizeof(short) << " Bytes" << std::endl;
        std::cout << "Size of int: " << sizeof(int) << " Bytes" << std::endl;
        std::cout << "Size of long: " << sizeof(long) << " Bytes" << std::endl;
        std::cout << "Size of float: " << sizeof(float) << " Bytes" << std::endl;
        std::cout << "Size of double: " << sizeof(double) << " Bytes" << std::endl;
        std::cout << "Size of string: " << sizeof(std::string) << " Bytes" << std::endl;
        
        long long result = 2147483646LL+5LL;
        std::cout << result << std::endl;
    #endif
    // Create a vector called cars that will store strings
    std::vector<std::string> cars = {"Volvo", "BMW", "Ford", "Mazda"};

    std::sort(cars.begin(),cars.end());
    std::cout << *cars.begin() << std::endl;
    std::cerr << "errror" << std::endl;
    return 0;
} 