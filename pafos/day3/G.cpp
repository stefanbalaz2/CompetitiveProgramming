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

vector<vector<int>> groups;
int n, k, per_group;

void match_two (int g1, int g2) {
    // fprintf(stderr, "Matching 2 %d %d\n", g1, g2);
    int e2 = g2 + k - 1;
    for (int i = 0; i < k; i++) {
        groups[i].push_back(g1 + i);
        groups[i].push_back(e2 - i);
    }
}

void match_three (int g1, int g2, int g3) {
    // fprintf(stderr, "Matching 3 %d %d %d\n", g1, g2, g3);
    // Adding the third row, in order
    for (int i = 0; i < k; i++) {
        groups[i].push_back(g3 + i);
    }
    vector<pair<int, pair<int, int>>> prs;
    if (k % 2 == 0) {
        // Even K scenario (the difference will be one).
        for (int i = 0; i < k / 2; i++) {
            // matching down[i] with up[k / 2 + i]
            prs.push_back({g2 + i + g1 + k / 2 + i, {g2 + i, g1 + k / 2 + i}});
        }
        for (int i = 0; i < k / 2 - 1; i++) {
            // matching up[i + 1] with down[k / 2 + i]
            prs.push_back({g2 + k / 2 + i + g1 + i + 1, {g2 + k / 2 + i, g1 + i + 1}});
        }
        // last pair, matching down[end] with up[beg]
        prs.push_back({g2 + k - 1 + g1, {g2 + k - 1, g1}});
    } else {
        // Odd K scenario (the difference will be zero).
        for (int i = 0; i < k / 2 + 1; i++) {
            // matching up[i] with down[k / 2 + i]
            prs.push_back({g2 + k / 2 + i + g1 + i, {g2 + k / 2 + i, g1 + i}});
        }
        for (int i = 0; i < k / 2; i++) {
            // matching up[k / 2 + i + 1] with down[i]
            prs.push_back({g2 + i + g1 + k / 2 + 1 + i, {g2 + i, g1 + k / 2 + 1 + i}});
        }
    }

    // fprintf(stderr, "Finished pairing! prs size is %d\n", (int)prs.size());
    sort(prs.begin(), prs.end());
    for (int i = 0; i < k; i++) {
        groups[k - 1 - i].push_back(prs[i].second.first);
        groups[k - 1 - i].push_back(prs[i].second.second);
    }
}

int main(){
    scanf("%d %d", &n, &k);
    int per_group = n / k;
    if (per_group == 1) {
        // We have n groups of 1 integer.
        for (int i = 1; i <= n; i++) {
            printf("%d\n", i);
        }
        return 0;
    }
    groups.resize(k);
    int to_match = (per_group & 1) ? 3 : 0;
    for (int per = 1; per < per_group - to_match; per += 2) {
        match_two((per - 1) * k + 1, per * k + 1);
    }

    if (to_match > 0) {
        assert (to_match == 3);
        // Should match last three rows;
        match_three(n - 3 * k + 1, n - 2 * k + 1, n - k + 1);
    }
    for (int i = 0; i < k; i++) {
        for (auto x : groups[i]) {
            printf("%d ", x);
        }
        printf("\n");
    }

    // DEBUG
    for (int i = 0; i < k; i++) {
        fprintf(stderr, "Group %d sum: %lld\n", i, accumulate(groups[i].begin(), groups[i].end(), 0ll));
    }
    return 0;
}
