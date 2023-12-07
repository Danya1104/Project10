#pragma once

#include <iostream>
#include <stdexcept>

class Bitefield {
public:
    using TELEM = unsigned int;

    Bitefield(int len);
    Bitefield(const Bitefield& bf);
    ~Bitefield();

    int GetMemIndex(const int n) const;
    TELEM GetMemMask(const int n) const;
    int GetLength() const;

    void SetBit(const int n);
    void ClrBit(const int n);
    int GetBit(const int n) const;

    Bitefield& operator=(const Bitefield& bf);
    bool operator==(const Bitefield& bf) const;
    bool operator!=(const Bitefield& bf) const;
    Bitefield operator|(const Bitefield& bf) const;
    Bitefield operator&(const Bitefield& bf) const;
    Bitefield operator~() const;

    friend std::istream& operator>>(std::istream& istr, Bitefield& bf);
    friend std::ostream& operator<<(std::ostream& ostr, const Bitefield& bf);

private:
    TELEM* pMem;
    int BitLen;
    int MemLen;
};
