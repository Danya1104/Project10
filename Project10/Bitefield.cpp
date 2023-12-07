#include "Bitefield.h"
#include <stdexcept>
#include <algorithm>

Bitefield::Bitefield(int len) : BitLen(len)
{
    if (len <= 0) {
        throw std::invalid_argument("len <= 0");
    }

    MemLen = (len % (8 * sizeof(TELEM)) == 0) ? len / (8 * sizeof(TELEM)) : len / (8 * sizeof(TELEM)) + 1;
    pMem = new TELEM[MemLen]();
}

Bitefield::Bitefield(const Bitefield& bf) : BitLen(bf.BitLen), MemLen(bf.MemLen)
{
    pMem = new TELEM[MemLen];
    std::copy(bf.pMem, bf.pMem + MemLen, pMem);
}

Bitefield::~Bitefield()
{
    delete[] pMem;
    pMem = nullptr;
    BitLen = 0;
}

int Bitefield::GetMemIndex(const int n) const
{
    if (n < 0 || n >= BitLen) {
        throw std::out_of_range("No correct index");
    }
    return n / (8 * sizeof(TELEM));
}

Bitefield::TELEM Bitefield::GetMemMask(const int n) const
{
    return static_cast<TELEM>(1) << (n % (8 * sizeof(TELEM)));
}

int Bitefield::GetLength() const
{
    return BitLen;
}

void Bitefield::SetBit(const int n)
{
    if (n >= 0 && n < BitLen) {
        pMem[GetMemIndex(n)] |= GetMemMask(n);
    }
    else {
        throw std::out_of_range("No correct n");
    }
}

void Bitefield::ClrBit(const int n)
{
    if (n >= 0 && n < BitLen) {
        pMem[GetMemIndex(n)] &= ~GetMemMask(n);
    }
    else {
        throw std::out_of_range("No correct n");
    }
}

int Bitefield::GetBit(const int n) const
{
    if (n >= 0 && n < BitLen) {
        return (pMem[GetMemIndex(n)] & GetMemMask(n)) ? 1 : 0;
    }
    else {
        throw std::out_of_range("No correct n");
    }
}

Bitefield& Bitefield::operator=(const Bitefield& bf)
{
    if (this != &bf) {
        delete[] pMem;
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        std::copy(bf.pMem, bf.pMem + MemLen, pMem);
    }
    return *this;
}

bool Bitefield::operator==(const Bitefield& bf) const
{
    return BitLen == bf.BitLen && MemLen == bf.MemLen && std::equal(pMem, pMem + MemLen, bf.pMem);
}

bool Bitefield::operator!=(const Bitefield& bf) const
{
    return !(*this == bf);
}

Bitefield Bitefield::operator|(const Bitefield& bf) const
{
    int len = std::max(BitLen, bf.BitLen);
    Bitefield tmp(len);
    std::copy(pMem, pMem + MemLen, tmp.pMem);
    for (int i = 0; i < bf.MemLen; i++) {
        tmp.pMem[i] |= bf.pMem[i];
    }
    return tmp;
}

Bitefield Bitefield::operator&(const Bitefield& bf) const
{
    int len = std::min(BitLen, bf.BitLen);
    Bitefield tmp(len);
    for (int i = 0; i < len; i++) {
        if (GetBit(i) & bf.GetBit(i)) {
            tmp.SetBit(i);
        }
    }
    return tmp;
}

Bitefield Bitefield::operator~() const
{
    Bitefield tmp(BitLen);
    for (int i = 0; i < tmp.BitLen; i++) {
        if (GetBit(i) == 0) {
            tmp.SetBit(i);
        }
        else {
            tmp.ClrBit(i);
        }
    }
    return tmp;
}

std::istream& operator>>(std::istream& istr, Bitefield& bf)
{
    std::string tmp;
    istr >> tmp;
    if (tmp.size() != bf.GetLength()) {
        throw std::invalid_argument("No correct length");
    }
    else {
        for (int i = 0; i < bf.GetLength(); i++) {
            if (tmp[i] == '0') {
                bf.ClrBit(i);
            }
            else if (tmp[i] == '1') {
                bf.SetBit(i);
            }
            else {
                throw std::invalid_argument("No correct string");
            }
        }
    }
    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const Bitefield& bf)
{
    ostr << "{";
    for (int i = 0; i < bf.GetLength(); i++) {
        if (bf.GetBit(i) == 1) {
            ostr << i + 1 << ", ";
        }
    }
    ostr << "}" << std::endl;
    return ostr;
}