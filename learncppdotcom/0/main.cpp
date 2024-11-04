#include <iostream>
#include <limits>

int main()
{
	std::cout << "Hello, world!";
	std::cout << "\nPress Enter to Close terminal\n";
	std::cin.clear(); // reset any error flags
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any characters in the input buffer until we find a newline
	std::cin.get(); // get one more char from the user (waits for user to press enter)
	return 0;
}