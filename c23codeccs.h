#ifndef C23CODECCS_H
#define C23CODECCS_H
#include "c23code.h"

class C23CodecCS : public C23Codec
{
public:
    C23CodecCS();
    virtual std::string encode(const uint64_t num);
    virtual int64_t decode(const std::string &code, int64_t* codeLen = NULL);
};

#endif // C23CODECCS_H
