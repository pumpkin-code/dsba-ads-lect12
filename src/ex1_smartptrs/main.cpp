/*! \file       main.cpp
 *  \author     Sergey Shershakov
 *  \version    0.2
 *  \date       25.02.2020
 *
 *  Smart pointers.
 */

#include <iostream>
#include <string>
#include <memory>
#include <cassert>

using namespace std;


// bad example
void demo1_1()
{
    string* p = new string("Hello world!");

    // ...

    return;     // memory leakage, because there is no delete p here
}


void demo1_2(int a)
{
    if(a % 2)
        throw std::exception();
}

void demo1_3()
{
    string* p = new string("Hello world!");

    demo1_2(2);         // throws an exception, so delete p unreachable
                        // memory leakage
    delete p;
}

void demo1()
{
    demo1_1();          // bad
    demo1_3();          // still not good

}


void demo2()
{
    {
        std::unique_ptr<string> myPtr(new string("Hello world"));

        cout << *myPtr << ", with size = " << myPtr->size() << "\n";

        // string* sp = myPtr;              // incompatible types

        string* sp = myPtr.get();           // OK
        cout << *sp << "\n";

        // ERROR: Can't copy unique_ptr:
        // std::unique_ptr<string> myOtherPtr = myPtr;
    }
}


void demo3()
{
    string* s1 = new string("Hello");
    string* s2 = new string("world");

    try {
        cout << *s1 << " " << *s2 << "\n";
        demo1_2(2);         // can throw an exception
    }
    catch(...)
    {
        cerr << "Could not handle exception, "
                "but released resources properly\n";
        delete s1;
        delete s2;
        return;
    }

    // if OK simply need to release the resource...
    delete s1;
    delete s2;
}


void demo3enhanced()
{
    std::unique_ptr<string> s1(new string("Hello"));
    std::unique_ptr<string> s2(new string("world"));

    try {
        cout << *s1 << " " << *s2 << "\n";
        demo1_2(2);         // can throw an exception
    }
    catch(...)
    {
        cerr << "Could not handle exception, "
                "but released resources properly\n";
        // resources handled by unique_ptr are released automatically
        return;
    }
    // resources handled by unique_ptr are released automatically
}


void demo4helper(std::unique_ptr<string> s)
{
    cout << *s << "\n";
}

void demo4()
{
    std::unique_ptr<string> s(new string("Hello world"));
    //demo4helper(s);   // ERROR: Can't copy unique_ptr
}

void demo4_1()
{
    std::unique_ptr<string> s1(new string("Hello world"));
    std::unique_ptr<string> s2 = std::make_unique<string>("Hello world");

    // assert(s1 == s2);    // failed, because pointers are not equal
    assert(*s1 == *s2);     // OK, strings are equal
}



void demo5helper(std::shared_ptr<string> s)
{
    cout << *s << "\n";
}

void demo5()
{
    std::shared_ptr<string> s(new string("Hello world"));
    demo5helper(s);   // OK: Can copy shared_ptr!
}



int main()
{
    demo1();
    demo2();
    demo3();
    demo4();
    demo4_1();
    demo5();

    return 0;
}
