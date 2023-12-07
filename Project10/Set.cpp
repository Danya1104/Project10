#include "Set.h"
#include <iostream>
#include <stdexcept>

Set::Set(int mp) : BitField(mp), MaxPower(mp) {}

Set::Set(const Set& s) : BitField(s.BitField), MaxPower(s.MaxPower) {}

Set::Set(const Bitefield& bf) : BitField(bf), MaxPower(bf.GetLength()) {}

Set::operator Bitefield() const {
    return static_cast<Bitefield>(BitField);
}

int Set::GetMaxPower() const {
    return MaxPower;
}

//int Set::IsMember(const int Elem) const {
//    if (Elem < 0 || Elem >= MaxPower) throw std::out_of_range("No correct Elem");
//    return BitField.GetBit(Elem);
//}
//
//void Set::InsElem(const int Elem) {
//    if (Elem < 0 || Elem >= MaxPower) throw std::out_of_range("No correct Elem");
//    BitField.SetBit(Elem);
//}
//
//void Set::DelElem(const int Elem) {
//    if (Elem < 0 || Elem >= MaxPower) throw std::out_of_range("No correct Elem");
//    BitField.ClrBit(Elem);
//}
 int Set::IsMember(const int Elem) const {
if (Elem >= 0 && Elem < MaxPower) {
    return BitField.GetBit(Elem);
}
throw std::out_of_range("No correct Elem");
}

void Set::InsElem(const int Elem) {
    if (Elem >= 0 && Elem < MaxPower) {
        BitField.SetBit(Elem);
    }
    else {
        throw std::out_of_range("No correct Elem");
    }
}

void Set::DelElem(const int Elem) {
    if (Elem >= 0 && Elem < MaxPower) {
        BitField.ClrBit(Elem);
    }
    else {
        throw std::out_of_range("No correct Elem");
    }
}

//int Set::IsMember(const int Elem) const {
//    if (Elem < 0 || Elem >= MaxPower) {
//        std::cerr << "Error: No correct Elem. Elem = " << Elem << std::endl;
//        throw std::out_of_range("No correct Elem");
//    }
//    return BitField.GetBit(Elem);
//}
//
//void Set::InsElem(const int Elem) {
//    BitField.SetBit(Elem);
//}
//
//void Set::DelElem(const int Elem) {
//    BitField.ClrBit(Elem);
//}


Set& Set::operator=(const Set& s) {
    if (this != &s) {
        BitField = s.BitField;
        MaxPower = s.MaxPower;
    }
    return *this;
}

bool Set::operator==(const Set& s) const {
    return BitField == s.BitField && MaxPower == s.MaxPower;
}

bool Set::operator!=(const Set& s) const {
    return !(*this == s);
}

Set Set::operator+(const Set& s) const {
    Set tmp(BitField | s.BitField);
    return tmp;
}

Set Set::operator+(const int Elem) const {
    Set tmp(*this);
    tmp.InsElem(Elem);
    return tmp;
}

Set Set::operator-(const int Elem) const {
    Set tmp(*this);
    tmp.DelElem(Elem);
    return tmp;
}

Set Set::operator*(const Set& s) const {
    Set tmp(BitField & s.BitField);
    return tmp;
}

Set Set::operator~() const {
    Set tmp(~BitField);
    return tmp;
}

//std::istream& operator>>(std::istream& istr, Set& s) {
//    int Elem;
//    for (int i = 0; i < s.MaxPower; i++) {
//        istr >> Elem;
//        if (Elem >= 0 && Elem < s.MaxPower) {
//            s.InsElem(Elem);
//        }
//        else {
//            throw std::out_of_range("No correct Elem");
//        }
//    }
//    return istr;
//}

//std::istream& operator>>(std::istream& istr, Set& s) {
//    int Elem;
//    for (int i = 0; i < s.MaxPower; i++) {
//        istr >> Elem;
//        if (Elem >= 0 && Elem < s.MaxPower) {
//            s.InsElem(Elem);
//        }
//        else {
//            std::cerr << "Error: No correct Elem. Elem = " << Elem << std::endl;
//            throw std::out_of_range("No correct Elem");
//        }
//    }
//    return istr;
//}
//std::istream& operator>>(std::istream& istr, Set& s) {
//    int Elem;
//    std::cout << "¬ведите элементы множества через пробел (размерность " << s.MaxPower << "): ";
//    for (int i = 0; i < s.MaxPower; ++i) {
//        istr >> Elem;
//        if (Elem >= 0) {
//            s.InsElem(Elem);
//        }
//        else {
//            std::cerr << "Error: No correct Elem. Elem = " << Elem << std::endl;
//            throw std::out_of_range("No correct Elem");
//        }
//    }
//    return istr;
//}
//std::istream& operator>>(std::istream& istr, Set& s) {
//    int Elem;
//    std::cout << "¬ведите элементы множества через пробел (размерность " << s.MaxPower << "): ";
//
//    while (istr >> Elem) {
//        s.InsElem(Elem);
//    }
//
//    return istr;
//}
std::istream& operator>>(std::istream& istr, Set& s) {
    int ElemCount = 0;  // ѕеременна€ дл€ подсчета введенных элементов
    int Elem;

    std::cout << "¬ведите элементы множества через пробел (размерность " << s.MaxPower << "): ";

    while (ElemCount < s.MaxPower && istr >> Elem) {
        s.InsElem(Elem);
        ElemCount++;
    }

    return istr;
}


std::ostream& operator<<(std::ostream& ostr, const Set& s) {
    ostr << std::endl << "{";
    for (int i = 0; i < s.MaxPower; i++) {
        if (s.IsMember(i)) {
            ostr << i << ", "; // выводите реальные элементы множества, а не индексы битов
        }
    }

    ostr << "}" << std::endl;
    return ostr;
}