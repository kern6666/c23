#include <cmath>
#include <string.h>
#include <stdio.h>
#include "util.h"
#include "c23codeccs2.h"

C23CodecCS2::C23CodecCS2()
{
}


std::string C23CodecCS2::encode(const uint64_t num)
{
    std::string c23Code = C23Codec::encode(num);
    addControlSum(c23Code);
    return c23Code;
}


int64_t C23CodecCS2::decode(const std::string &code, int64_t *codeLen)
{
    int64_t ncode;

    errorPos = -1;
    std::string delimiter1;
    delimiter1.append(1, Ki_SYMBOl);
    delimiter1.append(CODE_DELIMITER);
    ncode = code.find(delimiter1);

    if(ncode == std::string::npos)
    {
        ncode = code.find(CODE_DELIMITER);

        if(ncode == std::string::npos)
            return ERROR_CANNOT_FIND_DELIMITE;

    }else
    {
        ncode+=1; //MISS not delimiter symbol "1"
    }

    LOGD("Code %s Delimiter %s", code.c_str(),
           code.substr(ncode,CODE_DELIMITER.size()).c_str());

    int64_t res = checkControlSum(code,ncode);
    if( res == 0 )
    {
        return C23Codec::decode(code,codeLen);
    }else if( res < 0 ){
        return res;
    }else if(res < code.size()){
        //errorPos = res;
        std::string repaired_code = code;
        invertBit(repaired_code,res - 1);
        //printf("%s ::Repaired code pos = %lld",repaired_code.c_str(), res - 1);
        return C23Codec::decode(repaired_code,codeLen);
    }else{
        return ERROR_WRONG_REPAIRED_BIT;
    }
}


void C23CodecCS2::addControlSum(std::string &code)
{
    uint64_t ncode = code.size() - CODE_DELIMITER.size();
    std::vector<int> cs = getControlSum(code,0,ncode);
    int nequation = cs.size();

    for(int j = 0; j < nequation; j++)
    {
        code.append(1 ,(char) ( ( cs[j] % 2) + '0') );
    }
}

std::vector<int> C23CodecCS2::getControlSum(const std::string &code, int , int ncode)
{
    std::vector<int> cs;
    int nequation = ceil( log2( ncode + 1) );
    cs.assign(nequation, 0);
    for(int i = 0; i < ncode; i++)
    {
        for(int j = 0; j < nequation; j++)
        {
            int coef = nbit(i +1, j);
            cs[j] += ( coef * ( code[i] - '0' ) );
        }
    }

    for(int j= 0;j < nequation;j++)
        cs[j] %= 2;
    return cs;
}

int C23CodecCS2::  checkControlSum(const std::string &code, int64_t codeLen)
{
    uint64_t ncode = codeLen;

    if(ncode <= 0)
    {
        return ERROR_WRONG_SIZE;
    }

    std::vector<int> cs = getControlSum(code,0,ncode);
    int nequation = cs.size();
    int64_t error = 0;
    int diff;
    int j;
    int offset = codeLen + CODE_DELIMITER.size();
    for( j =0; j < nequation && offset + j < (int) code.size() ; j++ )
    {
        diff =  (cs[j] + (code[offset + j ] - '0')) % 2;
        error = error | (diff << j);
    }

    if( j < nequation && offset + j  >= (int)code.size())
    {
        return ERROR_WRONG_SIZE;
    }

    return error;
}


uint8_t C23CodecCS2::nbit(uint64_t num, uint32_t nbit)
{
    return (num >> nbit) & 0x1;
}

void C23CodecCS2::invertBit(std::string &str, int pos)
{
    str[pos] = ( 1 - (str[pos] - '0')) + '0';
}
