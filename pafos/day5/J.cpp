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

const int MAXN = 105;
int x[MAXN], y[MAXN];
int get_dist (int px, int py, int plus_id) {
    return min(abs(px - x[plus_id]), abs(py - y[plus_id]));
}

double euclid (double px, double py, double ex, double ey) {
    return sqrt((px - ex) * (px - ex) + (py - ey) * (py - ey));
}

pair<int, int> find_enter (int px, int py, int id) {
    if (abs(px - x[id]) < abs(py - y[id])) return {x[id], py};
    else return {px, y[id]};
}

void reconstruct (int px, int py, vector<int> ans_vec, int ex, int ey) {
    int n = (int)ans_vec.size();
    if (n == 0) {
        printf("1\n");
        printf("0 %d %d\n", ex, ey);
    } else if (n == 1) {
        printf("3\n");
        pair<int, int> enter_pos = find_enter(px, py, ans_vec[0]);
        pair<int, int> exit_pos = find_enter(ex, ey, ans_vec[0]);
        printf("0 %d %d\n", enter_pos.first, enter_pos.second);
        printf("%d %d %d\n", ans_vec[0] + 1, exit_pos.first, exit_pos.second);
        printf("0 %d %d\n", ex, ey);
    } else {
        printf("4\n");
        pair<int, int> enter_pos = find_enter(px, py, ans_vec[0]);
        pair<int, int> exit_pos = find_enter(ex, ey, ans_vec[1]);
        pair<int, int> intersection = {x[ans_vec[0]], y[ans_vec[1]]};
        printf("0 %d %d\n", enter_pos.first, enter_pos.second);
        printf("%d %d %d\n", ans_vec[0] + 1, intersection.first, intersection.second);
        printf("%d %d %d\n", ans_vec[1] + 1, exit_pos.first, exit_pos.second);
        printf("0 %d %d\n", ex, ey);
    }
}

int main(){
    int n_pluses, t;
    scanf("%d %d", &n_pluses, &t);
    int x_start, y_start, x_end, y_end;
    scanf("%d %d %d %d", &x_start, &y_start, &x_end, &y_end);

    for (int i = 0; i < n_pluses; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }

    double ans = euclid(x_start, y_start, x_end, y_end);
    vector<int> ans_vec;

    // Trying to use a single plus.
    for (int i = 0; i < n_pluses; i++) {
        double dist = get_dist(x_start, y_start, i) + t + get_dist(x_end, y_end, i);
        if (dist < ans) {
            ans = dist;
            ans_vec = {i};
        }
    }

    // Trying to use two pluses.
    for (int i = 0; i < n_pluses; i++) {
        for (int j = 0; j < n_pluses; j++) {
            if (i == j) continue;
            double dist = get_dist(x_start, y_start, i) + t + t + get_dist(x_end, y_end, j);
            if (dist < ans) {
                ans = dist;
                ans_vec = {i, j};
            }
        }
    }

    printf("%.10f\n", ans);
    reconstruct(x_start, y_start, ans_vec, x_end, y_end);
    return 0;
}
