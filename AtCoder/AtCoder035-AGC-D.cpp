/*

    idea:https://img.atcoder.jp/agc035/editorial.pdf

*/
#include<bits/stdc++.h>
#define pb push_back
#define ll long long
#define ff first
#define ss second
using namespace std;
typedef pair<ll,ll> pii;

const int maxn=19;
ll inf=2e18,a[maxn];
int n;
map<pii,ll>mapa[maxn][maxn];
ll go(int l,int r,int lx,int rx){

    if(l>r)return 0;

    map<pii,ll>::iterator it=mapa[l][r].find({lx,rx});
    if(it!=mapa[l][r].end()){
        return it->second;
    }

    ll ret=inf;

    for(int i=l;i<=r;i++){
        ret=min(ret,a[i]*(lx+rx)+ go(l,i-1,lx,lx+rx) + go(i+1,r,lx+rx,rx) );
    }

    mapa[l][r].insert({{lx,rx},ret});

    return ret;
}

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }

    printf("%lld\n",go(2,n-1,1,1)+a[1]+a[n]);


return 0;
}
