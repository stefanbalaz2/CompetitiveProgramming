#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<ll,ll> pii;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxn=4e5+10;
int n,m;
ll a[maxn],b[maxn];
ll s,c[maxn],d[maxn];
vector<pair<ll,pii>>niz;
ll dp[maxn][2][4],inf=2e18,sum;

bool check(int dd){

    int fn=n+m;
    for(int i=0;i<=fn;i++)
        for(int j=0;j<4;j++)dp[i][0][j]=dp[i][1][j]=-inf;


    dp[0][0][0]=dp[0][1][0]=0;
    int pt=1;
    for(int i=1;i<=fn;i++){

        while(pt<i && niz[pt].ff<=niz[i].ff-dd)pt++;

        int tip=niz[i].ss.ss;
        ll cost;
        if(tip==0)cost=c[niz[i].ss.ff];
        else cost=d[niz[i].ss.ff];

        for(int j=0;j<4;j++){
            dp[i][tip][j|(1<<tip)]=max(dp[i][tip][j|(1<<tip)],dp[i-1][tip][j]+cost);
            dp[i][tip][j|(1<<tip)]=max(dp[i][tip][j|(1<<tip)],dp[pt-1][tip^1][j]+cost);
        }

        for(int j=0;j<4;j++){
            dp[i][tip][j]=max(dp[i][tip][j],dp[i-1][tip][j]);
            dp[i][tip^1][j]=max(dp[i][tip^1][j],dp[i-1][tip^1][j]);
        }

    }

    if(sum-dp[fn][0][3]<=s)return true;
    if(sum-dp[fn][1][3]<=s)return true;
    return false;
}

int main(){

    ///freopen("test.txt","r",stdin);

    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d %d %lld",&n,&m,&s);

        niz.clear();
        niz.pb({(int)-2e9,{0,-1}});
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
            niz.pb({a[i],{i,0} });
        }
        for(int i=1;i<=m;i++){
            scanf("%lld",&b[i]);
            niz.pb({b[i],{i,1} });
        }
        sum=0;
        for(int i=1;i<=n;i++){
            scanf("%lld",&c[i]);
            sum+=c[i];
        }
        for(int i=1;i<=m;i++){
            scanf("%lld",&d[i]);
            sum+=d[i];
        }
        sort(niz.begin(),niz.end());

        ll l=1;
        ll r=2e9+2;
        ll sr,ret=0;
        while(l<=r){
            sr=(l+r)/2;
            if(check(sr)){
                ret=sr;
                l=sr+1;
            }
            else r=sr-1;
        }
        printf("%lld\n",ret);

    }

    return 0;
}
