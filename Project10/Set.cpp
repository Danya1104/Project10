#include "Set.h"
#include <iostream>
#include <stdexcept>
Set::Set(const int mp) : BitField(mp) {
    MaxPower = mp;
}
Set::Set(const Set& s) : BitField(s.BitField) {
    MaxPower = s.MaxPower;
}
Set::Set(const Bitefield& bf) : BitField(bf) {
    MaxPower = bf.GetLength();
}
Set::operator Bitefield() {
    Bitefield tmp(BitField);
    return tmp;
}
int Set::GetMaxPower() const {
    return MaxPower;
}
int Set::IsMember(const int Elem) const {
    if (Elem >= 0 && Elem <= MaxPower) {
        return BitField.GetBit(Elem);
    }
    throw std::out_of_range("No correct Elem");
}
void Set::InsElem(const int Elem) {
    if (Elem >= 0 && Elem <= MaxPower) {
        BitField.SetBit(Elem);
    }
    else {
        throw std::out_of_range("No correct Elem");
    }
}
void Set::DelElem(const int Elem) {
    if (Elem >= 0 && Elem <= MaxPower) {
        BitField.ClrBit(Elem);
    }
    else {
        throw std::out_of_range("No correct Elem");
    }
}
Set& Set::operator=(const Set& s) {
    BitField = s.BitField;
    MaxPower = s.MaxPower;
    return *this;
}
int Set::operator==(const Set& s) const {
    return BitField == s.BitField;
}
int Set::operator!=(const Set& s) const {
    return BitField != s.BitField;
}
Set Set::operator+(const Set& s) {
    Set tmp(BitField | s.BitField);
    return tmp;
}
Set Set::operator+(const int Elem) {
    Set tmp(*this);
    tmp.InsElem(Elem);
    return tmp;
}
Set Set::operator-(const int Elem) {
    Set tmp(*this);
    tmp.DelElem(Elem);
    return tmp;
}
Set Set::operator*(const Set& s) {
    Set tmp(BitField & s.BitField);
    return tmp;
}
Set Set::operator~(void) {
    int ElemCount = 0;

    Set tmp(MaxPower);
    for (int i = 0; i < MaxPower; i++) {
        if (!IsMember(i)) {
            tmp.InsElem(i);
        }
    }
    return tmp;
}
std::istream& operator>>(std::istream& istr, Set& s) {
    int Elem;
    std::cout << "Введите элементы множества через пробел: ";

    while (istr >> Elem) {
        s.InsElem(Elem);

        if (istr.peek() == '\n') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    return istr;
}
std::ostream& operator<<(std::ostream& ostr, const Set& s) {
    ostr << std::endl << "{";
    for (int i = 0; i < s.MaxPower; i++) {
        if (s.IsMember(i)) {
            ostr << i << ", ";
        }
    }
    ostr << "}" << std::endl;
    return ostr;
}
