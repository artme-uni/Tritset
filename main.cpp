#include "tritset.h"

int main()
{
    const Tritset a{Trit::U, Trit::U, Trit::U, Trit::T, Trit::T, Trit::T, Trit::F, Trit::F, Trit::F};
    const Tritset b{Trit::U, Trit::T, Trit::F, Trit::U, Trit::T, Trit::F, Trit::U, Trit::T, Trit::F};
    const Tritset aandb{Trit::U, Trit::U, Trit::F, Trit::U, Trit::T, Trit::F, Trit::F, Trit::F, Trit::F};

    Tritset a1 = a;
    a1 &= b;

    a1.print();
    aandb.print();

    //CHECK(a1 == aandb);
}