/*! \file       main.cpp
 *  \author     Sergey Shershakov
 *  \version    0.2
 *  \date       25.02.2020
 *
 *  STL ALGORITHMS, FUNCTORS, LAMBDAS.
 */

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <set>
#include <cassert>
#include <algorithm>

//using namespace std;      // WARN: don't use it, otherwise multiple cos's!
using std::cout;
using std::cin;
using std::string;



// inserters
void demo1()
{    
    std::vector<int> v1 = { 1, 2, 3, 4, 5 };

    // copy the elements of v1 into v2 by appending them
    std::vector<int> v2;
    std::copy (v1.cbegin(), v1.cend(),          // source
        back_inserter(v2));                     // destination

    // copy the elements of v1 into d1 by inserting them at the front
    // reverses the order of the elements
    std::deque<int> d1;
    std::copy (v1.cbegin(), v2.cend(),          // source
        front_inserter(d1));                    // destination

    // copy elements of coll1 into s1
    // only inserter that works for associative collections
    std::set<int> s1;
    std::copy (v1.cbegin(), v1.cend(),          // source
        inserter(s1, s1.begin()));              // destination
}


void printInt(int el)
{
    std::cout << el << " ";
}

// for_each
void demo2()
{
    std::vector<int> v = { 1, 12, 23, 30, 40, 5 };

    // print all elements
    std::for_each(v.cbegin(), v.cend(), printInt);

    cout << "\n\n";
}


int square(int value)
{
    return value * value;
}

// trasform
void demo3()
{
    std::vector<int> v1 = { 1, 2, 3, 4, 5 };
    std::for_each(v1.cbegin(), v1.cend(), printInt);
    cout << "\n";

    std::vector<int> v2;
    std::transform (v1.cbegin(), v1.cend(),     // source
            std::back_inserter(v2),             // destination
            square);                            // operation
    std::for_each(v2.cbegin(), v2.cend(), printInt);

    cout << "\n\n";
}



class PrintInt {
public:
    void operator() (int el) const
    {
        cout << el << " ";
    }
};

void demo4()
{
    std::vector<int> v = { 1, 12, 23, 30, 40, 5 };

    // print all elements with functor
    PrintInt printer;
    std::for_each(v.cbegin(), v.cend(), printer);
    //std::for_each(v.cbegin(), v.cend(), PrintInt());

    cout << "\n\n";
}

// min lambda
void demo5()
{
    [] {
        std::cout << "Hello world of Lambdas!\n";
    } ();


    auto l = [] {
        std::cout << "Hello world of Lambdas!\n";
    };

    // ...

    l();
}


// trasform with lambda
void demo6()
{
    std::vector<int> v1 = { 1, 2, 3, 4, 5 };
    std::for_each(v1.cbegin(), v1.cend(), printInt);
    cout << "\n";

    std::vector<int> v2;
    std::transform (v1.cbegin(), v1.cend(),     // source
            std::back_inserter(v2),             // destination

            [](int el) {                        // lambda as function object
                return el *  el;
            }
    );
    std::for_each(v2.cbegin(), v2.cend(), printInt);

    cout << "\n\n";
}



int main()
{
    demo1();
    demo2();
    demo3();
    demo4();
    demo5();
    demo6();

    return 0;
}
