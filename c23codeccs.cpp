#include "util.h"
#include "c23codeccs.h"

C23CodecCS::C23CodecCS()
{
}

std::string C23CodecCS::encode(const uint64_t num)
{
    std::string code = C23Codec::encode(num);
    int64_t nZero = 0;
    int64_t nOne = 0;
    size_t codelen = code.size();
    for(size_t i = 0; i < codelen; i++)
    {
        if(code[i] == '0')
        {
            nZero++;
        }else if(code[i] == '1')
        {
            nOne++;
        }
    }
    code.append( 1, '0' + nZero % 2);
    code.append( 1, '0' + nOne % 2);
    return code;
}

int64_t C23CodecCS::decode(const std::string &code, int64_t* codeLen)
{
    int64_t ncode = 0;
    int64_t res = C23Codec::decode(code,&ncode);
    if( res >= 0 )
    {
        if(code.size() < ncode + 2)
        {
            LOGE("Can not find check sum.");
            return ERROR_WRONG_SIZE;
        }
        int64_t nZero = 0;
        int64_t nOne = 0;
        for(int64_t i = 0; i < ncode; i++)
        {
            if(code[i] == '0')
            {
                nZero++;
            }else if(code[i] == '1'){
                nOne++;
            }
        }
        if( code[ncode] - '0' != nZero % 2
                || code[ncode + 1] - '0' != nOne % 2)
        {
            return ERROR_WRONG_CHECKSUM;
        }else
        {
            if(codeLen != NULL)
            {
                *codeLen = ncode + 2;
            }
            return res;
        }
    }else{
        return res;
    }
}
