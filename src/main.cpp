#include <vector>
#include <cmath>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "c23code.h"
#include "c23codeccs.h"
#include "c23codeccs2.h"
#include "c23codeccs3.h"
#include "tests/testc23code.h"
#include "robustnesschecker.h"

using namespace std;



int main()
{
//    Testc23Code test;
//    test.runTests();

    int ncodecs = 4;
    RobustnessChecker robChecker(ncodecs ,new C23Codec(),new C23CodecCS(),new C23CodecCS2(),new C23CodecCS3());
    RobustCheckingResult* res = robChecker.check(5,10000,5);
    for(int c =0; c< ncodecs;c++)
    {
        fprintf(stdout," Codec %i :: Error detected: %.2f Error fixed = %.2f \n",
                c ,res[c].per_success, res[c].errorFixed );
    }
    return 0;
}

