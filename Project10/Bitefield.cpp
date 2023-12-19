#include "Bitefield.h"
#include <stdexcept>
#include <algorithm>
#include <string>
Bitefield::Bitefield(int len) : BitLen(len)
{
    if (len <= 0) throw "len <= 0";
    if (len % (8 * sizeof(TELEM)) == 0) {
        MemLen = len / (8 * sizeof(TELEM));
    }
    else {
        MemLen = len / (8 * sizeof(TELEM)) + 1;
    }
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}
Bitefield::Bitefield(const Bitefield& bf) : BitLen(bf.BitLen), MemLen(bf.MemLen)
{
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}
int Bitefield::GetMemIndex(const int n) const
{
    if (n < 0 || n > BitLen) {
        throw std::out_of_range("No correct index");
    }
    return (n / (8 * sizeof(TELEM)));
}
TELEM Bitefield::GetMemMask(const int n) const
{
    return 1 << (n - sizeof(TELEM) * GetMemIndex(n));
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
    else throw " no correct n";
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
        return (pMem[GetMemIndex(n)] & GetMemMask(n));
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
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}
bool Bitefield::operator==(const Bitefield& bf) const
{
    int flag = 1;
    if (MemLen == bf.MemLen && BitLen == bf.BitLen) {
        for (size_t i = 0; i < MemLen; i++) {
            if (pMem[i] != bf.pMem[i]) flag = 0;
        }
    }
    else {
        flag = 0;
    }
    return flag;
}
bool Bitefield::operator!=(const Bitefield& bf) const
{
    int flag = 1;
    if (MemLen == bf.MemLen && BitLen == bf.BitLen) {
        for (size_t i = 0; i < MemLen; i++) {
            if (pMem[i] != bf.pMem[i]) flag = 0;
        }
    }
    else {
        flag = 0;
    }
    if (flag) return 0;
    else return 1;
}
Bitefield Bitefield::operator|(const Bitefield& bf)
{
    int len = bf.BitLen;
    if (BitLen > len) len = BitLen;
    Bitefield tmp(len);
    for (int i = 0; i < MemLen; i++) tmp.pMem[i] = pMem[i];
    for (int i = 0; i < bf.MemLen; i++) tmp.pMem[i] = tmp.pMem[i] | bf.pMem[i];
    return tmp;
}
Bitefield Bitefield::operator&(const Bitefield& bf)
{
    int len;
    if (BitLen > bf.BitLen) len = BitLen;
    else len = bf.BitLen;
    Bitefield tmp(len);
    int minlen;
    if (bf.BitLen < BitLen) minlen = bf.BitLen;
    else minlen = BitLen;
    for (int i = 0; i < minlen; i++) {
        if (GetBit(i) & bf.GetBit(i)) tmp.SetBit(i);
    }
    return tmp;
}
Bitefield Bitefield::operator~(void)
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
Bitefield::~Bitefield()
{
    delete[] pMem;
    pMem = nullptr;
    BitLen = 0;
}
std::istream& operator>>(std::istream& istr, Bitefield& bf) 
{
    std::string tmp;
    istr >> tmp;
    if (tmp.size() != bf.GetLength()) {
        throw "no correct length";
    }
    else {
        for (int i = 0; i < bf.GetLength(); i++) {
            if (tmp[i] == '0') bf.ClrBit(i);
            if (tmp[i] == '1') bf.SetBit(i);
            else throw "no correct string";
        }
    }
    return istr;
}
std::ostream& operator<<(std::ostream& ostr, const Bitefield& bf) 
{
    for (int i = 0; i < bf.GetLength(); i++) {
        if (bf.GetBit(i) == 1) std::cout << 1;
        else std::cout << 0;
    }
    return ostr;
}
