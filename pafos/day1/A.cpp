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

const int maxn=110;
int a[maxn];
int n;
int dp[2][1000010][2];
const int maxa=1000010;

int main(){


    scanf("%d",&n);
    int curr=0;
    dp[0][0][0]=1;
    int sum=0;
    for(int i=1;i<=n;i++){

        int a;
        scanf("%d",&a);

        for(int j=0;j<maxa;j++){
            dp[curr^1][j][0]=dp[curr][j][0];
            dp[curr^1][j][1]=dp[curr][j][1];
        }
        for(int j=0;j<maxa;j++){
            if(j+a>maxa)break;
            dp[curr^1][j+a][0]+=dp[curr][j][1];
            dp[curr^1][j+a][1]+=dp[curr][j][0];
        }
        for(int j=0;j<maxa;j++){
            dp[curr^1][j][0]=min(dp[curr^1][j][0],4);
            dp[curr^1][j][1]=min(dp[curr^1][j][1],4);

            ///printf("%d | %d %d\n",j,dp[curr^1][j][0],dp[curr^1][j][1]);
        }

        curr^=1;
        sum+=a;
    }
    if(sum%2){
        printf("No\n");
        return 0;
    }
    if(dp[curr][sum/2][0]==4)printf("Yes\n");
    else printf("No\n");

    return 0;
}
