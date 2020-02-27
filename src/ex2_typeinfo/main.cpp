/*! \file       main.cpp
 *  \author     Sergey Shershakov
 *  \version    0.2
 *  \date       25.02.2020
 *
 *  Type Identification.
 */

#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <functional>

//using namespace std;      // WARN: don't use it, otherwise multiple cos's!
using std::cout;
using std::cin;
using std::string;

struct Foo {
    int x;
    double y;
};

// type_info and typeid
void demo1()
{
    // std::type_info intTI = typeid(int);  // can't create a copy,
                                            // only one copy is allowed
    const std::type_info& intTI = typeid(int);
    cout << "Int type name is " << intTI.name() << "\n";

    const std::type_info& n42TI = typeid(42);
    cout << "42's type name is " << n42TI.name() << "\n";


    const std::type_info& dblTI = typeid(double);
    cout << "Double type name is " << dblTI.name() << "\n";

    const std::type_info& fooTI = typeid(Foo);
    cout << "Foo custom struct's type name is " << fooTI.name() << "\n";
}

class Base {
    virtual void foo() {}
};

class Derived : public Base {
    virtual void foo() override {}
};

void demo2()
{
    // RTTI
    Base b;
    Derived d;

    cout << "Base: " << typeid(b).name() <<
            ", Derived: " << typeid(d).name();
    assert(typeid(b) != typeid(d));

    cout << "\n";

    Base* b1 = &b;
    Base* b2 = &d;
    cout << "Ptr 2 Base: " << typeid(b1).name() <<
            ", Ptr to Derived: " << typeid(b2).name();
    cout << "\n";


    cout << "Deref ptr 2 Base: " << typeid(*b1).name()
         << ", Deref ptr to Derived: " << typeid(*b2).name();
    cout << "\n";
}

// decltype
void demo3()
{
    Foo foo { 42, 3.14 };
    int i = foo.x;
    int y = foo.y;

    decltype(foo.x) a = 15;     // a is integer
    cout << "Type of a is " << typeid(a).name() << "\n";


    Foo* pFoo = &foo;
    decltype(pFoo->y) b = 2.4;     // b is double
    cout << "Type of b is " << typeid(b).name() << "\n";
}

// function pointers (for upcoming contest)
void demo4()
{
    typedef double (*FPTR)(double);     // FPTR is a type for pointers to functions
                                        // like double sin(double)

    cout << "Input trig function: cos or sin: ";
    string funType;
    cin >> funType;

    FPTR trigFun = nullptr;
    if(funType == "sin")
        trigFun = sin;          // cmath cos, the same as mathFun = &sin
    else
        trigFun = cos;          // cmath cos, the same as mathFun = &cos

    cout << "Input argument: ";
    double arg;
    cin >> arg;
    cout << "Fun(" << arg << ") = " << trigFun(arg);

    cout << "\n\n";
}

// decltype for functions
void demo5()
{
    // Creating a type alias by using compile-time knowledlge about object cos
    // (event it is a function).
    using F = decltype(cos);
    decltype(cos) typeDef;          // obj is type definition for double fun(double)
    // F o = cos;                   // not possible, not a func pointer
    // typeDef o = cos;             // not possible, not a func pointer

    std::function<F> fn = cos;
    double res1 = fn(0);

    fn = sin;
    double res2 = fn(0);
}



int main()
{
    demo1();
    demo2();
    demo3();
    demo4();
    demo5();

    return 0;
}
