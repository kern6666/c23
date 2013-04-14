#include <stdio.h>
#include <math.h>
#include <string.h>

#include "util.h"
#include "c23code.h"

C23Codec::C23Codec():Ki_SYMBOl('1'),Di_SYMBOl('0'),BLOCK_DELIMITER("")
{
    CODE_DELIMITER.append(1, Di_SYMBOl);
    CODE_DELIMITER.append(3, Ki_SYMBOl);
}

C23Codec::~C23Codec()
{
}

std::string C23Codec::encode(uint64_t num)
{
    std::string prefix;
    if(num%2==0 && num%3==0)
    {
        num+=1;
        prefix.append("01");
    }else if(num%2==0)
    {
        num+=3;
        prefix.append("11");
    }else if(num%3==0)
    {
        num+=2;
        prefix.append("10");
    }else{
        prefix.append("00");
    }

    const _C23 &c23 = convertToC23(num);

    std::string c23Plus;
    uint64_t prevNi = 0;
    uint64_t xi = 1;
    for(int blockNum =c23.size() - 1;blockNum>0;blockNum--)
    {
        c23Plus.append(c23[blockNum].first-prevNi - fki(c23[blockNum].second),Di_SYMBOl);
        c23Plus.append(c23[blockNum].second,Ki_SYMBOl);

        xi = pow(2,c23[blockNum].first) + pow(3,c23[blockNum].second)*xi;
        prevNi =(uint64_t) log2(xi);

        c23Plus.append(BLOCK_DELIMITER);
    }

    std::string res;
    res.append(prefix);
    res.append(BLOCK_DELIMITER);
    res.append(c23Plus.begin(),c23Plus.end());
    res.append(CODE_DELIMITER);

    return res;
}

int64_t C23Codec::decode(const std::string &code, int64_t* codeLen)
{
    //checking code size
    if(code.size() < 2 + 2 + CODE_DELIMITER.size())
    {
        LOGE("Wrong code size.\n");
        return ERROR_WRONG_SIZE;
    }

    const char* pcode = code.c_str();

    uint64_t alpha = 0;

    if(strncmp(pcode,"00",2) == 0)
    {
        alpha = 0;
    }else if(strncmp(pcode,"01",2) == 0 )
    {
        alpha = -1;
    }else if(strncmp(pcode,"10",2) == 0)
    {
        alpha = -2;
    }else if(strncmp(pcode,"11",2) == 0)
    {
        alpha = -3;
    }else{
        LOGE("Wrong code prefix.\n");
        return ERROR_WRONG_PREFIX;
    }
    pcode += 2;

    _C23Block block;

    uint64_t prevNi = 0;
    //uint64_t ni;
    uint64_t xi = 1;
    bool isDelimiter = false;

    while(*pcode != '\0')
    {
        if(!getNextBlock(pcode, block,&isDelimiter))
        {
            LOGE("Can not decode block from code <%s>. \n",pcode);
            return ERROR_WRONG_BLOCK;
        }

        if(isDelimiter)
            break;
        if(!checkBlock(block.first , block.second, xi, prevNi, &xi))
        {
            LOGE("Wrong block: <%s>. \n",pcode);
            return ERROR_WRONG_BLOCK;
        }
//        ni = block.first + block.second + prevNi - 1;
//        xi = (1 << ni) + pow(3, block.second) * xi;
        pcode += block.first + block.second;
        prevNi = (uint64_t)log2(xi);
    }

    xi += alpha;

    if(!isDelimiter)
    {
        LOGE("Can not find deliter block.\n");
        return ERROR_CANNOT_FIND_DELIMITE;
    }

    if(codeLen != NULL)
    {
        *codeLen = pcode - code.c_str() + 4;
    }

    return xi;
}

uint64_t C23Codec::fki(uint64_t ki)
{
    return ki -1;
}

_C23 C23Codec::convertToC23(const uint64_t num)
{
    uint64_t x = num;
    _C23 res;
    size_t n0 = 0;
    size_t k0 = 0;
    size_t ni,ki;
    while(x % 2 == 0)
    {
        x/=2;
        n0++;
    }
    while(x%3 == 0)
    {
        x/=3;
        k0++;
    }
    res.push_back(_C23Block(n0,k0));
    while(x>1)
    {
        uint64_t nbits = (int)log2(x);
        if(x%3 == (uint64_t)(1<<nbits)%3)
        {//max block
            ni = nbits;
        }else
        {//min block
            ni = nbits - 1;
        }
        x -= 1 << ni;
        ki = 0;
        while(x%3 == 0)
        {
            x /= 3;
            ki++;
        }
        res.push_back(_C23Block(ni,ki));
    }
    return res;
}

bool C23Codec::getNextBlock(const char *code, _C23Block &resultBlock, bool *isDelimiter)
{
    uint64_t di = 0;
    uint64_t ki = 0;
    const char *pcode = code;

    if(strncmp(code,CODE_DELIMITER.c_str(), CODE_DELIMITER.size()) == 0)
    {
        *isDelimiter = true;
        return true;
    }

    *isDelimiter = false;
    while(*pcode != '\0' && *pcode == Di_SYMBOl)
    {
        pcode++;
        di++;
    }

    if(di == 0)
    {
        return false;
    }

    while(*pcode != '\0' && *pcode == Ki_SYMBOl)
    {
        pcode++;
        ki++;
    }

    if(ki == 0)
    {
        return false;
    }

    resultBlock.first = di;
    resultBlock.second = ki;
    return true;
}

bool C23Codec::checkBlock(uint64_t di, uint64_t ki, uint64_t xi1, uint64_t ni1, uint64_t *xi)
{
    double log23 = log2(3);
    uint64_t ni = di + ki + ni1 - 1;
    *xi = (1 << ni) + pow(3, ki) * xi1;
    if( ((uint64_t)log2(*xi)) != ni)
    {//checking minimal block
        if( ki *(log23 - 1) - log23 < di - 1 && di - 1 < ki*(log23 - 1) +1)
        {
            return true;
        }else
        {
            return false;
        }
    }else{ //checking maximal block
        if( ki *(log23 - 1) < di - 1)
        {
            return true;
        }else
        {
            return false;
        }
    }
}

