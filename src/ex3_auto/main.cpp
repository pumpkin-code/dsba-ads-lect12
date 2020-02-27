/*! \file       main.cpp
 *  \author     Sergey Shershakov
 *  \version    0.2
 *  \date       25.02.2020
 *
 *  Automatic Type Deduction with auto.
 */

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <memory>           // make_shared
#include <type_traits>      // is_same

//using namespace std;      // WARN: don't use it, otherwise multiple cos's!
using std::cout;
using std::cin;
using std::string;


double demo1helper()
{
    return 3.14;
}

void demo1()
{
    auto i = 42;                // i has type int
    cout << "Type of i: " << typeid(i).name() << "\n";
    assert(typeid(i) == typeid(int));

    auto d = demo1helper();     // d has type double
    cout << "Type of d: " << typeid(d).name() << "\n";
    assert(typeid(d) == typeid(double));
}

void demo2()
{
    //auto i;                   // ERROR: can’t deduce the type of i
    const auto i = 42;          // can use additional qualifiers

    // int& refI = i;           // ERROR: can't bind a non-const ref
    const int& crefI = i;       // OK
}


void demo3()
{
    std::vector<int> v1 { 10, 12, 20, 25 };

    // binding by value
    for(auto el : v1)
    {
        cout << el << ", ";
        assert(typeid(el) == typeid(int));
    }

    cout << "\n";

    // binding by const reference
    for(const auto& el : v1)
    {
        cout << el << ", ";
        assert(typeid(el) == typeid(const int&));
        // assert(typeid(el) != typeid(int));  // OOPS! what's that?
    }

    // binding by const reference
    for(auto& el : v1)
    {
        el *= 2;
        cout << el << ", ";
                                                    //cout << typeid(el).name();
        assert(typeid(el) == typeid(int&));
        //assert(typeid(el) != typeid(const int&));
        //assert(typeid(el) != typeid(int));  // OOPS! what's that?
    }

    cout << "\n";
}


void demo4()
{
    std::vector<int> v1 { 10, 12, 20, 25 };
    auto it1 = v1.begin();
    for(; it1 != v1.end(); ++it1)
    {
        *it1 += 1;
        cout << *it1 << ", ";
        //cout << typeid(it1).name(); // N9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEE
    }

    cout << "\n";

    const std::vector<int> v2const { 10, 12, 20, 25 };
    auto it2 = v2const.begin();
    for(; it2 != v2const.end(); ++it2)
    {
        // *it2 += 1;
        cout << *it2 << ", ";
        cout << typeid(it2).name(); //
    }

    assert(typeid(it1) != typeid(it2));

    cout << "\n";
}


// below are the examples from https://habr.com/ru/post/206458/

int GLOBAL = 13;
int foo()           { return 42; }
int& foo1()         { return GLOBAL; }
const int foo2()    { return 42; }
const int& foo3()   { return GLOBAL; }

void demo5()
{
    auto ri = foo();            // int
    auto ri1 = foo1();          // int
    auto ri2 = foo2();          // int
    auto ri3 = foo3();          // int

    //auto& ri4 = foo();        // ERROR: can't bind lvalue ref to rvalue
    auto& ri5 = foo1();         // int&
    //auto& ri6 = foo2();       // ERROR: can't bind lvalue ref to const rvalue
    auto& ri7 = foo3();         // const int&

    auto&& ri8 = foo();         // int&&
    auto&& ri9 = foo1();        // int&
    auto&& ri10 = foo2();       // const int&&
    auto&& ri11 = foo3();       // const int&

    int k = 5;
    //decltype(k)&& rk = k;             // ERROR: non-modifable rvalue
    decltype(foo())&& ri12 = foo();     // int&&
    decltype(foo1())&& ri13 = foo1();   // int&

    int i = 3;
    decltype(i) ri14;                   // int
    //decltype((i)) ri15;               // int& MUST be bound
}


template<typename T>
void demo6foo(T t)
{
}


void demo6()
{
    auto lmbd = [](auto i){};   // Lambda — OK since C++14
    // void foo(auto i);        // ERROR: auto can't behave like a function template
    decltype(auto) var = 3 + 4; // Expression — OK since C++14
    auto var1 = {1, 2, 3};      // OK, std::initializer_list<int>


    // According to Scott Meyers:
    // “I have no idea why type deduction for auto and for templates is not
    //  identical. If you know, please tell me!”
    // demo6foo({1, 2, 3});     // auto behaves differently with std::initializer_list
}



template<typename T>
void demo7foo(T t)
{
    // ...
}


void demo7()
{
    //  o is a type std::initializer_list<int>
    auto o = {1, 2, 3};
    demo7foo(o);                // OK, but why?
    //demo7foo({1, 2, 3});        // ERROR: (nobody knows why)
}



struct MyStruct {
    MyStruct(int i) : i(i) {}
    int i;
};

void demo8()
{
    auto sp = std::make_shared<MyStruct>(12);

    constexpr bool res = std::is_same <
            decltype(sp),
            std::shared_ptr<MyStruct> >::value;
    static_assert(res, "types are differ");

    std::cout << sp->i << '\n';
}


int main()
{
    demo1();
    demo2();
    demo3();
    demo4();
    demo5();
    demo6();
    demo7();
    demo8();


    return 0;
}
