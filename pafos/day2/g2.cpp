#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;

const int mod=1000000007;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int MAXN = 2005;
const int MAXLEN = 205;
const int ALPHA = 26;

struct trie {
    int child_cnt = 0;
    int last_idx = 0;
    trie *child[ALPHA];
    bool is_end = false;
};

struct compressed_trie {
    vector<string> transitions;
    vector<int> lengths;
    vector<compressed_trie*> children;
    vector<int> dp; vector<bool> can;
};

void add (trie* root, string s) {
    trie* cur = root;
    for (int i = 0; i < s.length(); i++) {
        if (cur -> is_end) return;
        int let = s[i] - 'a';
        if (cur -> child[let] == nullptr) {
            cur -> child_cnt += 1;
            cur -> child[let] = new trie();
            cur -> last_idx = let;
        }
        cur = cur -> child[let];
    }
    cur -> is_end = true;
}

compressed_trie* compress_trie(trie* cur) {
    compressed_trie* ret = new compressed_trie();
    // cout << "making compresed trie" << endl;
    for (int i = 0; i < 26; i++) {
        if (cur -> child[i]) {
            // find an edge, and add it accordingly
            string cur_str = "";
            cur_str.push_back('a' + i);
            trie* t = cur -> child[i];
            while (t -> child_cnt == 1) {
                int who = t -> last_idx;
                cur_str.push_back('a' + who);
                t = t -> child[who];
            }
            ret -> transitions.push_back(cur_str);
            ret -> lengths.push_back((int)cur_str.length());
            ret -> children.push_back(compress_trie(t));
        }
    }
    return ret;
}

void print_compressed(compressed_trie *cur, string cur_so_far = "") {
    int n = (int)cur -> transitions.size();
    cout << "Node: " << cur_so_far << " " << n << endl;
    for (int i = 0; i < n; i++) {
        print_compressed(cur -> children[i], cur_so_far + cur -> transitions[i]);
    }
}

void print_compressed_dp(compressed_trie *cur, string cur_so_far = "") {
    int n = (int)cur -> transitions.size();
    cout << "Node: " << cur_so_far << " " << n << " dp size " << cur -> dp.size() << endl;
    cout << "Dp: "; for (int x : cur -> dp) cout << x << " "; cout << endl;
    for (int i = 0; i < n; i++) {
        print_compressed_dp(cur -> children[i], cur_so_far + cur -> transitions[i]);
    }
}

void print_trie(trie *cur, string cur_so_far = "") {
    cout << "Node: " << cur_so_far << endl;
    for (int i = 0; i < 26; i++) {
        if (cur -> child[i]) {
            string tmp_s = cur_so_far;
            tmp_s.push_back('a' + i);
            print_trie(cur -> child[i], tmp_s);
        }
    }
}

vector<bool> merge_cans (const vector<bool> &dp1, const vector<bool> &dp2) {
    int n1 = (int)dp1.size();
    int n2 = (int)dp2.size();
    vector<bool> ret(n1 + n2 - 1, false);
    for (int i = 0; i < (int)ret.size(); i++) {
        for (int j = 0; j < n1; j++) {
            if (i - j >= 0 && i - j < n2) {
                ret[i] =  ret[i] || (dp1[j] && dp2[i - j]);
            }
        }
    }
    return ret;
}

vector<int> merge_dps (const vector<int> &dp1, const vector<int> &dp2) {
    int n1 = (int)dp1.size();
    int n2 = (int)dp2.size();
    vector<int> ret(n1 + n2 - 1, 0);
    for (int i = 0; i < (int)ret.size(); i++) {
        for (int j = 0; j < n1; j++) {
            if (i - j >= 0 && i - j < n2) {
                ret[i] = add(ret[i], mul(dp1[j], dp2[i - j]));
            }
        }
    }
    return ret;
}

void dfs (compressed_trie *root, int parent_length = 1) {

    int n = (int)root -> children.size();

    // cout << "doing dfs " << n << endl;
    // assert (n == 0 or n > 1);

    if (n == 0) {
        root -> dp.resize(2);
        root -> dp[0] = 0;
        root -> dp[1] = parent_length;

        root -> can.resize(2);
        root -> can[0] = false;
        root -> can[1] = parent_length > 0;
        return;
    }

    vector<int> dp_cur(1);
    dp_cur[0] = 1;

    vector<bool> can_cur(1);
    can_cur[0] = true;

    for (int i = 0; i < n; i++) {
        dfs(root -> children[i], root -> lengths[i]);
        dp_cur = merge_dps(dp_cur, root -> children[i] -> dp);
        can_cur = merge_cans(can_cur, root -> children[i] -> can);
        // root -> children[i] -> dp.clear();
    }



    // assert (dp_cur[1] == 0);
    dp_cur[1] = parent_length;
    can_cur[1] = parent_length > 0;

    root -> dp = dp_cur;
    root -> can = can_cur;
}

void reconstruct (compressed_trie *root, int m, string cur_so_far = "") {
    int n = (int)root -> children.size();

    if (m == 1) {
        cout << cur_so_far << endl;
        return;
    }

    vector<vector<bool>> prefix_cans;

    vector<bool> can_cur(1);
    can_cur[0] = true;

    prefix_cans.push_back(can_cur);
    for (int i = 0; i < n - 1; i++) {
        can_cur = merge_cans(can_cur, root -> children[i] -> can);
        prefix_cans.push_back(can_cur);
    }

    for (int i = n - 1; i >= 1; i--) {
        auto prev_can = prefix_cans[i];
        for (int takes = 1; takes < min(m + 1, (int)root -> children[i] -> can.size()); takes++) {
            if (prev_can[m - takes] && root -> children[i] -> can[takes]) {
                // cout << "can go to " << i << " and take " << takes << endl;
                reconstruct(root -> children[i], takes, cur_so_far + root -> transitions[i]);
                m -= takes;
                break;
            }
        }
    }

    // assert (m > 0);
    reconstruct(root -> children[0], m, cur_so_far + root -> transitions[0]);
}
int main(){
    freopen("test.txt","r",stdin);

    int N, M;
    cin >> N >> M;
    vector<string> input(N);
    for (int i = 0; i < N; i++) {
        cin >> input[i];
    }
    sort(input.begin(), input.end());

    trie* root = new trie();
    for (int i = 1; i <= N; i++) {
        add(root, input[i - 1]);
    }

    compressed_trie *comp_root = compress_trie(root);
    // print_compressed(comp_root);

    string start = "";
    while (comp_root -> children.size() == 1) {
        start += comp_root -> transitions[0];
        comp_root = comp_root -> children[0];
    }

    // cerr << "start: " << start << endl;

    // cerr << "LALA" << endl;

    dfs(comp_root, (int)start.length());
    // print_compressed_dp(comp_root);

    // cerr << "LALA" << endl;

    if (M >= comp_root->dp.size()) {
        cout << "0\n";
        return 0;
    }
    int ans = comp_root -> dp[M];
    cout << ans << endl;

    if (comp_root -> can[M]) reconstruct(comp_root, M, start);

    return 0;
}
