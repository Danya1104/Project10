#include "Bitefield.h"

class Set {
private:
    Bitefield BitField;
    int MaxPower;

public:
    Set(const int mp);
    Set(const Set& s);
    Set(const Bitefield& bf);
    operator Bitefield();

    int GetMaxPower() const;
    int IsMember(const int Elem) const;
    void InsElem(const int Elem);
    void DelElem(const int Elem);

    Set& operator=(const Set& s);
    int operator==(const Set& s) const;
    int operator!=(const Set& s) const;

    Set operator+(const Set& s);
    Set operator+(const int Elem);
    Set operator-(const int Elem);
    Set operator*(const Set& s);
    Set operator~(void);

    friend std::istream& operator>>(std::istream& istr, Set& s);
    friend std::ostream& operator<<(std::ostream& ostr, const Set& s);
};
