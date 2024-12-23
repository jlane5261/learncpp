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

```cpp
    const int dmv = 17;
    int var = 17;
    constexpr double max1 = 1.4*square(dmv);  //OK if square(17) is a constant expression
    constexpr double max2 = 1.4*square(var);  //Error: var is not a constant expression
    const double max3 = 1.4*square(var);      //OK, but evaluated at run time
```
For a function to be usable in a constant expression, it must be defined constexpr.
```cpp
    //REQT: must be rather simple: a return-statement computing a value
    constexpr double square(double x) {return x*x;}
```

==TODO== Watch a video explaining const and constexpr, and it's use cases

### Pointers, Arrays, and Loops

#### Arrays
`[]` - means "array of"
example:
```cpp
    char v[6]
```
this is an array of chars with a length of 6 (v[0]-v[5]) named "v"


#### Pointers

`*` - means "pointer to"
```cpp
    char* p;
```
this is a pointer to a char, name "p"

A Pointer variable can hold the address of an object of the appropriate type:
```cpp
    char* p = &v[3];    //p points to v's fourth element
    char x = *p;        //*p is the object that p points to
```

> ##### From Cherno
>
> Example code on pointers:
> ```cpp
>     char* buffer = new char[8];
>     memset(buffer,0,8);
> ```
> In this code, `buffer` is a pointer that is set to 8 chars that are allocated on the heap.
> 
> `memset` is using the `buffer` pointer to set 8 bytes at `buffer`'s location to `0`.


#### For loops and References

```cpp    
    for (statement 1; statement 2; statement 3) {}
```

All of these statements are technically optional.
* statement 1: do this initially before the loop
* statement 2: continue loop if true
* statement 3: do after every iteration of the loop

The following function is an example for loop that will print each element of `v`
> note: that we don't have to specify an array bound when we initialze the array with a list.

```cpp
    void print()
    {
        int v[] = {0,1,2,3,4,5,6,7,8,9};

        for (auto x : v)
            cout << x << '\n';

        for (auto x : {10,21,32,43,54,65})
            cout << x << '\n';
    }
```

This loop is explicitly copying the values from `v` into the variable `x`.
If we wanted to improve the performance, we could just have x refer to an element.

```cpp
    void increment()
    {
        int v[] = {0,1,2,3,4,5,6,7,8,9};

        for (auto& x : v)
            ++x;
    }
```
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

> ##### From Cherno
> 
> Example code on references:
> 
> ```cpp
>       void Increment(int* value) // taking a pointer as the function input
>       {
>           (*value)++; // dereferencing the pointer so we can increment the value
>       }
>       
>       int main()
>       {
>           int a = 5;
>           Increment(&a); // passes in a reference (memory address) to `a`
>           std::cout << a << '\n';
>       }
> ```
> An easier way to do this is to re-write the input to take a reference instead of a pointer. you would then
> call the function like this:
> ```cpp
>       Increment(a);
> ```

### User Defined Types

C++ Built in types (any type built from fundamental types, the `const` modifier, and declarator operators) are rich, but they are intentionally low level. They directly reflect the capabilities of conventional computer hardware. C++ uses abstraction mechanisms to design and implement their own types.

**User Defined Type** - a type built out of the built-in types using C++'s abstraction mechanisms are called _user-defined types_ (e.g. classes and enumerations)

#### Structures

The first step in building a new type is often to organize the elements it needs into a data structure, a `struct`

```cpp
    struct Vector {
        int sz;         //number of elements
        double* elem;   //pointer to elements
    };
```

This first version of Vecto consists of an `int` and a `double*`. A variable of type `Vector` can be defined like this:

``` cpp
    Vector v;
```

> NOTE: by itself, its not much use because `v`'s elem pointer doesn't point to anything.

Lets make `v` useful by giving it some elements.

```cpp
    void vector_init(Vector& v, int s)
    {
        v.elem = new double[s];     // allocate an array of s doubles
        v.sz = s;
    }
```

`v`'s `elem` member gets a pointer produced by the `new` operator, and `v`'s sz member gets the number of elements. 

The `&` in `Vector&` indicates that we pass v by non-const reference. **PASS BY REFERENCE: THE  INIT FUNCTION CAN MODIFY THE VECTOR PASSED TO IT.**

The `new` operator allocates memory from an area called _the free store_ AKA _dynamic memory_ AAKA _heap_

Lets create a simple use case for `Vector`:

```cpp
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
```

This is starting to come together but there is still a long way to go before this `Vector` is as elegant and flexible as the standard-library `vector`

Lets continue to gradually improve `Vector` as an example of language features and techniques.

> **PRO TIP**: don't reinvent standard-library components, such as `vector` and `string`, **use them!!**

from the above `read_and_sum` function, use `.` (dot) to access `struct` members through a name (and through a reference) and use `->` to access struct members through a pointer. For example:

```cpp
    void f(Vector v, Vector& rv, Vector* pv)
    {
        int i1 = v.sz;      // access through name
        int i2 = rv.sz;     // access through reference
        int i4 = pv->sz;    // access through pointer
    }
```

#### Classes

A tight connection between the representation of data and the operations on that data is needed for a user-defined type to have all the properties expected of a "real type". We have to distinguish between the interface to a type (to be used by all else), and its implementation (which has access to otherwise inaccessible data). The language mechanism for this is called a `class`.

Classes have members:

1. data members
2. function members
3. type members

The interface to a class is defined by the public members of a class, so that the private members are only accessible through that interface

lets revisit the `Vector` example from the struct section:

```cpp
    class Vector {
        public:
            Vector(int s) : elem{new double[s]}, sz{s} {}   // construct a Vector
            double& operator[](int i) { return elem[i]; }   // element access: subscripting
            int size() const { return sz; }                 // a "const" suffix means "can be applied to const objects"
        private:
            double* elem;   // pointer to the elements
            int sz;         // the number of elements
    };
```

now we can define a variable of our new type with

```cpp
    Vector v(6);    // a Vector with 6 elements
```

Here, the representation of a `Vector` (the members `elem` and `sz`) is accessible only through the interface provided by the public members: `Vector()`, `operator[]()`, and `size()`.

**Constructor** -  a constructor is a function with the smae name as its class. It is used to construct objects of a class. It is always immediately called as soon as an object is created from a class. `Vector(int)` defines how objects of type Vector are constructed. It initializes the `Vector` members using a member initializer list:

```cpp
    : elem{new double[s]}, sz{s}
```

that is, we initialize `elem` with a pointer to `s` elements of type `double` obtained from the free store. Then, we initialize `sz` to `s`

#### Enumerations

C++ supports a simple form of user-defined types for which we can enumerate the values:

```cpp
    enum class Color { red,blue,green };
    enum class Traffic_light { green,yellow,red };

    Color col = Color::red;
    Traffic_light light = Traffic_light::red;
```

**Enumerations** are used to make code more readable. The `class` after the `enum` specifies that an enumeration is strongly typed and that its enumerators are scoped. Being separate types, `enum class`es help prevent accidental misuses of constants. In particular, we cannot mix `Traffic_light` and `Color` values.

```cpp
    Color x = red;                  // error: which red?
    Color y = Traffic_light::red;   // error: that red is not a Color
    Color z = Color::red;           // ok!

similarly, we cannot implicitly mix `Color` and integer values.

    int i = Color::red;     // error: Color::red is not an int
    Color c = 2;            // error:: 2 is not a Color
```

> NOTE: If you don't wnat to explicitly qualify enumerator names and want enumerator values to be `int`s (without the need for an explicit conversion),  you can remove the `class` from `enum class` to get a "plain" `enum`.

 By default, an `enum class` has only assignment, initialization, and comparisons (e.g. `==` and `<`) defined. But because it is a user-defined type, new operators can be defined for it also!

```cpp
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
```

### Modularity

A C++ program consists of many parts: functions, user-defined types, class hierarchies, and templates. The key to managing this is to clearly define the interactions among those parts. The **first** and **most important** step is to distinguish between the interface to a part and its implementation. At the language level, C++ represents interfaces by declarations. A _declaration_ specifies all that's needed to use a function or a type. For Example:

```cpp
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
```

The key point here is that the function definitions are "elsewhere". For example, the `sqrt` definition would look like:

```cpp
    double sqrt(double d)       //definition of sqrt()
    {
        // ... algorithm as found in a math textbook
    }
```

#### Separate Compilation

C++ supports a notion of separate compilation where user code sees only declarations of the types and functions used. The definitions of those types and functions are in separate source files and compiled separately. This is useful for organizing a program into a set of semi-independent cod fragments. Such separation can be used to minimize compilation times and to strictly enforce separation of logically distinct parts of a program. This in turn minimizes the chance for errors. 

A **library** is often a collection of separately compiled code fragments (e.g. functions)

It is typical to place declarations that specify the interface to a module in a file with a name indicating its intended use. For Example:

```cpp
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
```

to access this interface: a user will _include_ the header file for example:

```cpp
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
```

To help ensure consistency the .cpp file providing the implementation of `Vector` will also include the .h file providing its interface:

```cpp
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
```

The code in user.cpp and Vector.cpp shares the Vector interface information presented in Vector.h, but the two files are otherwise independent and can be separately compiled.


#### Namespaces

In addition to functions, classes, and enumerations, C++ offers namespaces as a mechanism for expressing that some declarations belong together and that their names shouldn't clash with other names. For example, I might want to experiment with my own complex number type:

```cpp
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
```

By putting my code into the namespace `My_code`, I make sure that my names do not conflict with the standard-library names in namespace `std`. (the standard library does provide support for `complex` arithmetic.)

#### Error Handling

Error handling is a large and comlex topic with concerns and ramifications that go far beyond language facilities into programming techniques and tools. However C++ provides a few features to help. The major tool is the type system itself. The majority of C++ constructs are dedicated to the design and implementation of elegant and efficient abstractions (e.g., user-defined types and algorithms using them). One effect of this modularity and abstraction (in particular, the use of libraries) is that the point where a run-time error can be detected is separated from the point where it can be handled. **Error Handling** becomes increasingly important as programs grow and especially when libraries are used extensively.

#### Exceptions

Consider the `Vector` example. What should happen when we try to access an element that is out of range for the vector?


The solution is for the Vector implementer to detect the attempted out-of-range access and then tell the user about it!

```cpp
    double& Vector::operator[](int i)
    {
        if (i<0 || size()<=i) throw out_of_range{"Vector::operator[]"};
        return elem[i];
    }
```

The `throw` transfers control to a handler for exceptions of type `out_of_range` in some function that directly or indirectly called `Vector::operator[]()`.

We put code for which we are interested in handling exceptions into a `try`-block. the `catch`-clause providing a handler for out_of_range will be entrred. The out of range type is defined in the standard library (in `<stdexcept>`) and is in fact used by some standard-library container access functions.

Proper error handling mechanisms can make error handling simpler, more systematic and more readable!

#### Invariants

Whenever we define a function, we should consider what its preconditions are and if feasible test them. The `[a:b)` notation specifies a half-open range, meaning that `a` is part of the range but `b` is not. `operator[]()` operates on objects of type `Vector` and nothing it does makes any sense unless the members of Vector have "reasonable" values. In particular we did say "`elem` points to an array of `sz` doubles" but it was only stated in a comment.

Such a statementof what is assumed to be true for a class is called an **invariant**

It is the job of a constructor to establish the invariant for its class (so that the member functions can rely on it) and for the member funtions to make sure that the invariant holds when they exit.

Consider this:

```cpp
    Vector v(-27);
```

This is likely to cause chaos.
Here is a more appropriate definition:

```cpp
    Vector::Vector(int s)
    {
        if (s<0) throw length_error{"Vector constructor size"};
        elem = new double[s];
        sz = s;
    }
```

standard library exception`length_error` is used here to report a non-positive number of elements. If operator new can't find memory to allocate it throws a `std::bad_alloc`. We can now write:

```cpp
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
```

The notion of invariants is central to the design of classes and preconditions serve a similar role in the design of functions.

**Invariants**:
- help us to understand precisely what we want
- force us to be specific

The notion of invariants underlies C++'s notions of resource management supported by constructors and destructors.

#### Static Assertions

Exceptions report errors found at run time. If an error can be found at compile time, it is usually preferable to do so. We can perform simple checks on other properties that are known at compile time and report failures as compiler error messages. 

```cpp
    static_assert(4<=sizeof(int), "integers are too small");    // check integer size
```

This will write integers are too small if 4<=sizeof(int), that is, if an int on the system does not have at least 4 bytes.
The `static_assert` mechanism can be used for anything that can be expressed in terms of constant expressions

In general, `static_assert(A,S)` prints `S` as a compiler error message if `A` is not true.

The most important uses of static_asser come when we make assertions about types used sas parameters in generic programming.

## Advice
1. Don't panic! All will become clear in time.
2. You don't have to know every detail of C++ to write good programs.
3. Focus on programming techniques, not on language features; (See Section 2.1)



# CHAPTER 3

## Introduction
This chapter aims to provide an idea of C++'s support for abstraction and resource management (without going into a lot of detail.)


## Classes
The Central Language feature for C++ is the `Class` - a user defined type provided to represent a concept in the code of a program.

Very often, `classes` are what **libraries** offer!

Essentially, All language features beyond the fundamental types, operators, and statements exist to make classes better, more correct, easier to maintian, more efficient, more elegant, easier to use, easier to read, and easier to reason about.

For this chapter, we'll only consider 3 basic types of classes:

1. Concrete Classes
2. Abstract Classes
3. Classes in Class Hierarchies


### Concrete Types

The basic idea of a concrete class is that it behaves "just like built-in types".

a concrete class is a class that can be instantiated, meaning you can create objects from it. Unlike an abstract class, a concrete class has no pure virtual functions, which are functions with `= 0` in their declarations and no implementation. Instead, all member functions in a concrete class are either fully defined or inherited from other fully-defined base classes

#### Arithmetic Types

Arithmetic types are a version of concrete types, the class definition itself contains only the operations requiring access to the representation. Example:

```cpp
    class complex {
        double re, im;
    public:
        complex(double r, double i) : re{r}, im{i} {}   // construct a complex from two scalars
        complex(double r) : re{r}, im{0} {}             // construct complex from one scalar
        complex() : re{0}, im{0} {}                     // default: {0,0}

        double real() const {return re;}                // const indicates that these functions do not modify the object
        void real(double d) {re=d;}
        double imag() const {return im;}
        void imag(double d) {im=d;}

        complex& operator+=(complex z) {re+=z.re; im+=z.im; return *this;}
        complex& operator-=(complex z) {re-=z.re; im-=z.im; return *this;}

        complex& operator*=(complex);                   // defined out-of-class somewhere
        complex& operator/=(complex);                   // defined out-of-class somewhere
    };
```

This is a simplified version of the standard-library `complex`. The class definition itself contains only the operations requiring access to the representation.

many useful operations do not require direct access to the representation of `complex`, so the can be defined separately from the class definition:

```cpp
    complex operator+(complex a, complex b) {return a+=b;}
    complex operator-(complex a, complex b) {return a-=b;}
    complex operator-(complex a) { return {-a.real(), -a.imag()}; }     //unary minus
    ...
    ...
```

Its important to note here that an argument passed by value is copied, so that the argument can be modified, instead of the caller's copy, thus being able to use the result as the return value.

The definitions of == and != are straightforward.

```cpp
    bool operator==(complex a, complex b)       //equal
    {
        return a.real()==b.real() && a.imag()==b.imag();
    }

    bool operator!=(complex a, complex b)       // not equal
    {
        return !(a==b);
    }

    // ...
```

Class `complex` can be used like this:

```cpp
    void f(complex z)
    {
        complex a {2.3};        //construct complex a
        complex b {1/a};
        complex c {a+z*complex{1,2.3}};
        // ...

        if (c!=b)
            c = -(b/a)+2*b;
    }
```

The compiler converts operators involving complex numbers into appropriate function calls. For example, `c!=b` means `operator!=(c,b)`, and `1/a` means `operator/(complex{1},a)`.

NOTE: you cannot change operator syntax for built-in types, i.e. redefining `+` to subtract `int`s.

#### A Container

A _container_ is an object holding a colletion of elements, for example: a `Vector` is a container.

Lets take it back to the example `Vector` Class from Chapter 2. There is one fatal flaw in its design: using `new` to allocate memory for its elements, but it never deallocates! This is not a good idea because although C++ defines an interface for a garbage collector, it is not guaranteed that one is available to make unused memory available for new objects. In some environments you can't use a collector, and sometimes you prefer more precise control of destruction for logical or performance reasons. Therefore, we need a mechanism to ensure that the memory allocated by the constructor is deallocated.

That mechanism is called a `destructor`:

```cpp
    class Vector {
        private:
            double* elem;       // elem points to an array of sz doubles
            int sz;
        public:
            Vector(int s) : elem{new double[s]}, sz{s}      // constructor: acquire resources
            {
                for (int i=0; i!=s; ++i) elem[i]=0;         // initialize elements
            }

            ~Vector() { delete[] elem; }                    // destructor: release resources

            double& operator[](int i);
            int size() const;
    };
```

The name of a destructor is the complement operator, `~`, followed by the name of the class; it is the complement of a constructor. `Vector`'s constructor allocates some memory on the free store (also called the _heap_) using the `new` operator. The destructor cleans up by freeing that memory using the `delete` operator. This is all done without intervention by users of `Vector`. The users simply create and use `Vectors` much as they would variables of built-in types.

For Example:

```cpp
    void fct(int i)
    {
        Vector v(n);

        // ...use v...

        {
            Vector v2(2*n);
            // ... use v and v2 ...
        } // v2 is destroyed here

        // ... use v ...

    } // v is destroyed here
```

`Vector` obeys the same rules for naming, scope, allocation, lifetime, etc. as does a built-in type, such as `int` and `char`.

For details on how to control the lifetime of an object, see Chapter 6 section 4.2.

The constructor/destructor combination is the basis of many elegant techniques. In particular, it is the basis for most C++ general resource management techniques.

RAII - (_Resource Acquisition Is Initialization_) allows us to eliminate the allocations in general code and keep them buried inside the implementation of well-behaved abstractions. 

#### Initializing Containers

A container exists to hold elements, so we need convenient ways of getting elements into a container. We can handle that by creating a `Vector`  with an appropriate number of elements and then assigning to them, but typically other ways are more elegant.

Here are two of the Author's favorites:

 - _Initializer-list constructor_: Initialize with a list of elements.
 - `push_back()`: Add a new element at the end (at the back of) the sequence.

These can be declared, like this:

```cpp
    class Vector {
    public:
        Vector(std::initializer_list<double>);      // initialize with a list
        // ...
        void push_back(double);                     // add element at end increasing the size by one
        // ...
    };
```

The `push_back()` is useful for input of arbitrary numbers of elements. For example:

```cpp
    Vector read(istream& is)
    {
        Vector v;
        for (double d; is>>d; )          // read floating-point values into d
            v.push_back(d);             // add d to v
        return v;
    }
```

The input loop is terminated by an end-of-file or a formatting error. Until that happens, each number read is added to the `Vector` so that at the end, `v`'s size is the number of elements read.

`push_back()`'s implementation is later discussed in Chapter 13 Section 6.4.3

See Chapter 3 Section 3.2 for handling a potentially large amount of data.

The `std::initializer_list` used to define the initializer-list constructor is a standard-library type known to the compiler: when we use a `{}`-list, such as `{1,2,3,4}`, the compiler will create an object of type `initializer_list` to give to the program.

We can then write:

```cpp
    Vector v1 = {1,2,3,4,5};        // v1 has 5 elements
    Vector v2 = {1.23,3.45,6.7,8};  // v2 has 4 elements
```

`Vector`'s initializer-list constructor might be defined like this:

```cpp
    Vector::Vector(std::initializer_list<double> lst)   // initialize with a list
        :elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())}
    {
        copy(lst.begin(),lst.end(),elem);               // copy from lst into elem
    }
```

TODO: comment here on how this constructor works!!!

### Abstract Types

Types such as `complex` and `Vector` are called concrete types because their representation is part of their definition. In that they resemble built-in types. 

an **Abstract Type** is a type that completely insulates a user from implementation details. To do that, we decouple the interface from the representation, and give up genuine local variables. Since we don't know anything about the representation of an abstract type (not even its size), we must allocate objects on the free store and access them through references or pointers.

First define the interface of a class `Continer` which we will design as a more abstract version of our `Vector`:

```cpp
    class Container{
    public:
        virtual double& operator[](int) = 0;        // pure virtual function
        virtual int size() const = 0;               // const member function
        virtual ~Container() {}
    };
```

This class is a pure interface to specific containers defined later. The word `virtual` means "may be redefined later in a class derived from this one". The `=0` syntax says the function is _pure virtual_ meaning that a class derived from Container _must_ define the function.

> this is called a **virtual function**!

> A class with a pure virtual function is called an **Abstract Class**

> A class that provides an interface to a variety of other classes is often called a **Polymorphic type**

As is common for **Abstract Classes**, `Container` does not have a constructor! It does have a destructor however, and that destructor is in fact `virtual`. Again, this is common for Abstract Classes because they tend to be __manipulated through references or pointers__! Someone who destroys a `Container` through a pointer has no idea what resources are owned by its implementation.

Use a concrete class (such as `Vector`) to implement the functions required by the interface:

```cpp
    class Vector_container : public Container {
        Vector v;
    public:
        Vector_container(int s) : v(s) {}
        ~Vector_container() {}

        double& operator[](int i) {return v[i];}
        int size() const {return v.size();}
    };
```

The class `Vector_container` is _derived_ from class `Container`, the _base_ of `Vector_container`. Alternatively, the subclass(Vector_container) and superclass(Container).

since the derived class inherits members from its base class, it is commonly reffered to as _inheritance_.

consider this function:
```cpp
    void use(Container& c)
    {
        const int sz = c.size();

        for (int i=0; i!=sz; ++i)
            std::cout << c[i] << '\n';
    }
```

For a function like this to use a `Container` in complete ignorance of implementation details, some other function will have to make an object on which it can operate. For example:
```cpp
    void g()
    {
        Vector_container vc(10);    // 10 elements
        use(vc);
    }
```

since `use()` doesn't know about `Vector_containers`, only `Containers`,  it will work just as well for a different implementation of a `Container` such as a `List_container`!

> The main point here is that `use(Container&)` has no idea if its argument is a `Vector_container`, `List_container`, or any other kind of derived `Container`; **It doesn't need to know!**

```cpp
    void h()
    {
        List_container lc = { 1,2,3,4,5,6,7,8,9 };  // List_container has different implementation
        use(lc);
    }
```

Pro: `use()` doesn't need to be recompiled if the implementation of `Vector_container` changes, or a new derived class is created.

Con: objects must be manipulated through pointers or references.


### Virtual Functions

Consider again the use of `Container`:

```cpp
    void use(Container& c)
    {
        const int sz = c.size();

        for (int i=0; i!=sz; ++i)
            std::cout << c[i] << '\n';
    }
```

when `h()` calls `use()`, `List_container`'s operator[] must be used, similarly when `g()` is called, `Vector_container`'s operator[] must be used. A `Container` Object must contain information to allow it to select the right function to call at run time. The usual implementation technique is for the compiler to convert the name of a vertual function into an index into a table of pointers to functions. That table is usually called the _virtual function table_ or simply `vtbl`. Each class with virtual functions has its own vtbl identifying its virtual function. 

The functions in the `vtbl` allow the object to be used correctly even when the size of the object and the layout of its data are unkown to the caller. The implementation of the caller needs only to know the location of the pointer to the `vtbl` in a `Container` and the index used for each virtual function. This virtual call mechanism can be made almost as efficient as the "normal function call" mechanism. Its space overhead is one pointer in each object of a class with virtual functions plus one `vtbl` for each such class.

### Class Hierarchies



## Copy and Move

### Copying Containers

### Moving Containers

### Resource Management

### Suppressing Operations



## Templates

### Parameterized Types

### Function Templates

### Function Objects



## Advice


