/* compile and run this code to determine the default c++ std that a compiler is using
199711 for C++98,
201103 for C++11
201402 for C++14
201703 for C++17
*/

#include <iostream>

int main()
 { std::cout << __cplusplus << std::endl; }