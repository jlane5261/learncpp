## CHAPTER 1
When Learning C++, 
focus on fundamental concepts like
    - Type Safety - compile time checks to ensure variable types are used correctly
    - Resource management - ability to manage memory, files, network connections
    - Invariants - help maintain a class's consistent internal state

focus on programming techniques like
    - resource management using scoped objects
    - the use of iterators in algorithms


### ADVICE: Each chapter contains an "Advice"  section
This is a set of concrete recommendations related to the chapter contents. (Rough rules of thumb, not immutable laws)
    - Low-level code isn't necessarily efficient; don't avoid classes, templates, and STL components out of fear of prfm issues
    - Except for `new`,`delete`,`typeid`,`dynamic_cast`,`throw` operators, and the `try`-block, 
      individual C++ expressions and statements need no run-time support. (Essential for embedded and high-prfm apps)
    - 1.2.1 and 1.2.2 are wealthy chunks of text
    - "A constructor creates the execution env for the member functions and the destructor reverses that."
        - This is the ROOT for C++'s strategies for resource management (causing a demand for exceptions)
    - if data has an invariant, encapsulate it

---------------------------------------------------------------------------------------------------------------------
## CHAPTER 2 - The Basics

The ISO C++ standard defines two kinds of entities:
 1. Core Launguage Features: such as built in types (char, int, etc.) and loops (for-loops and while-statements)
 2. STL components: such as containers (vector and map) and I/O operations (`<<` and `getline()`)

fun fact - the `<<` operator is called "put to" and it will write it's second argument onto its first
            the `>>` operator is called "get from" and is used for input

Some definitions:
 1. A _type_ defines a set of possible values and a set of operations (for an object)
 2. An _object_ is some memory that holds a value of some type
 3. A _value_ is a set of bits interpreted according to a type
 4. A _variable_ is a named object

the *auto* type is to be used when there is not a specific reason to mention the type explicitly

__Constants__
*const* - meaning roughly "I promise not to change this value"
*constexpr* - meaning roughly "to be evaluated at compile time" <- this is mainly used for performance

big difference here is when evaluation happens.
for example
    const int dmv = 17;
    int var = 17;
    constexpr double max1 = 1.4*square(dmv);        //OK if square(17) is a constant expression
    constexpr double max2 = 1.4*square(var);        //error: var is not a constant expression
    const double max3 = 1.4*square(var);            //OK, but evaluated at run time

For a function to be usable in a constant expression, it must be defined constexpr.
    constexpr double square(double x) {return x*x;} //REQT: must be rather simple: a return-statement computing a value

*TODO* Watch a video explaining const and constexpr, and it's use cases

__Pointers, Arrays, and Loops__
[] - means "array of"
example:
    char v[6]

    this is an array of chars with a length of 6 (v[0]-v[5]) named "v"

* - means "pointer to"
example:
    char* p;

    this is a pointer to a char, name "p"

A Pointer variable can hold the address of an obhject of the appropriate type:
    char* p = &v[3];    //p points to v's fourth element
    char x = *p;        //*p is the object that p points to

for loops 
    for (statement 1; statement 2; statement 3) {}

    statement 1: do this initially before the loop
    statement 2: continue loop if true
    statement 3: do after every iteration of the loop