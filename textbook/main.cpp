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
    // Interesting question here: why does the answer not reset and cin wait for input if more than one character is returned?
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

int count_x(char* p, char x) 
// this function assumes that the char* is a C-style string 
// and points to a zero-terminated array of Char
// NOTE: this is different than a std::string
{
    if (p==nullptr) return 0;
    int count = 0;
    for (; *p!=0; ++p)
        if (*p==x)
            ++count;
    return count;
}

class Vector {
    public:
        Vector(int s) : elem{new double[s]}, sz{s} {}   // construct a Vector
        double& operator[](int i) { return elem[i]; }   // element access: subscripting
        int size() const { return sz; }                 // a "const" suffix means "can be applied to const objects"
    private:
        double* elem;   // pointer to the elements
        int sz;         // the number of elements
};

int main() {
    print_type_sizes();
    arithmetic_operations();
    types();
    accept_example();
    char a[] = {'h','e','l','l','o','0'};
    int count = count_x(a,'l');
    std::cout << "number of 'l' chars in string is: " << count << std::endl;
    Vector v(10);
    {v[3] = 5; v[8] = 3.1415; std::cout << v[2] << std::endl;}
    {double a = v.operator[](8); std::cout << a << std::endl;}
    {int size = v.size(); std::cout << size << std::endl;}
}