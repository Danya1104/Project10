#pragma once

#include "Bitefield.h"

class Set {
public:
    Set(int mp);
    Set(const Set& s);
    Set(const Bitefield& bf);
    operator Bitefield() const;

    int GetMaxPower() const;
    int IsMember(int Elem) const;
    void InsElem(int Elem);
    void DelElem(int Elem);

    Set& operator=(const Set& s);
    bool operator==(const Set& s) const;
    bool operator!=(const Set& s) const;

    Set operator+(const Set& s) const;
    Set operator+(int Elem) const;
    Set operator-(int Elem) const;
    Set operator*(const Set& s) const;
    Set operator~() const;

    friend std::istream& operator>>(std::istream& istr, Set& s);
    friend std::ostream& operator<<(std::ostream& ostr, const Set& s);

private:
    Bitefield BitField;
    int MaxPower;
};