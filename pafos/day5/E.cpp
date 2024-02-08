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

const string hidden = "BBRQNKRN";

int matches (string a, string b) {
    int ans = 0;
    for (int i = 0; i < 8; i++) {
        if (a[i] == b[i]) {
            ans += 1;
        }
    }
    return ans;
}

bool is_viable (string s) {
    unordered_map<int, vector<int>> occ;
    int i = 0;
    for (char c : s) {
        occ[c].push_back(i);
        i++;
    }

    bool ok = true;
    if (!(occ['R'][0] <= occ['K'][0] && occ['K'][0] <= occ['R'][1])) ok = false;
    if ((occ['B'][0] + occ['B'][1]) % 2 == 0) ok = false;
    return ok;
}

vector<string> generated;
const int MAGIC = 960;
int in_common[MAGIC][MAGIC];

void gen() {
    string init = "BBNNKQRR";
    sort(init.begin(), init.end());
    do {
        if (is_viable(init)) generated.push_back(init);
    } while (next_permutation(init.begin(), init.end()));
    for (int i = 0; i < MAGIC; i++) {
        for (int j = 0; j < MAGIC; j++) {
            in_common[i][j] = matches(generated[i], generated[j]);
        }
    }
}

int main(){
    gen();
    srand(time(NULL));

    vector<vector<int>> cur_buckets;
    vector<int> al(MAGIC); iota(al.begin(), al.end(), 0);
    cur_buckets.push_back(al);


    vector<int> queries;
    for (int QUERIES = 0; QUERIES < 5; QUERIES++) {
        int best = 0; int best_val = MAGIC + 1;
        for (int i = 0; i < MAGIC; i++) {
            int MAX_OVERALL = 0;
            for (auto bucket : cur_buckets) {
                vector<int> buckets(9, 0);
                for (int x : bucket) {
                    int c = in_common[i][x];
                    buckets[c] += 1;
                }
                int max_in_bucket = *max_element(buckets.begin(), buckets.end());
                MAX_OVERALL = max(MAX_OVERALL, max_in_bucket);
            }

            if (MAX_OVERALL < best_val) {
                best_val = MAX_OVERALL;
                best = i;
            }
        }

        printf("%d -> %d\n", best, best_val);
        queries.push_back(best);

        // should split all the buckets
        vector<vector<int>> new_cur_buckets;
        for (auto vec : cur_buckets) {
            vector<vector<int>> mini_buckets(9);
            for (int x : vec) {
                int c = in_common[best][x];
                mini_buckets[c].push_back(x);
            }

            for (int i = 0; i <= 8; i++) {
                if (!mini_buckets[i].empty()) {
                    new_cur_buckets.push_back(mini_buckets[i]);
                }
            }
        }

        cur_buckets = new_cur_buckets;
        printf("BEST: %d\n", best);
        int mx_bucket = 0;
        for (auto x : cur_buckets) {
            mx_bucket = max(mx_bucket, (int)x.size());
        }
        printf("MAX BUCKET: %d\n", mx_bucket);
        if (mx_bucket == 1) {
            exit(0);
        }
    }


    return 0;
}
