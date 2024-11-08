# CHAPTER 1
When Learning C++, 
focus on fundamental concepts like
- Type Safety - compile time checks to ensure variable types are used correctly
- Resource management - ability to manage memory, files, network connections
- Invariants - help maintain a class's consistent internal state

focus on programming techniques like
    - resource management using scoped objects
    - the use of iterators in algorithms


## ADVICE: Each chapter contains an "Advice"  section
This is a set of concrete recommendations related to the chapter contents. (Rough rules of thumb, not immutable laws)
- Low-level code isn't necessarily efficient; don't avoid classes, templates, and STL components out of fear of prfm issues
- Except for `new`,`delete`,`typeid`,`dynamic_cast`,`throw` operators, and the `try`-block, individual C++ expressions and statements need no run-time support. (Essential for embedded and high-performance apps)
- 1.2.1 and 1.2.2 are wealthy chunks of text
- if data has an invariant, encapsulate it
- "A constructor creates the execution environment for the member functions and the destructor reverses that."
    - This is the ROOT for C++'s strategies for resource management (causing a demand for exceptions)



# CHAPTER 2

### The Basics

The ISO C++ standard defines two kinds of entities:
 1. Core Launguage Features: such as built in types (char, int, etc.) and loops (for-loops and while-statements)
 2. STL components: such as containers (vector and map) and I/O operations (`<<` and `getline()`)


> fun fact - the `<<` operator is called "put to" and it will write it's second argument onto its first argument. The `>>` operator is called "get from" and is used for input

Some definitions:
 1. A **type** defines a set of possible values and a set of operations (for an object)
 2. An **object** is some memory that holds a value of some type
 3. A **value** is a set of bits interpreted according to a type
 4. A **variable** is a named object


Some more definitions, these are all types of __Statements__:
 1. A **declaration** introduces a name into the program, specifying its type and other characteristics.
    * It tells the compiler about the existence of an entity
 2. A **definition** provides complete implementation or allocation of memory for the entity
 3. An **expression** is a combination of operators, literals, and variables that evaluates to a value
 4. A **selection** is a control of the flow of logic based on conditions (if, else, switch)
 5. An **iteration** repeats a block of code multiple times (for, while, do-while)
 6. A **jump** transfers control to another part of the program (break, continue, return, goto)
 7. A **compound statement** groups multiple statements into a single unit and Enclosed within curly braces {}.
 8. A **Try-catch** is used for exception handling, catches any exceptions that occur

the *auto* type is to be used when there is not a specific reason to mention the type explicitly

### Constants
*const* - meaning roughly "I promise not to change this value"
*constexpr* - meaning roughly "to be evaluated at compile time" <- this is mainly used for performance

The big difference here is when evaluation happens.

For example:


    const int dmv = 17;
    int var = 17;
    constexpr double max1 = 1.4*square(dmv);  //OK if square(17) is a constant expression
    constexpr double max2 = 1.4*square(var);  //Error: var is not a constant expression
    const double max3 = 1.4*square(var);      //OK, but evaluated at run time

For a function to be usable in a constant expression, it must be defined constexpr.

    //REQT: must be rather simple: a return-statement computing a value
    constexpr double square(double x) {return x*x;}

==TODO== Watch a video explaining const and constexpr, and it's use cases

### Pointers, Arrays, and Loops

#### Arrays
[] - means "array of"
example:

    char v[6]

this is an array of chars with a length of 6 (v[0]-v[5]) named "v"


#### Pointers

`*` - means "pointer to"
    
    char* p;

this is a pointer to a char, name "p"

A Pointer variable can hold the address of an obhject of the appropriate type:
    char* p = &v[3];    //p points to v's fourth element
    char x = *p;        //*p is the object that p points to


#### For loops and References
    
    for (statement 1; statement 2; statement 3) {}

* statement 1: do this initially before the loop
* statement 2: continue loop if true
* statement 3: do after every iteration of the loop

The following function is an example for loop that will print each element of `v`
> note: that we don't have to speciy an array bound when we initialze the array with a list.

    void print()
    {
        int v[] = {0,1,2,3,4,5,6,7,8,9};

        for (auto x : v)
            cout << x << '\n';

        for (auto x : {10,21,32,43,54,65})
            cout << x << '\n';
    }

This loop is explicitly copying the values from `v` into the variable `x`.
If we wanted to improve the performance, we could just have x refer to an element.

    void increment()
    {
        int v[] = {0,1,2,3,4,5,6,7,8,9};

        for (auto& x : v)
            ++x;
    }

#### pointers and references

| Symbol | Where? | Description | Example |
| ----------- | ----------- | ----------- | ----------- |
| & | Prefix, expression  | "Address of" | `char* p = &v[3];` where `v` is a vector of [n] chars |
| & | Suffix, declaration | "Reference to" | `for(auto& x : v)` where `v` is a vector of [n] chars |
| * | Prefix, expression | "Contents of" | `char* p = &v[3];` |

**When used in a Declaration**, operators such as `&`,`*`, and `[]` are called **declarator operators**

A reference is similar to a pointer, except that you don't need to use a prefix `*` to access the value referred to be the reference.

> NOTE: a reference cannot be made to refer to a different object after its initialization

its important to ensure that a **pointer** always points to an object, so that dereferencing it is valid.
When we don't have an object to point to, or if we need to represent the notion of "no object available" (_e.g._ for an end of a list), we give the pointer the value `nullptr` ("the null pointer")

### User Defined Types

C++ Built in types (any type built from fundamental types, the `const` modifier, and declarator operators) are rich, but they are intentionally low level. They directly reflect the capabilities of conventional computer hardware. C++ uses abstraction mechanisms to design and implement their own types.

**User Defined Type** - a type built out of the built-in types using C++'s abstraction mechanisms are called _user-defined types_ (e.g. classes and enumerations)

#### Structures

The first step in building a new type is often to organize the elements it needs into a data structure, a `struct`

    struct Vector {
        int sz;         //number of elements
        double* elem;   //pointer to elements
    };

This first version of Vecto consists of an `int` and a `double*`. A variable of type `Vector` can be defined like this:

    Vector v;

>NOTE: by itself, its not much use because v's elem pointer doesn't point to anything.

Lets make `v` useful by giving it some elements.

    void vector_init(Vector& v, int s)
    {
        v.elem = new double[s];     // allocate an array of s doubles
        v.sz = s;
    }

`v`'s `elem` member gets a pointer produced by the `new` operator, and `v`'s sz member gets the number of elements. 

The `&` in `Vector&` indicates that we pass v by non-const reference. **PASS BY REFERENCE: THE  INIT FUNCTION CAN MODIFY THE VECTOR PASSED TO IT.**

The `new` operator allocates memory from an area called _the free store_ AKA _dynamic memory_ AAKA _heap_

Lets create a simple use case for `Vector`:

    double read_and_sum(int s)
        // read s integers from cin and return their sum; s is assumed to be positive
    {
        Vector v;
        vector_init(v,s);           // allocate s elements for v
        for (int i=0; i!=s; ++i)
            std::cin >> v.elem[i];   // read into elements

        double sum = 0;
        for (int i=0; i!=s; ++i)
            sum+=v.elem[i];         // take the sum of the elements
        return sum;
    }

This is starting to come together but there is still a long way to go before this `Vector` is as elegant and flexible as the standard-library `vector`

Lets continue to gradually improve `Vector` as an example of language features and techniques.

>**PRO TIP**: don't reinvent standard-library components, such as `vector` and `string`, **use them!!**

from the above `read_and_sum` function, use `.` (dot) to access `struct` members through a name (and through a reference) and use `->` to access struct members through a pointer. For example:

    void f(Vector v, Vector& rv, Vector* pv)
    {
        int i1 = v.sz;      // access through name
        int i2 = rv.sz;     // access through reference
        int i4 = pv->sz;    // access through pointer
    }

#### Classes

