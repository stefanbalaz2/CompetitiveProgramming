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

const int MAXN = 1000005;
char s[MAXN];

int x[MAXN], y[MAXN];
int dp[MAXN];

void normalize (vector<int> what, unordered_map<int, int> &where) {
    sort(what.begin(), what.end());
    what.resize(unique(what.begin(), what.end()) - what.begin());
    int ID = 0;
    for (auto x : what) {
        ID += 1;
        where[x] = ID;
    }
}

struct fenwick_tree {
    vector<int> fenw;
    int n;
    fenwick_tree() {

    }
    fenwick_tree(int _n) {
        n = _n;
        fenw.resize(n + 1);
    }
    void upd (int pos, int val) {
        while (pos <= n) {
            fenw[pos] = add(fenw[pos], val);
            pos += (pos & -pos);
        }
    }
    int get_larger (int pos) {
        return sub(get(n), get(pos));
    }
    int get_smaller (int pos) {
        if (pos <= 0) return 0;
        return get(pos - 1);
    }
    int get (int pos) {
        int ans = 0;
        while (pos > 0) {
            ans = add(ans, fenw[pos]);
            pos -= (pos & -pos);
        }
        return ans;
    }
};

unordered_map<int, vector<int>> q_y, q_x, q_sum;
unordered_map<int, unordered_map<int, int>> m_y, m_x, m_sum;
unordered_map<int, fenwick_tree> f_y, f_x, f_sum;

int main(){
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        if (s[i] == 'I') s[i] = 'A';
        else if (s[i] == 'C') s[i] = 'B';
        else s[i] = 'C';
    }
    int cntA = 0, cntB = 0, cntC = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i] == 'A') cntA += 1;
        else if (s[i] == 'B') cntB += 1;
        else cntC += 1;
        x[i] = cntA - cntB;
        y[i] = cntB - cntC;
    }

    for (int i = 0; i <= n; i++) {
        q_y[y[i]].push_back(x[i]);
        q_sum[x[i] + y[i]].push_back(x[i]);
        q_x[x[i]].push_back(y[i]);
    }

    for (int i = -MAXN; i < MAXN; i++) {
        if (q_x.count(i)) normalize(q_x[i], m_x[i]);
        if (q_y.count(i)) normalize(q_y[i], m_y[i]);
        if (q_sum.count(i)) normalize(q_sum[i], m_sum[i]);

        if (q_x.count(i)) {
            int sz = (int)q_x[i].size();
            f_x[i] = fenwick_tree(sz);
        }

        if (q_y.count(i)) {
            int sz = (int)q_y[i].size();
            f_y[i] = fenwick_tree(sz);
        }

        if (q_sum.count(i)) {
            int sz = (int)q_sum[i].size();
            f_sum[i] = fenwick_tree(sz);
        }
    }

    for (int i = 0; i <= n; i++) {
        int X = x[i];
        int Y = y[i];
        int SUM = x[i] + y[i];

        if (i) {
            dp[i] = 0;

            // Getting.
            dp[i] = add(dp[i], f_y[Y].get_smaller(m_y[Y][x[i]])); //
            // printf("dpie %d %d\n", i, dp[i]);
            dp[i] = add(dp[i], f_sum[SUM].get_larger(m_sum[SUM][x[i]]));
            // printf("dpie %d %d\n", i, dp[i]);
            dp[i] = add(dp[i], f_x[X].get_larger(m_x[X][y[i]]));
            // printf("dpie %d %d\n", i, dp[i]);
        } else {
            dp[i] = 1;
        }


        // Updating.
        f_y[Y].upd(m_y[Y][x[i]], dp[i]);
        // printf("here upd: %d + %d\n", m_y[Y][x[i]], dp[i]);
        f_sum[SUM].upd(m_sum[SUM][x[i]], dp[i]);
        f_x[X].upd(m_x[X][y[i]], dp[i]);
    }

    printf("%d\n", dp[n]);
    return 0;
}
