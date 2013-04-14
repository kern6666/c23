#ifndef C23CODECS2_H
#define C23CODECS2_H
#include "c23code.h"

class C23CodecCS2 : public C23Codec
{
public:
    C23CodecCS2();
    virtual std::string encode(const uint64_t num);
    virtual int64_t decode(const std::string &code, int64_t* codeLen = NULL);
    int64_t getErrorPos();
private:
    std::vector<int> getControlSum(const std::string &code,int offset,int ncode);
    void addControlSum(std::string &code);
    int checkControlSum(const std::string &code, int64_t codeLen);
    inline uint8_t nbit(uint64_t num, uint32_t nbit);
    void invertBit(std::string &str, int pos);
private:
    int64_t errorPos;
};

#endif // C23CODECS2_H
