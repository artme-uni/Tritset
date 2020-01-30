#ifndef TRITSET_TRIT_H
#define TRITSET_TRIT_H

#include <iostream>

enum class Trit
{
    F, U, T
};

Trit IntToTrit(int x);

int TritToInt(Trit x);

Trit operator&(const Trit &a, const Trit &b);

Trit operator|(const Trit &a, const Trit &b);

Trit operator!(const Trit &a);

void printTrit(const Trit a, std::ostream &output);

#endif //TRITSET_TRIT_H
