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

int bsize=300;
const int maxn=1e5+10;
int n;
int a[2][maxn],q;
struct myset{

    vector<int>cnt;
    int sz;
    set<int>ps;

    void init(int n){
    cnt.resize(n);this->sz=n;}

    void insert(int x){
        if(x>n)return;
        cnt[x]++;
        if(cnt[x]==1)ps.insert(x);
    }
    void erase(int x){
        if(x>n)return;
        cnt[x]--;
        if(cnt[x]==0)ps.erase(x);
    }

}st[2];
void build(int c){

    for(int i=1;i<=n;i++){
        for(int j=max(1,i+1);j<=min(n,i+bsize);j++){
            st[c].insert(abs(i-j)*abs(a[c][i]-a[c][j]));
        }
    }

}
void skini(int c,int i,int s){

    for(int j=max(1,i-bsize);j<=min(n,i+bsize);j++){
        if(i==j)continue;
        if(s==j)continue;
        st[c].erase(abs(i-j)*abs(a[c][i]-a[c][j]));
    }

}
void dodaj(int c,int i,int s){

    for(int j=max(1,i-bsize);j<=min(n,i+bsize);j++){
        if(i==j)continue;
        if(s==j)continue;
        st[c].insert(abs(i-j)*abs(a[c][i]-a[c][j]));
    }

}
void promeni(int c,int a1,int b1){

    if(a1>b1)swap(a1,b1);

    skini(c,a1,-1);
    skini(c,b1,a1);

    swap(a[c][a1],a[c][b1]);
    dodaj(c,a1,-1);
    dodaj(c,b1,a1);
}
int get_rez(){

    return min(*st[0].ps.begin(),*st[1].ps.begin());

}
int main(){

    scanf("%d %d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[0][i]);
        a[1][a[0][i]]=i;
    }
    st[0].init(n+1);
    st[1].init(n+1);
    build(0);
    build(1);

    printf("%d\n",get_rez());

    while(q--){

        int l,r;;
        scanf("%d %d",&l,&r);

        promeni(1,a[0][l],a[0][r]);
        promeni(0,l,r);

        printf("%d\n",get_rez());

    }

    return 0;
}
