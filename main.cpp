#include <iostream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "c23code.h"
#include "c23codeccs.h"
#include "c23codeccs2.h"
#include "testc23code.h"
#include "robustnesschecker.h"

using namespace std;



int main()
{
//    Testc23Code test;
//    test.runTests();

//    uint64_t x = 0xFFF5;
//    int i = 4;
//    uint8_t xi = (x >> i) & 1;
//    printf("x = %ll i = %d x[i] = %X \n", x, i , xi);
//    cout << x << " | " << i << " | " << (int)xi << "\n";

//    srand(time(NULL));
//    int x = 5;
//    C23CodecCS2 codec;
//    std::string code = codec.encode(x);
//    std::string corCode = code;
//    int n = code.find("0111");
//    int pos = rand() % (n );
//    corCode[pos] = (1 - (code[pos] - '0')) + '0';
//    printf("%s\n%s pos = %d n=%d \n", code.c_str(),corCode.c_str(),pos,n);
//    int dx = codec.decode(corCode);
//    printf("\n%d == %d \n",x,dx);
//    assert(dx == x);

    RobustnessChecker robChecker(new C23CodecCS2());
    RobustCheckingResult res = robChecker.check(5,10000,5);
    fprintf(stdout,"Error detected: %.2f\%. Error fixed = %.2f\%. \n", res.per_success, res.errorFixed );
    return 0;
}

