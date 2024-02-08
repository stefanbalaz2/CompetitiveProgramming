#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define mid (left+right)/2
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

const int MAXN = 1000010;
int a[MAXN];
pii q[MAXN];

int seg[MAXN << 2];
int lazy[MAXN << 2];

void push (int idx) {
    if (lazy[idx] != 0) {
        seg[idx*2] += lazy[idx];
        seg[idx*2+1] += lazy[idx];
        lazy[2 * idx] += lazy[idx];
        lazy[2 * idx + 1] += lazy[idx];
        lazy[idx] = 0;
    }
}

void update (int idx, int left, int right, int l, int r, int val) {
    if (r < left || l > right) return;
    if (l <= left && right <= r) {
        lazy[idx] += val;
        seg[idx]+=val;
        return;
    }
    push(idx);
    update(idx * 2, left, mid, l, r, val);
    update(idx * 2 + 1, mid + 1, right, l, r, val);
    seg[idx] = max(seg[idx * 2], seg[idx * 2 + 1]);
}

int query (int idx, int left, int right, int l, int r) {
    if (r < left || l > right) return 0;
    if (l <= left && right <= r) {
        return seg[idx];
    }
    push(idx);
    int ans = 0;
    ans = max(ans, query(idx * 2, left, mid, l, r));
    ans = max(ans, query(idx * 2 + 1, mid + 1, right, l, r));
    return ans;
}


int ITS;
int L[MAXN], R[MAXN];
int get_l (int x) {
    int pos = lower_bound(R + 1, R + ITS + 1, x) - (R);
    return pos;
}

int get_r (int x) {
    int pos = upper_bound(L + 1, L + ITS + 1, x) - (L) - 1;
    return pos;
}

int n; int qq;
void input() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    scanf("%d", &qq);
    for (int i = 1; i <= qq; i++) scanf("%d %d", &q[i].first, &q[i].second);
}

long long solve_smart() {
    sort(q + 1, q + qq + 1, [](pii a, pii b) { if (a.first == b.first) return a.second > b.second; return a.first < b.first; });
    int cur_r = q[1].second;
    vector<bool> in(qq + 1); in[1] = true;

    for (int i = 2; i <= qq; i++) {
        if (q[i].second <= cur_r) {
            in[i] = false;
        } else {
            in[i] = true;
            cur_r = q[i].second;
        }
    }

    ITS = 0;
    vector<pair<int, int>> its;
    for (int i = 1; i <= qq; i++) {
        if (in[i]) {
            // printf("%d -> %d\n", q[i].first, q[i].second);
            ITS += 1;
            L[ITS] = q[i].first;
            R[ITS] = q[i].second;
            its.push_back(q[i]);
        }
    }

    vector<pair<int, int>> occ;
    for (int i = 1; i <= n; i++) {
        occ.push_back({a[i], i});
    }

    sort(occ.begin(), occ.end());
    reverse(occ.begin(), occ.end());

    long long answer = 0;
    for (auto pr : occ) {
        int val = pr.first, pos = pr.second;
        int l = get_l(pos);
        int r = get_r(pos);
        if (l > r) continue;
        int cnt = query(1, 1, ITS, l, r);
        answer = max(answer, 1ll * val * cnt);
        update(1, 1, ITS, l, r, 1);
    }
    return answer;
}

long long solve_brute() {
    ll ans = 0;
    for (int i = 1; i <= qq; i++) {
        int l = q[i].first, r = q[i].second;
        ll cur = 0;
        for (int m = l; m <= r; m++) {
            int cnt_larger = 0;
            for (int j = l; j <= r; j++) {
                if (a[j] > a[m]) cnt_larger += 1;
            }
            cur = max(cur, 1ll * cnt_larger * a[m]);
        }
        ans = max(ans, cur);
    }
    return ans;
}

void gen() {
    n = 10;
    srand(time(NULL));
    for (int i = 1; i <= n; i++) {
        a[i] = rand() % 1000000000 + 1;
    }
    qq = 10;
    for (int i = 1; i <= qq; i++) {
        int l = rand() % n + 1;
        int r = rand() % n + 1;
        if (l > r) swap(l, r);
        q[i] = {l, r};
    }

    printf("%d\n", n);
    for (int i = 1; i <= n; i++) printf("%d ", a[i]); printf("\n");
    printf("%d\n", qq);
    for (int i = 1; i <= n; i++) {
        printf("%d %d\n", q[i].first, q[i].second);
    }
}

int main(){

    input();
    //gen();

    ll ans = solve_smart();
    printf("%lld\n", ans);

    /*ll brute = solve_brute();
    printf("%lld\n", brute);*/

    return 0;
}
