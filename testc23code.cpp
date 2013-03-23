#include <assert.h>
#include <stdio.h>

#include "testc23code.h"
#include "time.h"


Testc23Code::Testc23Code()
{
}

void Testc23Code::test1()
{
    time_t start = time(NULL);
    C23Codec c23;
    for(int x = 2; x < 1000000; x++)
    {
        std::string code = c23.encode(x);
        int res = c23.decode(code.c_str());
        assert( res == x );
    }
    printf("Test Succeed %d seconds.\n", time(NULL) - start);
}


void Testc23Code::runTests()
{
    test1();
}
