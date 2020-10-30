/*

    idea: https://img.atcoder.jp/arc086/editorial.pdf

*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<ll,ll> pii;
const int maxn=2e5+10;
ll mod=1e9+7;
int cnt[maxn],n,maxlvl,ind[maxn];
vector<int>vect[maxn];
struct trip{
    ll one,two,three;
};
vector<trip>dp[maxn];
bool srt(int x,int y){
    return dp[x].size()>dp[y].size();
}
void go(int x,int lvl){

    cnt[lvl]++;
    ind[x]=x;
    int maxsz=0;
    maxlvl=max(maxlvl,lvl);
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        go(id,lvl+1);

        if(dp[ind[x]].size()<dp[ind[id]].size())swap(ind[x],ind[id]);

        maxsz=max(maxsz,(int)dp[ind[id]].size());
        int curr=dp[ind[x]].size()-1;
        for(int j=dp[ind[id]].size()-1;j>=0;j--){

            trip pom1=dp[ind[id]][j];
            trip pom2=dp[ind[x]][curr];

            dp[ind[x]][curr]={ ( pom1.one*pom2.one )%mod, (pom1.one*pom2.two+pom1.two*pom2.one)%mod, ( (pom1.one*pom2.three+pom1.two*pom2.two)%mod+(pom1.two*pom2.three+pom1.three*pom2.one)%mod+(pom1.three*pom2.two+pom1.three*pom2.three)%mod )%mod};

            curr--;
        }

    }

    for(int i=1;i<=maxsz;i++){
        dp[ind[x]][dp[ind[x]].size()-i].one=(dp[ind[x]][dp[ind[x]].size()-i].one+dp[ind[x]][dp[ind[x]].size()-i].three)%mod;
        dp[ind[x]][dp[ind[x]].size()-i].three=0;
    }

    dp[ind[x]].pb({1,1,0});
}
ll step(ll base,ll pw){

    ll ret=1;
    while(pw){


        if(pw&1)ret=(ret*base)%mod;

        base=(base*base)%mod;
        pw=pw/2;
    }

    return ret;
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int p;
        scanf("%d",&p);
        vect[p].pb(i);
    }

    go(0,1);

    int ch=maxlvl;
    ll rez=0;
    for(int i=0;i<dp[ind[0]].size();i++){
        rez=(rez+step(2,n+1-cnt[ch])*dp[ind[0]][i].two)%mod;
        ch--;
    }

    printf("%lld\n",rez);

    return 0;
}
