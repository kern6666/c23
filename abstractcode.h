#ifndef ABSTRACTCODE_H
#define ABSTRACTCODE_H

#include <stdint.h>
#include <string>

enum{ ERROR_WRONG_SIZE = -2, ERROR_WRONG_BLOCK = -1,
      ERROR_CANNOT_FIND_DELIMITE = -3 , ERROR_WRONG_PREFIX = -4,
    ERROR_WRONG_CHECKSUM = -5,ERROR_WRONG_REPAIRED_BIT = -6};

class AbstractCodec
{
public:
    AbstractCodec(){}
    virtual ~AbstractCodec(){}
    virtual std::string encode(uint64_t num) = 0;
    virtual int64_t decode(const std::string &code, int64_t* codeLen = NULL) = 0;
};

#endif // ABSTRACTCODE_H
