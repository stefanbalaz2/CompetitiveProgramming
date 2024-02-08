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

int cur_a = 0, cur_b = 0, cur_c = 0, cur_d = 0;
const int LENGTH = 20;

int a1[30],a2[30];
int main(){
    int LENGTH = 20;
    set<pair<pii,pii>>st;
    for (int mask = 0; mask < (1 << LENGTH); mask++) {

        int curr=0;
        for(int i=0;i<LENGTH/2;i++){

            if(mask&(1<<i)){
                a1[curr]=1;
                a1[curr+1]=1;
            }
            else{
                a1[curr]=0;
                a1[curr+1]=0;
            }

            curr+=2;
        }

        curr=1;
        for(int i=LENGTH/2;i<LENGTH;i++){

            if(mask&(1<<i)){
                a2[curr]=1;
                a2[(curr+1)%LENGTH]=1;
            }
            else{
                a2[curr]=0;
                a2[(curr+1)%LENGTH]=0;
            }

            curr+=2;
            curr%=LENGTH;
        }

        pair<pii,pii>pom={{0,0},{0,0} };

        for(int i=0;i<LENGTH;i++){
            if(a1[i]==0 && a2[i]==0)pom.ff.ff++;
            if(a1[i]==0 && a2[i]==1)pom.ff.ss++;
            if(a1[i]==1 && a2[i]==0)pom.ss.ff++;
            if(a1[i]==1 && a2[i]==1)pom.ss.ss++;
        }

        st.insert(pom);

    }

    for(set<pair<pii,pii>>::iterator it=st.begin();it!=st.end();it++){

        printf("%d %d %d %d\n",(*it).ff.ff,(*it).ff.ss,(*it).ss.ff,(*it).ss.ss);

    }


    return 0;
}
