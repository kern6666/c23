#ifndef ABSTRACTCODE_H
#define ABSTRACTCODE_H

#include <stdint.h>
#include <string>

class AbstractCode
{
public:
    AbstractCode(){}
    virtual ~AbstractCode(){}
    virtual std::string encode(uint64_t num) = 0;
    virtual uint64_t decode(const std::string &code) = 0;
};

#endif // ABSTRACTCODE_H
