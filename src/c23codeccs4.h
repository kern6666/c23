#ifndef C23CODECCS3_H
#define C23CODECCS3_H
#include "c23codeccs.h"

class C23CodecCS4 : public C23Codec
{
public:
    C23CodecCS4();
    virtual std::string encode(const uint64_t num);
    virtual int64_t decode(const std::string &code, int64_t* codeLen = NULL);
private:
    std::vector<int> getControlSum(const std::string &code,int offset,int ncode);
    void addControlSum(std::string &code);
    void appendShortCS(std::string &code, int offset, int ncode, char symbol);
    void appendBlockNumCS(std::string &code, int offset, int ncode);
    void appendRepairedCS(std::string &code, const std::string repaired_string);
    std::string generateRepairedCS(std::string &code, int offset, int ncode, char symbol);
    int checkControlSum(const std::string &code, int64_t codeLen);
    inline uint8_t nbit(uint64_t num, uint32_t nbit);
    void invertBit(std::string &str, int pos);
};

#endif // C23CODECCS3_H
