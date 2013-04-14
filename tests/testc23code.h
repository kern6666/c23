#ifndef TESTC23CODE_H
#define TESTC23CODE_H
#include "abstractcode.h"

class Testc23Code
{
public:
    Testc23Code();
    void testCodec(uint64_t from, uint64_t to1, AbstractCodec &codec);
    void runTests();
};

#endif // TESTC23CODE_H
