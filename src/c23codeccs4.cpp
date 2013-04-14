#include <cmath>
#include <string.h>
#include <stdio.h>

#include "util.h"
#include "c23codeccs4.h"

C23CodecCS4::C23CodecCS4()
{
}


std::string C23CodecCS4::encode(const uint64_t num)
{
    std::string c23Code = C23Codec::encode(num);
    addControlSum(c23Code);
    return c23Code;
}





void C23CodecCS4::addControlSum(std::string &code)
{
    uint64_t ncode = code.size() - CODE_DELIMITER.size();
    uint64_t offset = 2;
    appendShortCS(code,offset, ncode - offset ,'0');
    appendShortCS(code,offset, ncode - offset,'1');
    appendBlockNumCS(code,offset, ncode - offset);
    appendRepairedCS(code,generateRepairedCS(code, offset,ncode - offset,'0'));
    appendRepairedCS(code,generateRepairedCS(code, offset,ncode - offset,'1'));
    std::vector<int> cs = getControlSum(code,0,ncode);
    int nequation = cs.size();
    for(int j = 0; j < nequation; j++)
    {
        code.append(1 ,(char) ( cs[j] + '0') );
    }
}

std::string C23CodecCS4::generateRepairedCS(std::string &code, int offset, int ncode, char symbol)
{
    std::string res;
    int nsymbol = 0;
    int i;
    for( i = offset; i < ncode + offset; i++)
    {
        if( code[i] == symbol)
        {
            nsymbol++;
        }else{
            if( nsymbol != 0 && i != 0)
            {
                res.append(1, nsymbol%2 + '0');
                nsymbol = 0;
            }
        }
    }

    if( nsymbol != 0 && i != 0)
    {
      res.append(1, nsymbol%2 + '0');
    }

    return res;
}

void C23CodecCS4::appendShortCS(std::string &code, int offset, int ncode, char symbol)
{
    unsigned int nsymbol = 0;
    for(int i = offset; i < ncode + offset; i++)
    {
        if(code[i] == symbol)
            nsymbol++;
    }
    char cs[3];
    nsymbol = nsymbol % 4;
    cs[0] = ((nsymbol & 0x2) >> 1) + '0';
    cs[1] = (nsymbol & 0x1) + '0';
    cs[2] = '\0';
    code.append(cs);
}

void C23CodecCS4::appendBlockNumCS(std::string &code, int offset, int ncode)
{
    int blocksNum = 0;
    bool isPrevSeq1 = true;

    for(int i = offset; i < ncode + offset; i++)
    {
        if( code[i] == '0' && isPrevSeq1)
        {
            isPrevSeq1 = false;
            blocksNum ++;
        }else if(code[i] == '1')
        {
            isPrevSeq1 = true;
        }
    }
    code.append(1, blocksNum % 2  + '0' );
}

void C23CodecCS4::appendRepairedCS(std::string &code, const std::string repaired_string)
{
    std::vector<int> cs = getControlSum(repaired_string, 0, repaired_string.size());
    for(unsigned int i = 0; i < cs.size(); i++)
        code.append( 1 , cs[i] + '0' );
}

std::vector<int> C23CodecCS4::getControlSum(const std::string &code, int , int ncode)
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

int64_t C23CodecCS4::decode(const std::string &code, int64_t *codeLen)
{
//    int64_t ncode;


//    std::string delimiter1;
//    delimiter1.append(1, Ki_SYMBOl);
//    delimiter1.append(CODE_DELIMITER);
//    ncode = code.find(delimiter1);
//    int64_t ncode;


//    std::string delimiter1;
//    delimiter1.append(1, Ki_SYMBOl);
//    delimiter1.append(CODE_DELIMITER);
//    ncode = code.find(delimiter1);

//    if(ncode == std::string::npos)
//    {
//        ncode = code.find(CODE_DELIMITER);

//        if(ncode == std::string::npos)
//            return ERROR_CANNOT_FIND_DELIMITE;

//    }else
//    {
//        ncode+=1; //MISS not delimiter symbol "1"
//    }

//    LOGD("Code %s Delimiter %s", code.c_str(),
//           code.substr(ncode,CODE_DELIMITER.size()).c_str());

//    int64_t res = checkControlSum(code,ncode);
//    if( res == 0 )
//    {
//        return C23Codec::decode(code,codeLen);
//    }else if( res < 0 ){
//        return res;
//    }else if(res < code.size()){
//        //errorPos = res;
//        std::string repaired_code = code;
//        invertBit(repaired_code,res - 1);
//        //printf("%s ::Repaired code pos = %lld",repaired_code.c_str(), res - 1);
//        return C23Codec::decode(repaired_code,codeLen);
//    }else{
//        return ERROR_WRONG_REPAIRED_BIT;
//    }
////    if(ncode == std::string::npos)
////    {
////        ncode = code.find(CODE_DELIMITER);

////        if(ncode == std::string::npos)
////            return ERROR_CANNOT_FIND_DELIMITE;

////    }else
////    {
////        ncode+=1; //MISS not delimiter symbol "1"
////    }

////    LOGD("Code %s Delimiter %s", code.c_str(),
////        int64_t ncode;


//    std::string delimiter1;
//    delimiter1.append(1, Ki_SYMBOl);
//    delimiter1.append(CODE_DELIMITER);
//    ncode = code.find(delimiter1);

//    if(ncode == std::string::npos)
//    {
//        ncode = code.find(CODE_DELIMITER);

//        if(ncode == std::string::npos)
//            return ERROR_CANNOT_FIND_DELIMITE;

//    }else
//    {
//        ncode+=1; //MISS not delimiter symbol "1"
//    }

//    LOGD("Code %s Delimiter %s", code.c_str(),
//           code.substr(ncode,CODE_DELIMITER.size()).c_str());

//    int64_t res = checkControlSum(code,ncode);
//    if( res == 0 )
//    {
//        return C23Codec::decode(code,codeLen);
//    }else if( res < 0 ){
//        return res;
//    }else if(res < code.size()){
//        //errorPos = res;
//        std::string repaired_code = code;
//        invertBit(repaired_code,res - 1);
//        //printf("%s ::Repaired code pos = %lld",repaired_code.c_str(), res - 1);
//        return C23Codec::decode(repaired_code,codeLen);
//    }else{
//        return ERROR_WRONG_REPAIRED_BIT;
//    }    code.substr(ncode,CODE_DELIMITER.size()).c_str());

//    int64_t res = checkControlSum(code,ncode);
//    if( res == 0 )
//    {
//        return C23Codec::decode(code,codeLen);
//    }else if( res < 0 ){
//        return res;
//    }else if(res < code.size()){
//        //errorPos = res;
//        std::string repaired_code = code;
//        invertBit(repaired_code,res - 1);
//        //printf("%s ::Repaired code pos = %lld",repaired_code.c_str(), res - 1);
//        return C23Codec::decode(repaired_code,codeLen);
//    }else{
//        return ERROR_WRONG_REPAIRED_BIT;
//    }
    return -1;
}

int C23CodecCS4::  checkControlSum(const std::string &code, int64_t codeLen)
{
    code.size();
    codeLen = codeLen;
//    uint64_t ncode = codeLen;
//    int isFirstCSOK = 0;

//    //isFirstCSOK = C23CodecCS::checkControlSum(code,codeLen);

//    if(ncode <= 0)
//    {
//        return ERROR_WRONG_SIZE;
//    }

//    std::vector<int> cs = getControlSum(code,0,ncode);
//    int nequation = cs.size();
//    int64_t error = 0;
//    int diff;
//    int j;
//    int offset = codeLen + CODE_DELIMITER.size() + 2;
//    for( j =0; j < nequation && offset + j < (int) code.size() ; j++ )
//    {
//        diff =  (cs[j] + (code[offset + j ] - '0')) % 2;
//        error = error | (diff << j);
//    }

//    if( j < nequation && offset + j  >= (int)code.size())
//    {
//        return ERROR_WRONG_SIZE;
//    }

//    if(isFirstCSOK == 0 )
//    {
//        return 0;
//    }else{
//        return error;
//    }
    return 0;
}


uint8_t C23CodecCS4::nbit(uint64_t num, uint32_t nbit)
{
    return (num >> nbit) & 0x1;
}

void C23CodecCS4::invertBit(std::string &str, int pos)
{
    str[pos] = ( 1 - (str[pos] - '0')) + '0';
}
