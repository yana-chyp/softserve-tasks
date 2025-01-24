#include "AnyType.h"
#include "AnyType.cpp"
#include <iostream>

int main() {
    AnyType a;
    std::cout<<"a: "<<a<<"\n";

    AnyType b = 1;
    std::cout<<"b: "<<b<<"\n";

    AnyType c = 3.14;
    std::cout<<"c: "<<c<<"\n";

    b = 'b';
    std::cout<<"b: "<<b<<"\n";

    AnyType d = true;
    std::cout<<"d: "<<d<<"\n";

    std::cout<<"swap:\n";
    c.swap(d);
    std::cout<<"c: "<<c<<"\n";
    std::cout<<"d: "<<d<<"\n";

    AnyType e = c;
    std::cout<<"e: "<<e<<"\n";

    std::cout<<"a.getType(): "<<a.getType()<<"\n";
    // std::cout<<"bool(a): "<<bool(a)<<"\n";
    char a_c = a;
    std::cout<<"char(a): "<<a_c<<"\n";

    return 0;
}