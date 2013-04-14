#ifndef C23CODECCS3_H
#define C23CODECCS3_H
#include "c23codeccs.h"

class C23CodecCS3 : public C23CodecCS
{
public:
    C23CodecCS3();
    virtual std::string encode(const uint64_t num);
    virtual int64_t decode(const std::string &code, int64_t* codeLen = NULL);
private:
    std::vector<int> getControlSum(const std::string &code,int offset,int ncode);
    void addControlSum(std::string &code);
    int checkControlSum(const std::string &code, int64_t codeLen);
    inline uint8_t nbit(uint64_t num, uint32_t nbit);
    void invertBit(std::string &str, int pos);
};

#endif // C23CODECCS3_H
