#include<bits/stdc++.h>
typedef unsigned long long ll;
using u128=__uint128_t;
using namespace std;

const int MAXN = 100010;
const int ALPHA = 26;

char s[MAXN];
vector<int> occ[ALPHA];

int solve (const vector<int> &pos) {
    int tot = accumulate(pos.begin(), pos.end(), 0);
    int med = pos[2];
    int ans = 0;
    for (int i = 0; i < 5; i++) {
        ans += abs((med + i - 2) - pos[i]);
    }
    return ans;
}
const string alias = "alias";
int main(){
    int n; scanf("%d", &n);
    scanf("%s", s + 1);

    for (int i = 1; i <= n; i++) {
        occ[s[i] - 'a'].push_back(i);
    }

    int answer = INT_MAX;

    /*for (int mid = 3; mid <= n - 2; mid++) {
        vector<int> pos;
        for (int chances_a1 = -1; chances_a1 < 2; chances_a1 += 2) {
            if (!extract(occ['a' - 'a'], mid - 2, chances_a1, pos) continue;

            for (int chances_a2 = -1; chances_a2 < 2; chances_a2 += 2) {
                if (!extract(occ['a' - 'a'], mid + 1, chances_a2, pos) continue;

                for (int chances_l = -1; chances_l < 2; chances_l += 2) {
                    if (!extract(occ['l' - 'a'], mid - 1, chances_l, pos) continue;

                    for (int chances_i = -1; chances_i < 2; chances_i += 2) {
                        if (!extract(occ['i' - 'a'], mid, chances_i, pos)) continue;

                        for (int chances_s = -1; chances_s < 2; chances_s += 2) {
                            if (!extract(occ['s' - 'a'], mid, chances_s, pos)) continue;

                            update_answer(ans, pos, mid);
                        }
                    }
                }
        }
    }*/

    for (int i = 0; i < occ[alias[0] - 'a'].size(); i++) {
        int st = occ[alias[0] - 'a'][i];
        vector<int> pos; pos.push_back(st);
        bool failed = false;
        int swaps = 0;
        for (int j = 1; j < 5; j++) {
            int let = alias[j] - 'a';
            int next_pos = lower_bound(occ[let].begin(), occ[let].end(), st + 1) - occ[let].begin();
            if (next_pos == (int)occ[let].size()) {
                failed = true;
                break;
            }
            st = occ[let][next_pos];
            pos.push_back(st);
        }
        if (!failed) {
            answer = min(answer, solve(pos));
        }
    }
    printf("%d\n", answer);
    return 0;
}
