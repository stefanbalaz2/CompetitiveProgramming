#include <bits/stdc++.h>
using namespace std;

void solve_old (int n, int m, int ul, int ur, vector<tuple<int, int>> &bishops) {
    if (n == 1) {
        for (int i = 0; i < m; i++) {
            bishops.push_back({ul, ur + i});
        }
    } else if (m == 1) {
        for (int i = 0; i < n; i++) {
            bishops.push_back({ul + i, ur});
        }
    } else if (n == m) {
        for (int i = 0; i < m; i++) {
            bishops.push_back({ul, ur + i});
        }
        for (int i = 1; i < m - 1; i++) {
            bishops.push_back({ul + n - 1, ur + i});
        }
    } else {
        if (n < m) {
            for (int i = 0; i < n; i++) {
                bishops.push_back({ul + i, ur});
            }
            solve_old(n, m - n, ul, ur + n, bishops);
        } else {
            for (int i = 0; i < m; i++) {
                bishops.push_back({ul, ur + i});
            }
            solve_old(n - m, m, ul + m, ur, bishops);
        }
    }
}

vector<tuple<int, int>> output_smart (int n, int m, vector<tuple<int, int>> bishops) {
    vector<tuple<int, int>> odd, even;
    for (auto [x, y] : bishops) {
        if ((x + y) % 2 == 1) odd.push_back({x, y});
        else even.push_back({x, y});
    }
    // printf("%d %d\n", (int)odd.size(), (int)even.size());
    vector<tuple<int, int>> ret;
    if (odd.size() > even.size()) {
        for (auto [x, y] : odd) {
            ret.push_back({x, y});
            if (n % 2 == 0) ret.push_back({n + 1 - x, y});
            else ret.push_back({x, m + 1 - y});
        }
    } else {
        for (auto [x, y] : even) {
            ret.push_back({x, y});
            if (n % 2 == 0) ret.push_back({n + 1 - x, y});
            else ret.push_back({x, m + 1 - y});
        }
    }
    return ret;
}

int main() {
    int n, m; scanf("%d %d", &n, &m);
    vector<tuple<int, int>> vec;
    if (n % 2 == 0 || m % 2 == 0 || n == m) {
        vector<tuple<int, int>> bishops;
        solve_old(n, m, 1, 1, bishops);
        if (n != m) vec = output_smart(n, m, bishops);
        else vec = bishops;
    } else {
        vector<tuple<int, int>> bishops;
        if (n > m) {
            solve_old(n - m, m, 1, 1, bishops);
            vec = output_smart(n - m, m, bishops);
            for (int i = 1; i <= m; i++) {
                vec.push_back({n, i});
            }
        } else {
            solve_old(n, m - n, 1, 1, bishops);
            vec = output_smart(n, m - n, bishops);
            for (int i = 1; i <= n; i++) {
                vec.push_back({i, m});
            }
        }
    }

    printf("%d\n", (int)vec.size());
    for (auto [x, y] : vec) {
        printf("%d %d\n", x, y);
    }
    return 0;
}
