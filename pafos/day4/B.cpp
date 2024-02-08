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

const int maxn=5e5+10;
ll tree[maxn*4],lazy[maxn*4],dp[maxn];
vector<pair<pii,int>>vect[2][maxn];

void build(int x,int l,int r){
    tree[x]=0;
    lazy[x]=0;
    if(l==r){
        tree[x]=0;
        return;
    }
    int mid=(l+r)/2;
    build(x*2,l,mid);
    build(x*2+1,mid+1,r);
    tree[x]=max(tree[x*2],tree[x*2+1]);
}
void push(int x){
    if(lazy[x]==0)return;

    tree[x*2]+=lazy[x];
    tree[x*2+1]+=lazy[x];
    lazy[x*2]+=lazy[x];
    lazy[x*2+1]+=lazy[x];

    lazy[x]=0;
}
void update(int x,int l,int r,int lp,int rp,ll val){
    if(l>rp || r<lp)return;
    if(l>=lp && r<=rp){
        tree[x]+=val;
        lazy[x]+=val;
        return;
    }
    int mid=(l+r)/2;
    push(x);
    update(x*2,l,mid,lp,rp,val);
    update(x*2+1,mid+1,r,lp,rp,val);
    tree[x]=max(tree[x*2],tree[x*2+1]);
}
ll inf=1e18;
ll qq(int x,int l,int r,int lp,int rp){
    if(l>rp || r<lp)return -inf;
    if(l>=lp && r<=rp)return tree[x];
    int mid=(l+r)/2;
    push(x);
    return max(qq(x*2,l,mid,lp,rp),qq(x*2+1,mid+1,r,lp,rp));
}

int main(){

    int t;
    scanf("%d",&t);
    while(t--){
        int n,x;
        scanf("%d %d",&n,&x);
        for(int i=0;i<=x;i++){
            vect[0][i].clear();
            vect[1][i].clear();
        }
        for(int i=1;i<=n;i++){
            int l,r,w,p;
            scanf("%d %d %d %d",&l,&r,&w,&p);
            vect[0][l].pb({{w,p},l-1});
            vect[1][r+1].pb({{w,p},l-1});
        }

        multiset<int>st;
        dp[0]=0;
        build(1,0,x);
        ll rez=0;
        for(int i=1;i<=x;i++){

            for(int j=0;j<vect[0][i].size();j++){
                update(1,0,x,0,vect[0][i][j].ss,-vect[0][i][j].ff.ss);
                st.insert(vect[0][i][j].ff.ff);
            }
            for(int j=0;j<vect[1][i].size();j++){
                update(1,0,x,0,vect[1][i][j].ss,vect[1][i][j].ff.ss);
                st.erase(st.find(vect[1][i][j].ff.ff));
            }

            ll c=-inf;
            if(st.size())c=(*st.rbegin());

            dp[i]=c+qq(1,0,x,0,i-1);
            rez=max(rez,dp[i]);
            update(1,0,x,i,i,dp[i]-qq(1,0,x,i,i));

        }

        printf("%lld\n",rez);

    }

    return 0;
}
