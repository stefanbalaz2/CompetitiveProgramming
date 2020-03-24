/*

    observation: pairs will be disjoint, suppose they arent, then we can reorder those pairs to get a better solution
    idea: dp[i][j] best answer upto ith position with j pairs
    optimize it with lambda optimization

    lambda optimization: https://codeforces.com/blog/entry/72577   task F

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
typedef pair<ll,int> pii;
const int maxa=1e9;
const int maxn=1e5+10;
pii dp[maxn];
int n,k;
ll inf=2e18,a[maxn];
pii check(ll delta){

    dp[0]={0,0};

    pii best={inf,-1};
    for(int i=1;i<=n;i++){

        dp[i]=dp[i-1];

        if(best.ss!=-1)
            dp[i]=min(dp[i],{best.ff-delta+a[i],best.ss+1});

        pii pom;
        pom.ss=dp[i-1].ss;
        pom.ff=dp[i-1].ff-a[i];

        best=min(best,pom);
    }

    return dp[n];
}

int main(){


    int t;
    scanf("%d",&t);
    while(t--){

        scanf("%d %d",&n,&k);
        for(int i=1;i<=n;i++)scanf("%lld",&a[i]);

        int l=0;
        int r=maxa+10;
        int sr,ret=-1;
        while(l<=r){
            sr=(l+r)/2;
            if(check(sr).ss<k){
                ret=sr;
                l=sr+1;
            }
            else r=sr-1;
        }
        pii pom=check(ret);

        printf("%lld\n",pom.ff+(ll)k*ret);
    }


	return 0;
}
