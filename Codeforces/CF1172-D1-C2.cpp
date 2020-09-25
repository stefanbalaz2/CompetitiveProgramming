/*

    idea:   https://codeforces.com/blog/entry/67511



*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int maxm=3010;
const int maxn=2e5+10;
ll mod=998244353;
ll w[maxn],a[maxn],sa,sb;
int in[maxm][maxm][4],f[maxm][maxm],g[maxm][maxm];
int n,m;
ll step(ll x,ll pw){

    ll ret=1;
    while(pw){
        if(pw&1)ret=(ret*x)%mod;
        pw/=2;
        x=(x*x)%mod;
    }
    return ret;
}
ll inv(ll x){
    return step(x,mod-2);
}
void go_f(int i,int j){

    for(int i=m;i>=0;i--){
        for(int j=m;j>=0;j--){

            if(i+j>m)continue;
            if(i+j==m){
                f[i][j]=1;
                continue;
            }

            f[i][j]=((ll)f[i][j]+(ll)in[i][j][1]*(ll)f[i][j+1]+(ll)in[i][j][0]*(ll)f[i+1][j] )%mod;
        }
    }

}
void go_g(int i,int j){

    for(int i=m;i>=0;i--){
        for(int j=m;j>=0;j--){

            if(i+j>m)continue;
            if(i+j==m){
                g[i][j]=1;
                continue;
            }

            g[i][j]=((ll)g[i][j]+(ll)in[i][j][3]*(ll)g[i+1][j]+(ll)in[i][j][2]*(ll)g[i][j+1]  )%mod;
        }
    }
}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&m);

    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        scanf("%lld",&w[i]);
        if(a[i])sa+=w[i];
        else sb+=w[i];
    }

    for(int i=0;i<=m;i++)
        for(int j=0;j<=m;j++){
            if(i+j>m)continue;
            ll pom=inv(sa+sb+i-j);
            in[i][j][0]=((sa+i+1)*pom)%mod;
            in[i][j][1]=((sb-j)*pom)%mod;
            in[i][j][2]=((sb-j-1)*pom)%mod;
            in[i][j][3]=((sa+i)*pom)%mod;
        }


    go_f(0,0);
    go_g(0,0);


    for(int i=1;i<=n;i++){
        if(a[i])printf("%lld ",(w[i]*f[0][0])%mod);
        else printf("%lld ",(w[i]*g[0][0])%mod);
    }

    return 0;
}
