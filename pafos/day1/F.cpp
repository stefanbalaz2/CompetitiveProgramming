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

const int MAXN = 505;
char init[MAXN][MAXN], fin[MAXN][MAXN];

vector<pii> rott (vector<pii> points) {
    vector<pii> ret;
    for (auto pr : points) {
        ret.push_back({-pr.second, pr.first});
    }
    return ret;
}

const int MAX_COMP = 3005;
const int SHIFT = 1002;
bool has[MAX_COMP][MAX_COMP];

void dbg_print (vector<pii> a) {
    for (auto pr : a) {
        printf("(%d %d) ", pr.first, pr.second);
    }
    printf("\n");
}

void rot2 (int &x, int &y) {
    int tmp = x;
    x = -y;
    y = tmp;
}
void try_match (const vector<pii> &in, const vector<pii> &out, pii shift, int rots) {
    // printf("trying shift (%d, %d)\n", shift.first, shift.second);
    for (auto pr : out) {
        has[pr.first + SHIFT][pr.second + SHIFT] = true;
    }
    int matches = 0;
    int unmatched_i = 0, unmatched_j = 0;
    for (auto pr : in) {
        int i = pr.first + shift.first, j = pr.second + shift.second;
        if (has[i + SHIFT][j + SHIFT]) {
            has[i + SHIFT][j + SHIFT] = false;
            matches += 1;
        } else {
            unmatched_i = pr.first;
            unmatched_j = pr.second;
        }
    }

    int found_i = -1, found_j = -1;
    for (auto pr : out) {
        if (has[pr.first + SHIFT][pr.second + SHIFT]) {
            found_i = pr.first;
            found_j = pr.second;
        }
        has[pr.first + SHIFT][pr.second + SHIFT] = false;
    }

    if (matches == (int)in.size() - 1) {
        found_i -= shift.first; found_j -= shift.second;
        for (int i = 0; i < 4 - rots; i++) {
            rot2(unmatched_i, unmatched_j);
            rot2(found_i, found_j);
        }
        printf("%d %d\n%d %d\n", unmatched_j, unmatched_i, found_j, found_i);
        exit(0);
    }
}

int main(){
    int h, w; scanf("%d %d", &h, &w);
    for (int i = 0; i < h; i++) {
        scanf("%s", init[i]);
    }
    int H, W; scanf("%d %d", &H, &W);
    for (int i = 0; i < H; i++) {
        scanf("%s", fin[i]);
    }
    vector<pii> input_st, input_fin;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (init[i][j] == 'o') {
                input_st.push_back({i, j});
            }
        }
    }
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (fin[i][j] == 'o') {
                input_fin.push_back({i, j});
            }
        }
    }

    int N = (int)input_st.size();
    for (int rot = 0; rot < 4; rot++) {
        vector<pii> current_stuff = input_st;
        sort(current_stuff.begin(), current_stuff.end());

        vector<pii> possible_shifts;

        for (int i = 0; i < min(3, N); i++) {
            for (int j = 0; j < min(3, N); j++) {
                possible_shifts.push_back({input_fin[i].first - current_stuff[j].first, input_fin[i].second - current_stuff[j].second});
            }
        }

        for (auto possible_shift : possible_shifts) {
            try_match(input_st, input_fin, possible_shift, rot);
        }

        input_st = rott(input_st);
    }

    assert(false);
    return 0;
}
