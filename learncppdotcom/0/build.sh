# debug
#g++ -ggdb -Wall -o HelloWorld main.cpp


# release
g++ -O2 -DNDEBUG -std=c++17 -o HelloWorld main.cpp


# disable compiler extensions
#g++ -pedantic-errors -O2 -DNDEBUG -o HelloWorld main.cpp


# Warning flags
# -Wall, -Weffc++, -Wextra, -Wconversion, -Wsign-conversion, -Werror


# Standards
# -std=c++11, -std=c++14, -std=c++17, -std=c++20