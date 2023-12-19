#include <iostream>
#include <stdexcept>

typedef unsigned int TELEM;

class Bitefield {
private:
    TELEM* pMem;
    int BitLen;
    int MemLen;
    int GetMemIndex(const int n) const;
    TELEM GetMemMask(const int n) const;

public:
    Bitefield(int len);
    Bitefield(const Bitefield& bf);
    ~Bitefield();

    int GetLength() const;
    void SetBit(const int n);
    void ClrBit(const int n);
    int GetBit(const int n) const;

    bool operator==(const Bitefield& bf) const;
    bool operator!=(const Bitefield& bf) const;
    Bitefield& operator=(const Bitefield& bf);
    Bitefield operator|(const Bitefield& bf);
    Bitefield operator&(const Bitefield& bf);
    Bitefield operator~(void);

    friend std::istream& operator>>(std::istream& istr, Bitefield& bf);
    friend std::ostream& operator<<(std::ostream& ostr, const Bitefield& bf);
};
