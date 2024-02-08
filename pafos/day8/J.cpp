#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxn=5010;
int pc[maxn][maxn][2],a[maxn],dp[2][maxn],n,k,b[maxn];
//int pc2[maxn][maxn][2];
ll pref[maxn];
inline ll get_pref(int l,int r){
    return pref[r]-pref[l-1];
}
void prek(){

    for(int i=1;i<=n;i++)pref[i]=pref[i-1]+a[i];

    for(int j=1;j<=k;j++){

        int r=0;
        for(int i=1;i<=n;i++){

            if(r<i)r=i-1;
            while(r+1<=n && get_pref(i,r+1)<=b[j])r++;

            pc[i][j][0]=r;

        }

    }


    for(int j=1;j<=k;j++){

        int r=n+1;
        for(int i=n;i>=1;i--){

            if(r>i)r=i+1;
            while(r-1>=1 && get_pref(r-1,i)<=b[j])r--;

            pc[i][j][1]=r;


        }

    }

}
bool check(int l,int k,int r,int prv){

    if(pc[l][k][0]>=r-1 || pc[r][k][1]<=l+1)return true;
    if(dp[prv][ pc[l][k][0]+1]>=r)return true;
    if(dp[prv][l]>=pc[r][k][1]-1)return true;
    return false;
}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&k);

    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=k;i++){
        scanf("%d",&b[i]);
    }
    prek();

    int curr=0;
    for(int i=1;i<=n;i++){
        dp[curr][i]=i;
    }

    for(int i=1;i<=k;i++){
        int nxt=(curr^1);

        for(int j=1;j<=n;j++){

            dp[nxt][j]=dp[curr][j];
            for(int k=dp[nxt][j]+1;k<=n;k++){
                if(check(j,i,k,curr))dp[nxt][j]++;
                else break;
            }

        }

        curr^=1;
    }
    if(dp[curr][1]>=n)printf("Yes\n");
    else printf("No\n");

    return 0;
}
