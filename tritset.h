#ifndef TRITSET_TRITSET_H
#define TRITSET_TRITSET_H

#include "trit.h"

#include <initializer_list>
#include <unordered_map>
#include <iostream>

#define TritInUInt (int)(sizeof(unsigned int)*4)

class TritsetProxy;

class Iterator;

class Tritset
{
private:

    unsigned int *set;
    int capacity;

    void push(int position, Trit val);

    Trit get(int position) const;

    int bigger_capacity(const Tritset &object) const;

    friend class TritsetProxy;

    friend class Iterator;

public:

    Tritset(int cap)
    {
        set = nullptr;
        set = (unsigned int *) malloc((size_t) (cap + TritInUInt - cap % TritInUInt) * 2);
        capacity = cap + TritInUInt - cap % TritInUInt;
        for (int i = 0; i < capacity / TritInUInt; i++)
            set[i] = 0;
    }

    Tritset(const Tritset &set) : Tritset(set.length())
    {
        for (int i = 0; i < set.length(); i++)
        {
            this->push(i, set.get(i));
        }
    }

    Tritset()
    {
        set = nullptr;
        capacity = 0;
    }

    ~Tritset()
    {
        if (capacity != 0)
            free(set);
    }

    Tritset(const std::initializer_list<Trit> &list);

    int get_capacity() const;

    int length() const;

    int cardinality(Trit value) const;

    std::unordered_map<Trit, int> cardinality() const;

    void trim(int last_index);

    void print(int index, std::ostream &output) const;

    void print() const;

    void print(std::ostream &output) const;

    Trit operator[](int x) const;

    TritsetProxy operator[](int x);

    Tritset operator&(const Tritset &object) const;

    Tritset &operator&=(const Tritset &object);

    Tritset operator|(const Tritset &object) const;

    Tritset &operator|=(const Tritset &object);

    Tritset &operator=(const Tritset &object);

    Tritset operator!() const;

    bool operator==(const Tritset &t) const;

    bool operator!=(const Tritset &t) const;

    Iterator begin();

    Iterator end();

    void shrink();

    void delete_trit(int position);
};

class TritsetProxy
{
private:
    int index;
    Tritset *set;

public:
    TritsetProxy(Tritset *set, int index) : set(set), index(index)
    {
    };

    TritsetProxy &operator=(TritsetProxy T)
    {
        set->push(index, (Trit) T);
        return *this;
    }

    TritsetProxy &operator=(Trit T)
    {
        set->push(index, T);
        return *this;
    }

    operator Trit() const
    {
        return set->get(index);
    }
};

class Iterator
{
private:
    int cur;
    Tritset *set;
public:

    Iterator(Tritset *set, int cur) : set(set), cur(cur)
    {
    };

    Iterator()
    {
        cur = 0;
    }

    int operator+(int n)
    {
        return cur + n;
    }

    int operator-(int n)
    {
        return cur - n;
    }

    int operator++(int)
    {
        return cur++;
    }

    int operator++()
    {
        return cur++;
    }

    int operator--()
    {
        return cur--;
    }

    int operator--(int)
    {
        return cur--;
    }

    bool operator!=(const Iterator &it)
    {
        return cur != it.cur;
    }

    bool operator==(const Iterator &it)
    {
        return cur == it.cur;
    }

    Trit operator*()
    {
        return set->get(cur);
    }

    void operator=(Trit T)
    {
        set->push(cur, T);
    }
};

#endif //TRITSET_TRITSET_H
