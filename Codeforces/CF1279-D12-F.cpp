/*
    editorial: https://codeforces.com/blog/entry/72577
*/
#include<bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define ll long long
#define pb push_back
typedef pair<int,int> pii;
const int maxn=1e6+10;
pii dp[maxn],stek[maxn];
int n,l,k,pref[maxn],niz[maxn],lp,rp;
bool operator <(pii x,pii y){
    if(x.ss<y.ss)return 1;
    else if(x.ss==y.ss){
        if(x.ff>y.ff)return 1;
    }
    return 0;
}
void update(pii &x,pii y){
    if(x<y)x=y;
}
pii calc(int x){

    memset(dp,0,sizeof(dp));
    for(int i=1;i<=n;i++){
        update(dp[i],{dp[max(0,i-l)].ff+1,dp[max(0,i-l)].ss+pref[i]-pref[max(0,i-l)]-x});
        update(dp[i],dp[i-1]);
    }

return dp[n];
}
int go(){

    for(int i=1;i<=n;i++)pref[i]=pref[i-1]+niz[i];

    pii pom=calc(0);

    if(pom.ff<=k)return pref[n]-pom.ss;

    pii ret;
    int retsr;
    int l=0;
    int r=2*n;
    int sr;
    while(l<=r){
        sr=(l+r)/2;
        pii pom=calc(sr);

        if(pom.ff>=k){
            ret=pom;
            retsr=sr;
            l=sr+1;
        }
        else r=sr-1;
    }

    ret.ss=ret.ss+ret.ff*retsr-(ret.ff-k)*(retsr+1);

    return pref[n]-ret.ss;
}
int main(){

    scanf("%d %d %d",&n,&k,&l);
    string s;
    cin>>s;

    for(int i=1;i<=n;i++){
        int pom;
        if(s[i-1]>='a' && s[i-1]<='z')pom=0;
        else pom=1;

        niz[i]=pom;
    }

    int rez;
    rez=go();

    for(int i=1;i<=n;i++)niz[i]^=1;

    rez=min(rez,go());

    printf("%d\n",rez);

return 0;
}
