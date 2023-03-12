/*

    idea:   https://codeforces.com/blog/entry/61891

*/
#include<bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
using namespace std;
typedef pair<ll,ll> pii;

const int maxn=1010;

int n,m;
vector<pair<int,pii> >cand;
ll dp[maxn][maxn],mod=998244353;

ll step(ll base,ll pw){


    ll ret=1;
    while(pw){

        if(pw&1)ret=(ret*base)%mod;

        base=(base*base)%mod;
        pw/=2;

    }

    return ret;
}

ll inv(ll x){

    return step(x,mod-2);

}

int main(){

    ///freopen("test.txt","r",stdin);


    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int a;
            scanf("%d",&a);
            cand.pb({a,{i,j} } );
        }
    }

    sort(cand.begin(),cand.end());

    ll sum=0;
    ll xsab=0;
    ll ysab=0;
    ll xmnoz=0;
    ll ymnoz=0;
    ll cnt=0;
    for(int j=0;j<cand.size();j++){

        vector<pii>vect;
        vect.pb(cand[j].ss);
        for(int k=j+1;k<cand.size();k++){
            if(cand[k].ff!=cand[k-1].ff){
                break;
            }
            vect.pb(cand[k].ss);
            j++;
        }

        for(int i=0;i<vect.size();i++){

            ll x=vect[i].ff;
            ll y=vect[i].ss;

            dp[x][y]=sum+(((x*x)%mod)*cnt)%mod+ (x*xmnoz)%mod+xsab +(((y*y)%mod)*cnt)%mod+(y*ymnoz)%mod+ysab;
            dp[x][y]%=mod;
            dp[x][y]*=inv(cnt);
            dp[x][y]%=mod;

           /// printf("%lld %lld %lld  | %lld %lld %lld %lld %lld %lld  ADSA\n",x,y,dp[x][y],sum,cnt,xmnoz,ymnoz,xsab,ysab);

        }

        for(int i=0;i<vect.size();i++){

            ll x=vect[i].ff;
            ll y=vect[i].ss;

            cnt++;
            sum=(sum+dp[x][y])%mod;
            xsab=(xsab+x*x)%mod;
            ysab=(ysab+y*y)%mod;

            xmnoz=(xmnoz-2*x)%mod;
            if(xmnoz<0)xmnoz+=mod;

            ymnoz=(ymnoz-2*y)%mod;
            if(ymnoz<0)ymnoz+=mod;

        }

    }

    int c1,c2;
    scanf("%d %d",&c1,&c2);

    printf("%lld\n",dp[c1][c2]);


    return 0;
}
