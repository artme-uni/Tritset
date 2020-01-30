#include "tritset.h"

void
Tritset::push(int position, Trit val)
{
    if ((val == Trit::T) || (val == Trit::F))
    {
        int value = TritToInt(val);

        if (capacity == 0)
        {
            set = (unsigned int *) calloc(1, sizeof(unsigned int));
            capacity = TritInUInt;
            set[0] = 0;
        }

        if (capacity < position)
        {
            set = (unsigned int *) realloc(set, (position / TritInUInt + 1) * sizeof(unsigned int));
            int last = capacity;
            capacity = (position / TritInUInt + 1) * TritInUInt;
            for (int i = last / TritInUInt; i < capacity / TritInUInt; i++)
            {
                set[i] = 0;
            }
        }

        unsigned int temp = set[int(position / TritInUInt)];
        int shift = (TritInUInt - (position % TritInUInt) - 1) * 2;
        int mask = value << shift;
        int result = (temp & ~(3u << shift)) | mask;
        set[int(position / TritInUInt)] = result;
    }
}

int
Tritset::get_capacity() const
{
    return capacity;
}

int
Tritset::length() const
{
    if (capacity != 0)
    {
        for (int i = capacity - 1; i != 0; i--)
        {
            if (get(i) != Trit::U)
                return i + 1;
        }
    } else
    {
        return 0;
    }

    return 0;
}

void
Tritset::trim(int last_index)
{
    if (capacity > last_index)
    {
        for (int i = last_index; i < (last_index / TritInUInt + 1) * TritInUInt; i++)
            delete_trit(i);

        if (capacity == 0)
            free(set);
        else
        {
            set = (unsigned int *) realloc(set, last_index / TritInUInt + 1);
            capacity = (last_index / TritInUInt + 1) * TritInUInt;
        }
    }
}

int
Tritset::bigger_capacity(const Tritset &object) const
{
    int cap;

    if (capacity > object.capacity)
    {
        cap = capacity;
    } else
    {
        cap = object.capacity;
    }

    return cap;
}

Trit
Tritset::get(int position) const
{
    if (position >= capacity)
    {
        return Trit::U;
    } else
    {
        unsigned int temp = set[position / TritInUInt];
        int shift = (TritInUInt - (position % TritInUInt) - 1) * 2;
        int result = (temp >> shift) & 3;

        return IntToTrit(result);
    }
}

void
Tritset::print(int index, std::ostream &output) const
{
    printTrit(this->get(index), output);
}

void
Tritset::print() const
{
    print(std::cout);
}

void
Tritset::print(std::ostream &output) const
{
    int length = this->length();
    if (length)
    {
        for (int i = 0; i <= length - 1; i++)
        {
            print(i, output);

            if (i == length - 1)
            {
                output << std::endl;
            }
        }
    } else
    {
        output << "Tritset is empty" << std::endl;
    }
}

Trit
Tritset::operator[](int x) const
{
    return this->get(x);
}

TritsetProxy
Tritset::operator[](int x)
{
    return TritsetProxy(this, x);
}

Tritset &
Tritset::operator=(const Tritset &object)
{
    if (this == &object)
    {
        return *this;
    }

    set = (unsigned int *) realloc(set, (size_t) object.capacity * 2);
    capacity = object.capacity;

    for (int i = 0; i < object.capacity / TritInUInt; i++)
    {
        set[i] = object.set[i];
    }

    return *this;
}

Tritset
Tritset::operator&(const Tritset &object) const
{
    int cap = object.bigger_capacity(*this);

    Tritset temp;

    for (int i = 0; i < cap; i++)
    {
        temp.push(i, (this->get(i) & object.get(i)));
    }

    return temp;
}

Tritset
Tritset::operator|(const Tritset &object) const
{
    int cap = object.bigger_capacity(*this);

    Tritset temp;

    for (int i = 0; i < cap; i++)
    {
        temp.push(i, (this->get(i) | object.get(i)));
    }

    return temp;
}

Tritset
Tritset::operator!() const
{
    Tritset temp;

    for (int i = 0; i < capacity; i++)
    {
        temp.push(i, !this->get(i));
    }

    return temp;
}

bool
Tritset::operator==(const Tritset &object) const
{
    int cap = object.bigger_capacity(*this);

    for (int i = 0; i < cap; i++)
    {
        if (get(i) != object.get(i))
            return false;
    }

    return true;
}

bool
Tritset::operator!=(const Tritset &object) const
{
    return !(*this == object);
}

Tritset &
Tritset::operator&=(const Tritset &object)
{
    *this = *this & object;

    return *this;
}

Tritset &
Tritset::operator|=(const Tritset &object)
{
    *this = *this | object;

    return *this;
}

Tritset::Tritset(const std::initializer_list<Trit> &list)
        : Tritset(list.size())
{
    for (size_t i = 0; i < list.size(); i++)
    {
        int count = 0;

        for (auto &element : list)
        {
            push(count, element);
            count++;
        }
    }
}

int
Tritset::cardinality(Trit value) const
{
    int count = 0;

    for (int i = 0; i < length(); i++)
    {
        if (get(i) == value)
            count++;
    }

    return count;
}

std::unordered_map<Trit, int>
Tritset::cardinality() const
{
    std::unordered_map<Trit, int> map;

    for (int i = 0; i < length(); i++)
    {
        Trit temp = get(i);
        switch (temp)
        {
            case Trit::U:
                map[Trit::U]++;
                break;
            case Trit::F:
                map[Trit::F]++;
                break;
            case Trit::T:
                map[Trit::T]++;
                break;
            default:
                break;
        }
    }

    return map;
}

Iterator
Tritset::begin()
{
    return Iterator(this, 0);
}

Iterator
Tritset::end()
{
    return Iterator(this, this->length());
}

void
Tritset::shrink()
{
    if (this->length() < capacity)
    {
        for (int i = capacity / TritInUInt - 1; i > (length() / TritInUInt); i--)
            if (set[i] == 0)
            {
                capacity -= TritInUInt;
            } else
                break;
    }

    set = (unsigned int *) realloc(set, capacity * 2);
}

void Tritset::delete_trit(int position)
{
    if (position < length())
    {
        unsigned int temp = set[int(position / TritInUInt)];
        int shift = (TritInUInt - (position % TritInUInt) - 1) * 2;
        int result = temp & ~(3u << shift);
        set[int(position / TritInUInt)] = result;
    }
}
