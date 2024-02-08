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

vector<vector<short>> precalc;
vector<vector<int>> precalc2;

vector<string> grid;

int x, y, z;
int a, b;

void psdrand (int ans, int n) {
    a = ((ll)a * x + (ll)ans * y + z) % n + 1;
    b = ((ll)b * y + (ll)ans * z + x) % n + 1;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, m; cin >> n >> m;
    grid.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    int k; cin >> k;
    cin >> x >> y >> z;
    a = 1; b = n;

    const int MAGIC = 50;
    ll ANSWER = 0;
    if (m <= MAGIC) {
        vector<vector<int>> precalc_col;
        for (int i = 0; i < m; i++) {
            vector<int> cur(n + 1, 0);
            for (int j = 1; j <= n; j++) {
                cur[j] = cur[j - 1];
                if (grid[j - 1][i] == '1') cur[j] += 1;
            }
            precalc_col.push_back(cur);
        }

        for (int i = 0; i < k; i++) {
            int l = min(a, b), r = max(a, b);
            // cerr << l << " " << r << endl;
            int cnt = r - l + 1;
            int ans = 0;
            for (int j = 0; j < m; j++) {
                int d = precalc_col[j][r] - precalc_col[j][l - 1];
                if (d == 0 || d == cnt) {
                    ans += 1;
                }
            }
            // cerr << ans << endl;
            ANSWER += ans;
            psdrand(ans, n);
        }
    } else {
        vector<vector<int>> precalc_col;
        for (int i = 0; i < m; i++) {
            // for each column
            vector<int> cur(n);
            cur[n - 1] = 1;
            for (int j = n - 2; j >= 0; j--) {
                if (grid[j][i] == grid[j + 1][i]) {
                    cur[j] = cur[j + 1] + 1;
                } else {
                    cur[j] = 1;
                }
            }
            precalc_col.push_back(cur);
        }

        /*for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d", precalc_col[j][i]);
            }
            printf("\n");
        }*/

        if (m >= 50000) {
            precalc2.resize(n);
            for (int i = 0; i < n; i++) {
                precalc2[i].resize(n - i);
                vector<int> hm(n, 0);
                int cur = m;
                for (int j = 0; j < m; j++) {
                    int c = precalc_col[j][i];
                    if (i + c < n) hm[i + c] += 1;
                }
                for (int j = i; j < n; j++) {
                    cur -= hm[j];
                    precalc2[i][j - i] = cur;
                }
            }
            for (int i = 0; i < k; i++) {
                int l = min(a, b), r = max(a, b);
                // cerr << l << " " << r << endl;
                int ans = precalc2[l - 1][r - l];
                ANSWER += ans;
                psdrand(ans, n);
            }
        } else {
            precalc.resize(n);
            for (int i = 0; i < n; i++) {
                precalc[i].resize(n - i);
                vector<int> hm(n, 0);
                int cur = m;
                for (int j = 0; j < m; j++) {
                    int c = precalc_col[j][i];
                    if (i + c < n) hm[i + c] += 1;
                }
                for (int j = i; j < n; j++) {
                    cur -= hm[j];
                    precalc[i][j - i] = cur;
                }
            }

            /*for (int i = 0; i < n; i++) {
                for (int j = 0; j < (int)precalc[i].size(); j++) {
                    printf("%hu ", precalc[i][j]);
                }
                printf("\n");
            }*/

            for (int i = 0; i < k; i++) {
                int l = min(a, b), r = max(a, b);
                // cerr << l << " " << r << endl;
                int ans = precalc[l - 1][r - l];
                ANSWER += ans;
                psdrand(ans, n);
            }
        }
    }
    cout << ANSWER << endl;
    return 0;
}
