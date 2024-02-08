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

const int MAXN = 200010;
int a[MAXN];
pii dp[20][MAXN];

pii get_min(int l,int r){
    int h=log2(r-l+1);
    return min(dp[h][l],dp[h][r-(1<<h)+1]);
}
int n;
map<pii, int> memo;
map<pair<pii,bool>,int>memo2;
int go(int l,int r);
int go2(int l,int r,int flag){

    if(l>r)return 0;

    pair<pii,int>pr={ {l,r},flag };
    if(memo2.count(pr))return memo2[pr];

    int &ans=memo2[pr];

    ans=go(l,r);
    if(flag==0)ans=add(ans,go2(l+1,r,0));
    else ans=add(ans,go2(l,r-1,1));
    return ans;
}
int go(int l,int r){


    if (l == r) return 1;
    /*pii pr = {l, r};
    if (memo.count(pr)) return memo[pr];

    ///if(memo.size()%1000==0)printf("%d SZ\n",memo.size());

    int &ans = memo[pr];
*/
    int m = get_min(l,r).ss;

    int ans=1;

    //for(int i=l;i<m;i++)ans=add(ans,go(i,m-1));
    //for(int i=m+1;i<=r;i++)ans=add(ans,go(m+1,i));

    ans=add(go2(l,m-1,0),ans);
    ans=add(go2(m+1,r,1),ans);

    ///printf("%d ");

    return ans;
}
void prek(){

    for(int i=0;i<19;i++){
    for(int j=1;j<=n;j++){
        if(j+(1<<i)>n)dp[i+1][j]=dp[i][j];
        else dp[i+1][j]=min(dp[i][j],dp[i][ j+(1<<i) ]);
    }
    }

}
int main(){

   /// freopen("test.txt","r",stdin);

    int t;
    scanf("%d",&t);

    while(t--){

        memo.clear();
        memo2.clear();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            //a[i]=i;
        }
        for(int i=1;i<=n;i++){
            dp[0][i]={a[i],i};
        }
        ///random_shuffle(a+1,a+n+1);
        prek();
        ///srand(time(NULL));
        ///random_shuffle(a+1,a+n+1);

        printf("%d\n",go(1,n));

        ///printf("%d SZ\n",memo.size());
    }

    return 0;
}
