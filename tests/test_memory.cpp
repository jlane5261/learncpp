/*_________________________________________________

Tests to determine Stack and Heap sizes.
___________________________________________________

The stack is a region of memory reserved 
for efficient, structured, temporary storage
and is typically managed automatically by the CPU.

The heap is another region of the same 
RAM, set aside for dynamic, manually 
managed memory allocation.
___________________________________________________

CMDs on linux:
| stack | `ulimit -s`|
| heap  | `htop`     |
_________________________________________________*/


#include <iostream>
#include <new>

void testStack(int depth) {
    char buffer[1024]; // Allocate on stack
    std::cout << "Depth: " << depth << '\n';
    testStack(depth + 1); // Recursive call
}

void testHeap() {
    size_t size = 0;
    try {
        while (true) {
            new char[1024 * 1024]; // Allocate 1 MB on heap
            ++size;
        }
    } catch (std::bad_alloc&) {
        std::cout << "Heap size limit reached: " << size << " MB\n";
    }
}

int main() {
    // Warning: Calling these functions can lead to crashes and instability. Proceed with caution.
    // try {
    //     testStack(1);
    // } catch (...) {
    //     std::cout << "Stack size limit reached\n";
    // }
    //
    // testHeap();
    return 0;
}