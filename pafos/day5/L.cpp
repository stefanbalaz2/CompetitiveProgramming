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

char temp[10];

char input[55], output[55];
void prepare() {
    int t; scanf("%d", &t);
    while (t--) {
        scanf("%s", input);
        vector<bool> has(25, false);
        for (int i = 0; i < 50; i++) {
            int here = input[i] - 'A';
            if (has[here]) output[i] = '1';
            else output[i] = '0';
            has[here] = true;
        }
        output[50] = '\0';
        printf("%s\n", output);
        fflush(stdout);
    }
}
void play() {
    int t; scanf("%d", &t);
    while (t--) {
        scanf("%s", input);
        vector<int> a, b;
        for (int i = 0; i < 50; i++) {
            if (input[i] == '0') a.push_back(i + 1);
            else b.push_back(i + 1);
        }
        // printf("a is: "); for (auto p : a) printf("%d ", p); printf("\n");
        // printf("b is: "); for (auto p : b) printf("%d ", p); printf("\n");
        vector<int> where_b(25, -1);
        for (int i = 0; i < 24; i += 2) {
            // printf("cur i %d\n", i);
            printf("%d\n", b[i]);
            fflush(stdout);
            scanf("%s", input);
            int what = input[0] - 'A';
            where_b[what] = b[i];
            printf("%d\n", b[i + 1]);
            fflush(stdout);
            scanf("%s", input);
            what = input[0] - 'A';
            where_b[what] = b[i + 1];
        }
        int what_empty = -1;
        for (int i = 0; i < 25; i++) {
            if (where_b[i] == -1) {
                what_empty = i;
                break;
            }
        }
        where_b[what_empty] = b[24];

        for (int i = 0; i < 25; i++) {
            printf("%d\n", a[i]);
            fflush(stdout);
            scanf("%s", input);
            int what = input[0] - 'A';

            printf("%d\n", where_b[what]);
            fflush(stdout);

            scanf("%s", input);
            if (i < 24) assert(input[1] == '+');
            else assert(input[1] == '!');
        }
    }
}
int main(){
    scanf("%s", temp);
    if (temp[1] == 'r') prepare();
    else play();
    return 0;
}
