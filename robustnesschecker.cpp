#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "util.h"
#include "robustnesschecker.h"

enum{ERROT_DETECTED = 1, ERROR_REPAIRED = 2, ERROR_MISSED = 0};

RobustnessChecker::RobustnessChecker(AbstractCodec *codec)
{
    this->codec = codec;
    srand(time(NULL));
}

RobustnessChecker::~RobustnessChecker()
{
    delete codec;
}

int RobustnessChecker::check(int64_t num)
{
    std::string code = codec->encode(num);
    uint64_t rnum = rand() + 5;
    std::string rnumCode = codec->encode(rnum);
    LOGD("Code    : %s\n",code.c_str());
    int invBit = invertOneBit(code);
    LOGD("Corupted: %s :: %d\n",code.c_str(),invBit);
    code.append(rnumCode);
    int64_t res = codec->decode(code);
    if(res == ERROR_WRONG_BLOCK
            || res == ERROR_WRONG_CHECKSUM)
    {
        return ERROT_DETECTED;
    }else if(res != num)
    {
        LOGE("Wrong decoded : enc = %lu dec = %lld .\n\n",
                (unsigned long) num,(long long) res);
        return ERROR_MISSED;
    }else
    {
        LOGD("Decoded suceess.\n\n");
        return ERROR_REPAIRED;
    }
}

RobustCheckingResult RobustnessChecker::check(int64_t from, int64_t to, int64_t times)
{
    RobustCheckingResult res = {0,0,0};

    if(to == from || times == 0)
    {
        return res;
    }



   for(int k = 0; k < times ; k++)
    {
        for(int i = from; i < to; i++)
        {
            int checkRes = check(i) ;
            if(checkRes == ERROT_DETECTED)
            {
                res.errorDetected+=1;
            }else if(checkRes == ERROR_REPAIRED){
                res.errorFixed+=1;
            }
        }
    }
   res.errorDetected *= 100.0 / times / (to - from);
   res.errorFixed *= 100.0 / times / (to - from);
    res.per_success = res.errorDetected + res.errorFixed;
    return res;
}

int RobustnessChecker::invertOneBit(std::string &str)
{
    int pos = ( rand() / (double) RAND_MAX ) *(str.size() - 1);
    if(str[pos] == '0')
    {
        str[pos] = '1';
    }else
    {
        str[pos] = '0';
    }
    return pos;
}
