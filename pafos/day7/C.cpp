#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
#define maxN 50'000

int n, m;
int L = 0;
vector<int> g[maxN], g_inv[maxN];
int d[maxN], deg[maxN];

inline void toposort() {
    memset(d, -1, sizeof(d));
    vector<int> q;
    q.clear();
    for (int u = 0; u < n; u++) {
        deg[u] = g[u].size();
        if (deg[u] == 0) {
            q.push_back(u);
            d[u] = 0;
        }
    }
    for (int i = 0; i < (int)q.size(); i++) {
        int u = q[i];
        for (auto v: g_inv[u]) {
            deg[v]--;
            d[v] = max(d[v], d[u]+1);
            if (deg[v] == 0)
                q.push_back(v);
        }
    }
    return;
    printf("d: ");
    for (int i = 0; i < n; i++)
        printf("%d ", d[i]);
    printf("\n");
}


void erase_edge(int u, int v) {
    for (int i = 0; i < g[u].size(); i++)
        if (g[u][i] == v) {
            g[u][i] = g[u][g[u].size()-1];
            g[u].pop_back();
            break;
        }
    for (int i = 0; i < g_inv[v].size(); i++) {
        if (g_inv[v][i] == u) {
            g_inv[v][i] = g_inv[v][g_inv[v].size()-1];
            g_inv[v].pop_back();
            break;
        }
    }
    return;
    for (int u = 0; u < n; u++) {
        printf("%d: ", u+1);
        for (auto v: g[u])
            printf("%d ", v+1);
        printf("\n");
    }
}

tuple<bool, int> go() {
    toposort();

    int u = 0;
    for (int i = 0; i < n; i++)
        if (d[i] > d[u])
            u = i;
    //printf("test: %d %d\n", d[u], L);
    if (d[u] == L)
        return {true, L};

    int len = d[u];
    for (int i = 0; i < len; i++) {
        for (auto v: g[u]) {
            if (d[u] == d[v] + 1) {
                int ans;
                printf("? %d %d\n", u+1, v+1);
                fflush(stdout);
                scanf("%d", &ans);
                if (ans == 0) {
                    erase_edge(u, v);
                    return {false, i};
                }
                u = v;
                break;
            }
        }
    }

    return {true, len};
}

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u-1].push_back(v-1);
        g_inv[v-1].push_back(u-1);
    }

    while (true) {
        auto [passed, len] = go();
        L = max(L, len);
        if (passed) {
            printf("! %d\n", L);
            return 0;
        }


    }


    return 0;
}
