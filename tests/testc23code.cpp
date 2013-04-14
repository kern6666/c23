#include <assert.h>
#include <stdio.h>

#include "c23code.h"
#include "c23codeccs.h"
#include "c23codeccs2.h"
#include "c23codeccs3.h"
#include "testc23code.h"
#include "time.h"


Testc23Code::Testc23Code()
{
}

void Testc23Code::runTests()
{
   C23Codec codec1;
   testCodec(2,100000, codec1);
   C23CodecCS codec2;
   testCodec(2,100000, codec2);
   C23CodecCS2 codec3;
   testCodec(2,100000, codec3);
   C23CodecCS3 codec4;
   testCodec(2,100000, codec4);
}


void Testc23Code::testCodec(uint64_t from, uint64_t to1, AbstractCodec &codec)
{
    time_t start = time(NULL);
    for(int64_t x = from; x < (int64_t)to1; x++)
    {
        std::string code = codec.encode(x);
        int64_t res = codec.decode(code);
        assert( res == x );
    }
    printf("Test Succeed %ld seconds.\n", time(NULL) - start);
}
