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
> note: that we don't have to specify an array bound when we initialze the array with a list.

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

A tight connection between the representation of data and the operations on that data is needed for a user-defined type to have all the properties expected of a "real type". We have to distinguish between the interface to a type (to be used by all else), and its implementation (which has access to otherwise inaccessible data). The language mechanism for this is called a `class`.

Classes have members:

1. data members
2. function members
3. type members

The interface to a class is defined by the public members of a class, so that the private members are only accessible through that interface

lets revisit the `Vector` example from the struct section:

    class Vector {
        public:
            Vector(int s) : elem{new double[s]}, sz{s} {}   // construct a Vector
            double& operator[](int i) { return elem[i]; }   // element access: subscripting
            int size() const { return sz; }                 // a "const" suffix means "can be applied to const objects"
        private:
            double* elem;   // pointer to the elements
            int sz;         // the number of elements
    };

now we can define a variable of our new type with

    Vector v(6);    // a Vector with 6 elements

Here, the representation of a `Vector` (the members `elem` and `sz`) is accessible only through the interface provided by the public members: `Vector()`, `operator[]()`, and `size()`.

**Constructor** -  a constructor is a function with the smae name as its class. It is used to construct objects of a class. It is always immediately called as soon as an object is created from a class. `Vector(int)` defines how objects of type Vector are constructed. It initializes the `Vector` members using a member initializer list:

    : elem{new double[s]}, sz{s}

that is, we initialize `elem` with a pointer to `s` elements of type `double` obtained from the free store. Then, we initialize `sz` to `s`

#### Enumerations

C++ supportsa simple form of user-defined types for which we can enumerate the values:

    enum class Color { red,blue,green };
    enum class Traffic_light { green,yellow,red };

    Color col = Color::red;
    Traffic_light light = Traffic_light::red;

**Enumerations** are used to make code more readable. The `class` after the `enum` specifies that an enumeration is strongly typed and that its enumerators are scoped. Being separate types, `enum class`es help prevent accidental misuses of constants. In particular, we cannot mix `Traffic_light` and `Color` values.

    Color x = red;                  // error: which red?
    Color y = Traffic_light::red;   // error: that red is not a Color
    Color z = Color::red;           // ok!

similarly, we cannot implicitly mix `Color` and integer values.

    int i = Color::red;     // error: Color::red is not an int
    Color c = 2;            // error:: 2 is not a Color

> NOTE: If you don't wnat to explicitly qualify enumerator names and want enumerator values to be `int`s (without the need for an explicit conversion),  you can remove the `class` from `enum class` to get a "plain" `enum`.

 By default, an `enum class` has only assignment, initialization, and comparisons (e.g. `==` and `<`) defined. But because it is a user-defined type, new operators can be defined for it also!

    Traffic_light& operator++(Traffic_light& t)
        // prefix increment: ++
    {
        switch (t) {
        case Traffic_light::green:  return t=Traffic_light::yellow;
        case Traffic_light::yellow: return t=Traffic_light::red;
        case Traffic_light::red:    return t=Traffic_light::green;
        }
    }

    Traffic_light next = ++light;       // next becomes Traffic_light::green


### Modularity

A C++ program consists of many parts: functions, user-defined types, class hierarchies, and templates. The key to managing this is to clearly define the interactions among those parts. The **first** and **most important** step is to distinguish between the interface to a part and its implementation. At the language level, C++ represents interfaces by declarations. A _declaration_ specifies all that's needed to use a function or a type. For Example:

    double sqrt(double);    // the square root function takes a double and returns a double

    class Vector {
    public:
        Vector(int s);
        double& operator[](int i);
        int size() const;           // a "const" suffix means "can be applied to const objects";
    private:
        double* elem; // elem points to an array of sz doubles
        int sz;
    };

The key point here is that the function definitions are "elsewhere". For example, the `sqrt` definition would look like:

    double sqrt(double d)       //definition of sqrt()
    {
        // ... algorithm as found in a math textbook
    }

#### Separate Compilation

C++ supports a notion of separate compilation where user code sees only declarations of the types and functions used. The definitions of those types and functions are in separate source files and compiled separately. This is useful for organizing a program into a set of semi-independent cod fragments. Such separation can be used to minimize compilation times and to strictly enforce separation of logically distinct parts of a program. This in turn minimizes the chance for errors. 

A **library** is often a collection of separately compiled code fragments (e.g. functions)

It is typical to place declarations that specify the interface to a module in a file with a name indicating its intended use. For Example:

    // Vector.h


    class Vector {
    public:
        Vector(int s);
        double& operator[](int i);
        int size() const;           
    private:
        double* elem;      // elem points to an array of sz doubles
        int sz;
    };

to access this interface: a user will _include_ the header file for example:

    // user.cpp


    #include "Vector.h"     // get the Vector Interface
    #include <cmath>        // get the standard-library math function interface (this includes sqrt())
    using namespace std;    // make std members visible

    double sqrt_sum(Vector& v)
    {
        double sum =0;
        for (int i=0; i!=v.size(); ++i)
            sum+=sqrt(v[i]);                // sum of square roots
        return sum;
    }

To help ensure consistency the .cpp file providing the implementation of `Vector` will also include the .h file providing its interface:

    // Vector.cpp


    #include "Vector.h" // get the inteface

    Vector::Vector(int s)
        :elem{new double[s]}, sz{s}
    {
    }

    double& Vector::operator[](int i)
    {
        return elem[i];
    }

    int Vector::size() const
    {
        return sz;
    }

The code in user.cpp and Vector.cpp shares the Vector interface information presented in Vector.h, but the two files are otherwise independent and can be separately compiled.


#### Namespaces

In addition to functions, classes, and enumerations, C++ offers namespaces as a mechanism for expressing that some declarations belong together and that their names shouldn't clash with other names. For example, I might want to experiment with my own complex number type:

    namespace My_code {
        class complex {/* ... */};
        complex sqrt(complex);
        // ...
        int main();
    }

    int My_code::main()
    {
        complex z{1,2};
        auto z2 = sqrt(z);
        std::cout << '{' << z2.real() << '' << z2.imag() << "}\n";
    }

    int main()
    {
        return My_code::main();
    }

By putting my code into the namespace `My_code`, I make sure that my names do not conflict with the standard-library names in namespace `std`. (the standard library does provide support for `complex` arithmetic.)

#### Error Handling

Error handling is a large and comlex topic with concerns and ramifications that go far beyond language facilities into programming techniques and tools. However C++ provides a few features to help. The major tool is the type system itself. The majority of C++ constructs are dedicated to the design and implementation of elegant and efficient abstractions (e.g., user-defined types and algorithms using them). One effect of this modularity and abstraction (in particular, the use of libraries) is that the point where a run-time error can be detected is separated from the point where it can be handled. **Error Handling** becomes increasingly important as programs grow and especially when libraries are used extensively.

#### Exceptions

Consider the `Vector` example. What should happen when we try to access an element that is out of range for the vector?


The solution is for the Vector implementer to detect the attempted out-of-range access and then tell the user about it!

    double& Vector::operator[](int i)
    {
        if (i<0 || size()<=i) throw out_of_range{"Vector::operator[]"};
        return elem[i];
    }

The `throw` transfers control to a handler for exceptions of type `out_of_range` in some function that directly or indirectly called `Vector::operator[]()`.

We put code for which we are interested in handling exceptions into a `try`-block. the `catch`-clause providing a handler for out_of_range will be entrred. The out of range type is defined in the standard library (in `<stdexcept>`) and is in fact used by some standard-library container access functions.

Proper error handling mechanisms can make error handling simpler, more systematic and more readable!

#### Invariants

Whenever we define a function, we should consider what its preconditions are and if feasible test them. The `[a:b)` notation specifies a half-open range, meaning that `a` is part of the range but `b` is not. `operator[]()` operates on objects of type `Vector` and nothing it does makes any sense unless the members of Vector have "reasonable" values. In particular we did say "`elem` points to an array of `sz` doubles" but it was only stated in a comment.

Such a statementof what is assumed to be true for a class is called an **invariant**

It is the job of a constructor to establish the invariant for its class (so that the member functions can rely on it) and for the member funtions to make sure that the invariant holds when they exit.

Consider this:

    Vector v(-27);

This is likely to cause chaos.
Here is a more appropriate definition:

    Vector::Vector(int s)
    {
        if (s<0) throw length_error{"Vector constructor size"};
        elem = new double[s];
        sz = s;
    }

standard library exception`length_error` is used here to report a non-positive number of elements. If operator new can't find memory to allocate it throws a `std::bad_alloc`. We can now write:

    void test()
    {
        try {
            Vector v(-27);
        }
        catch (std::length_error){
            // handle negative size
        }
        catch (std::bad_alloc){
            // handle memory exhaustion
        }
    }

The notion of invariants is central to the design of classes and preconditions serve a similar role in the design of functions.

**Invariants**:
- help us to understand precisely what we want
- force us to be specific

The notion of invariants underlies C++'s notions of resource management supported by constructors and destructors.

#### Static Assertions

Exceptions report errors found at run time. If an error can be found at compile time, it is usually preferable to do so. We can perform simple checks on other properties that are known at compile time and report failures as compiler error messages. 

    static_assert(4<=sizeof(int), "integers are too small");    // check integer size

This will write integers are too small if 4<=sizeof(int), that is, if an int on the system does not have at least 4 bytes.
The `static_assert` mechanism can be used for anything that can be expressed in terms of constant expressions

In general, `static_assert(A,S)` prints `S` as a compiler error message if `A` is not true.

The most important uses of static_asser come when we make assertions about types used sas parameters in generic programming.

## Advice
1. Don't panic! All will become clear in time.
2. You don't have to know every detail of C++ to write good programs.
3. Focus on programming techniques, not on language features; (See Section 2.1)

# CHAPTER 3