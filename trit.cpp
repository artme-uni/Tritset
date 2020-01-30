#include "trit.h"

Trit IntToTrit(int x)
{
    Trit temp;

    switch (x)
    {
        case 0:
            temp = Trit::U;
            break;
        case 1:
            temp = Trit::F;
            break;
        case 2:
            temp = Trit::T;
            break;
        default:
            temp = Trit::U;
            break;
    }

    return temp;
}

int TritToInt(Trit x)
{
    unsigned int temp;
    switch (x)
    {
        case Trit::U:
            temp = 0;
            break;
        case Trit::F:
            temp = 1;
            break;
        case Trit::T:
            temp = 2;
            break;
    }

    return temp;
}

Trit operator&(const Trit &a, const Trit &b)
{
    if ((a == Trit::F) || (b == Trit::F))
    {
        return Trit::F;
    } else if ((a == Trit::U) || (b == Trit::U))
    {
        return Trit::U;
    } else
    {
        return Trit::T;
    }
}

Trit operator|(const Trit &a, const Trit &b)
{
    if ((a == Trit::T) || (b == Trit::T))
    {
        return Trit::T;
    } else if ((a == Trit::U) || (b == Trit::U))
    {
        return Trit::U;
    } else
    {
        return Trit::F;
    }
}

Trit operator!(const Trit &a)
{
    if (a == Trit::T)
    {
        return Trit::F;
    } else if (a == Trit::F)
    {
        return Trit::T;
    }

    return Trit::U;
}

void printTrit(const Trit a, std::ostream &output)
{
    switch (a)
    {
        case Trit::U:
            output << "U ";
            break;
        case Trit::F:
            output << "F ";
            break;
        case Trit::T:
            output << "T ";
            break;
        default:
            output << "U ";
            break;
    }
}