#include <iostream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <assert.h>


using namespace std;

typedef unsigned long ulong;
typedef pair<unsigned long,unsigned long> C23Block;
typedef vector<C23Block> C23;

C23 convertTo23Code(unsigned long n)
{
    int n0 = 0;
    int k0 = 0;
    int ni,ki;
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
        if(n%3 == (1<<nbits)%3)
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

string printC23(const C23& c23)
{
    printf("    #     ni      ki\n");
    for(int  i =0; i < c23.size(); i++)
    {
        printf("%5d %5d %5d\n",i,c23[i].first,c23[i].second);
    }
}

void test()
{
    for(int  i =1; i < 1000000; i++)
    {
        C23 c23i = convertTo23Code(i);
        assert(C23toNumber(c23i) == i);
        printf("%d Sucsess\n",i);
    }
}

int main()
{
    test();
    cout<<"\n\nHello\n\n";
    return 0;
}

