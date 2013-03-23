#include <iostream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <assert.h>
#include "c23code.h"
#include "testc23code.h"


using namespace std;

typedef unsigned long ulong;
typedef pair<unsigned long,unsigned long> C23Block;
typedef vector<C23Block> C23;

C23 convertTo23Code(unsigned long n)
{
    size_t n0 = 0;
    size_t k0 = 0;
    size_t ni,ki;
    while(n%2 == 0)
    {
        n/=2;
        n0++;
    }
    while(n%3 == 0)
    {
        n/=3;
        k0++;
    }
    C23 res;
    res.push_back(C23Block(n0,k0));
    while(n>1)
    {
        ulong nbits = (int)log2(n);
        if(n%3 == (ulong)(1<<nbits)%3)
        {//max block
            ni = nbits;
        }else
        {//min block
            ni = nbits - 1;
        }
        n -= 1 << ni;
        ki = 0;
        while(n%3 == 0)
        {
            n /= 3;
            ki++;
        }
        res.push_back(C23Block(ni,ki));
    }
    return res;
}

ulong fplus(ulong ki)
{
    return ki-1;
}

ulong flog(ulong ki)
{
    return (ulong)(log2(3)-1)*ki;
}


string convertToC23Coding(ulong num, ulong(*fki)(ulong))
{

    const char Ki_SYMBOl = '1';
    const char Ni_SYMBOl = '0';
    const string blockDelimiter = " ";
    const bool isShowMinMax = true;
    string prefix;
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

     const C23 &c23 = convertTo23Code(num);

    string c23Plus;
    ulong prevNi = 0;
    ulong xi = 1;
    for(int blockNum =c23.size() - 1;blockNum>0;blockNum--)
    {
        c23Plus.append(c23[blockNum].second,Ki_SYMBOl);
        c23Plus.append(c23[blockNum].first-prevNi - fki(c23[blockNum].second),Ni_SYMBOl);
        xi = pow(2,c23[blockNum].first) + pow(3,c23[blockNum].second)*xi;
        prevNi =(ulong) log2(xi);

        if(isShowMinMax)
        {
            if(prevNi == c23[blockNum].first)
            {
                c23Plus.push_back('+');
            }else{
                c23Plus.push_back('-');
            }
        }

        c23Plus.append(blockDelimiter.begin(),blockDelimiter.end());
   }
    string res;
    res.append(prefix.begin(),prefix.end());
    c23Plus.append(blockDelimiter.begin(),blockDelimiter.end());
    res.append(c23Plus.rbegin(),c23Plus.rend());

    return res;
}

string convertToC23Plus(ulong num)
{
    return convertToC23Coding(num,fplus);
}

string convertToC23Log(ulong num)
{
    return convertToC23Coding(num,flog);
}

ulong C23toNumber(const C23 &c23)
{
    ulong res = 1;
    for(int i = c23.size()-1;i>=1;i--)
    {
        C23Block c;
        res = (1 << c23[i].first) + pow(3,c23[i].second)*res;
    }
    res = res << c23[0].first;
    res *=pow(3,c23[0].second);
    return res;
}

void printC23(const C23& c23)
{
    printf("# |\tni\tki\n");
    for(size_t  i =0; i < c23.size(); i++)
    {
        printf("%d |\t%ld\t %ld\n",i,c23[i].first,c23[i].second);
    }
}

void test()
{
    for(unsigned long  i =1; i < 1000000; i++)
    {
        C23 c23i = convertTo23Code(i);
        assert(C23toNumber(c23i) == i);
        printf("%ld Sucsess\n",i);
    }
}

void printInequality(ulong di,ulong ki)
{
    double lp = (log2(3)-1)*ki - log2(3);
    double rp = (log2(3)-1)*ki + 1;
    printf("\n(di,ki) : (%ld,%ld) || %lf < %ld < %lf %s\n",di,ki,lp,di,rp,
           lp <= di && di <= rp ? "TRUE" : "FALSE");
}

int main()
{
    //test();
//    ulong num = 2012201211;
//    cout<<endl;
//    printC23(convertTo23Code(num));
//    cout<<endl<<convertToC23Plus(num)<<endl<<endl;
//    cout<<endl<<convertToC23Log(num)<<endl<<endl;

//    const float di = 3;
//    const float ki = 5;
//    cout<< (int)log2(3)<<(log2(3))/(log2(3)-1)<<endl<<endl;
//    printInequality(di,ki);
//    printInequality(di-1,ki+1);
//    printInequality(di+1,ki-1);
    int64_t x = 2222;
    C23Codec c23;
    std::string code = c23.encode(x);
    cout << x << " : " << code << endl;
    int64_t decoded = c23.decode(code.c_str());
    cout << decoded << endl;
    if( decoded != x )
    {
        cerr<<"Wrong result.\n";
    }
    Testc23Code test;
    test.runTests();
    return 0;
}

