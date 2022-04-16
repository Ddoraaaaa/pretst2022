/*
40 tests

L, R, N

subtask 1 (15%): L,R<=1000
subtask 2 (30%): L,R<=50000
subtask 3 (55%): L,R<=1000000000
*/

#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

const int NumberOfTests=40, NumberOfSubtasks=3;
char TestName[]="./tests/test00.inp";
ofstream outp;
int  Subtasks[]=    {0,     15,     30,     55        }, Deno=100;

int MinL[]=         {0,     1000,   35000,  999500000 };
int Step[]=         {0,     101,    1000,   5000      };

//cpalgo
long long binpower(long long base, long long e, long long mod) {
    long long result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = result * base % mod;
        base = base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(long long n, long long a, long long d, int s) {
    long long x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(long long n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    long long d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

int cnt[10005];

void Gen(int pos, int minL, int step)
{
    minL+=(pos-1)*step;

	int ans=1;
	for(int i=1; i<=step; i++)
	{
		cnt[i]=cnt[i-1]+MillerRabin(minL-1+i);
	}
	for(int i=101; i<=step; i++)
	{
		if(cnt[i]-cnt[i-100]>cnt[ans+99]-cnt[ans-1])
		{
			ans=i-99;
		}
	}
	outp<<minL+ans-1<<" "<<minL+ans+98<<" 100\n";
}

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);
    for(int i=1; i<=NumberOfSubtasks; i++) Subtasks[i]=NumberOfTests*Subtasks[i]/Deno;

    int CurTest=0;
    for(int Subtask=1; Subtask<=NumberOfSubtasks; Subtask++)
    {
        for(int test=1; test<=Subtasks[Subtask]; test++, CurTest++)
        {
            TestName[12]=CurTest/10+'0', TestName[13]=CurTest%10+'0';
            outp.open(TestName);
            Gen(test, MinL[Subtask], Step[Subtask]);
            outp.close();
        }
    }
}