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

int main(){
    int n, k; scanf("%d %d", &n, &k);
    const int MAX_DAY = 32;
    vector<int> in_day[MAX_DAY];
    vector<int> ends(n), ans(n, 0);
    vector<int> ends_at[MAX_DAY];
    for (int i = 0; i < n; i++) {
        int st, en; scanf("%d %d", &st, &ends[i]);
        in_day[st].push_back(i);
    }
    for (int day = 1; day <= 31; day++) {
        for (auto x : in_day[day]) {
            ends_at[ends[x]].push_back(x);
        }
        int to_collect = k;
        while (to_collect > 0) {
            bool found = false;
            for (int d_c = 1; d_c <= 31; d_c++) {
                while (to_collect > 0 && !ends_at[d_c].empty()) {
                    found = true;
                    to_collect -= 1;
                    ans[ends_at[d_c].back()] = day;
                    ends_at[d_c].pop_back();
                }
            }
            if (!found) break;
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
