#include<iostream>
#include<stdio.h>
#include<unordered_map>

int main() {
    // Declare a hashmap that maps strings to integers
    std::unordered_map<std::string, int> myMap;

    // Insert key-value pairs
    myMap["apple"] = 3;
    myMap["banana"] = 5;
    myMap["orange"] = 7;

    // Access elements by key
    std::cout << "Apples: " << myMap["apple"] << std::endl;

    // Update a value
    myMap["apple"] = 10;

    // Check if a key exists
    if (myMap.find("banana") != myMap.end()) {
        std::cout << "Bananas found in the map." << std::endl;
    }

    // Remove a key-value pair
    myMap.erase("orange");

    // Iterate over all key-value pairs
    for (const auto& pair : myMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    return 0;
}