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

map<pii, int> memo;
int go(int l,int r){


    if (l == r) return 1;
    pii pr = {l, r};
    if (memo.count(pr)) return memo[pr];

    int &ans = memo[pr];

    int m = l;
    for (int i = l + 1; i <= r; i++) {
        if (a[i] < a[m]) m = i;
    }

    ans += 1;
    for (int i = l; i < m; i++) {
        ans =add(ans,go(i, m - 1));
    }
    for (int i = m + 1; i <= r; i++) {
        ans =add(ans,go(m + 1, i));
    }

    return ans;
}

int main(){

    freopen("test.txt","r",stdin);

    int t;
    scanf("%d",&t);

    while(t--){

        memo.clear();
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }

        printf("%d\n",go(1,n));

    }

    return 0;
}
