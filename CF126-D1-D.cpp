/*

    idea: https://codeforces.com/blog/entry/3140

*/
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ff first
#define ss second
#define ll long long
typedef pair<int,int> pii;
const ll maxn=1e18;
int br;
ll dp[100][2];
ll fib[100];
int niz[100],brn;
ll go2(int x,int mora){


    if(x==brn)return 1;

    if(dp[x][mora]!=-1)return dp[x][mora];

    ll ret=0;
    dp[x][mora]=0;
    if(mora){

        if(niz[x]<=2)return 0;
        if(niz[x+1]+1>=niz[x])return 0;

        ll cnt=(niz[x]-niz[x+1])/2;
        cnt--;

        if((niz[x]-niz[x+1])%2==1){
            cnt++;
            ret+=cnt*go2(x+1,0);
        }
        else{
            ret+=go2(x+1,1);
            ret+=cnt*go2(x+1,0);
        }
    }
    else{

        ll cnt=(niz[x]-niz[x+1])/2;

        if((niz[x]-niz[x+1])%2==1){
            cnt++;
            ret+=cnt*go2(x+1,0);
        }
        else{
            ret+=go2(x+1,1);
            ret+=cnt*go2(x+1,0);
        }
    }

    dp[x][mora]=ret;

    return ret;
}
ll go(ll x){

    brn=0;

    int pt=br;
    while(x){

        while(fib[pt]>x)pt--;

        niz[++brn]=pt;
        x-=fib[pt];
    }
    niz[++brn]=1;

    return go2(1,0);

}
int main(){

    int t;
    scanf("%d",&t);

    fib[0]=1;
    fib[1]=1;
    br=1;
    for(int i=2;fib[i-2]+fib[i-1]<=maxn;i++){
        fib[i]=fib[i-1]+fib[i-2];
        br++;
    }


    while(t--){
        ll n;
        scanf("%lld",&n);
        memset(dp,-1,sizeof(dp));

        printf("%lld\n",go(n));
    }

    return 0;
}
