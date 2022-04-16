#include "testlib.h"
#include <map>
#include <vector>
using namespace std;

map<pair<int, int>, int> edges;
int n, m, s, t;

long long dp[105], cnt[105];
int cntlis(vector<int> v)
{
    long long ans=0, cntans=0;
    for(int i=1; i<=v.size(); i++)
    {
        dp[i]=1;
        cnt[i]=1;
        for(int j=i-1; j>=1; j--)
        {
            if(v[i-1]<=v[j-1]) continue;
            if(dp[j]+1==dp[i])
            {
                cnt[i]+=cnt[j];
            }
            else if(dp[j]+1>dp[i])
            {
                dp[i]=dp[j]+1;
                cnt[i]=cnt[j];
            }
        }
        if(dp[i]==ans)
        {
            cntans+=cnt[i];
        }
        else if(dp[i]>ans)
        {
            ans=dp[i];
            cntans=cnt[i];
        }
    }
    return cntans;
}

int check(int lisCnt)
{
    vector<int> vec;
    for(int i=1; i<=100; i++)
    {
        int tmp=ouf.readInt(0, 100, "value of numbers");
        vec.push_back(tmp);
    }
    int res=cntlis(vec);
    if(res==lisCnt)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int L=inf.readInt(), R=inf.readInt(), N=inf.readInt();
    double ans=0;
    for(int i=L; i<=R; i++)
    {
        ans+=check(i);
    }
    if(ans==0) quitf(_ok, "Correct");
    else quitf(_wa, "Incorrect");
}