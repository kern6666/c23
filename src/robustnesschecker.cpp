#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "util.h"
#include "robustnesschecker.h"

enum{ERROT_DETECTED = 1, ERROR_REPAIRED = 2, ERROR_MISSED = 0};

RobustnessChecker::RobustnessChecker(int n, ...)
{    
    va_list vl;
    va_start(vl,n);
    ncodecs= n;
    codecs = new AbstractCodec*[n];
    for(int i =0;i < n;i++)
    {
        codecs[i] = va_arg(vl,AbstractCodec*);
    }
    va_end(vl);
    srand(time(NULL));
}

RobustnessChecker::~RobustnessChecker()
{
    for(int i =0;i < ncodecs;i++)
    {
        delete codecs[i];
    }
    delete[] codecs;
}

int RobustnessChecker::check(int64_t num,int codec_num)
{
    std::string code = codecs[codec_num]->encode(num);
    uint64_t rnum = rand() + 5;
    std::string rnumCode = codecs[codec_num]->encode(rnum);
    LOGD("Code    : %s\n",code.c_str());
    int invBit = invertOneBit(code);
    LOGD("Corupted: %s :: %d\n",code.c_str(),invBit);
    code.append(rnumCode);
    int64_t res = codecs[codec_num]->decode(code);
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

RobustCheckingResult* RobustnessChecker::check(int64_t from, int64_t to, int64_t times)
{
    RobustCheckingResult* res = new RobustCheckingResult[ncodecs];

    for(int c =0;c< ncodecs;c++)
    {
        res[c].errorDetected = 0;
        res[c].errorFixed = 0;
        res[c].per_success = 0;
    }

    if(to == from || times == 0)
    {
        return res;
    }


   for(int codec_num = 0; codec_num < ncodecs; codec_num++)
   {
       for(int k = 0; k < times ; k++)
        {
            for(int i = from; i < to; i++)
            {
                int checkRes = check(i,codec_num) ;
                if(checkRes == ERROT_DETECTED)
                {
                    res[codec_num].errorDetected+=1;
                }else if(checkRes == ERROR_REPAIRED){
                    res[codec_num].errorFixed+=1;
                }
            }
        }
       res[codec_num].errorDetected *= 100.0 / times / (to - from);
       res[codec_num].errorFixed *= 100.0 / times / (to - from);
       res[codec_num].per_success = res[codec_num].errorDetected + res[codec_num].errorFixed;
   }

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
