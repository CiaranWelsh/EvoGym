//
// Created by Ciaran Welsh on 30/09/2020.
//

#include "NumCpp.hpp"


class A{

public:
    explicit A(unsigned long long seed = 0){
        if (seed == 0 )
            nc::random::seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        else
            nc::random::seed(seed);
    }

    void printRandInt(){
        std::cout << nc::random::uniform<double>(0.0, 1.0);
    }
};

class B : public A {
public:
    using A::A;
    void printRndInt2(){
        std::cout << nc::random::uniform(0.0, 1.0);

    }
};


int main (){
//    A a;
//    a.printRandInt();
    B b;
    b.printRndInt2();
}






















