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

inline int f(int x) {
    return x / 3;
}

int main(){
    int n; scanf("%d", &n);
    if (n == 1) {
        printf("1 1\n");
        return 0;
    }
    int min_non = 0, max_non = 0;
    if (n % 2 == 1) {
        min_non = 1 + 2 * f(n / 2);
        max_non = n;
    } else {
        min_non = 2 + 2 * f(n / 2 - 1);
        max_non = n;
    }
    printf("%d %d\n", min_non, max_non);
    return 0;
}
