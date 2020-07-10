/*

    idea: https://codeforces.com/blog/entry/57796

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<ll,int> pii;
const int maxn=1e5+10;
int ind[maxn],n;
ll dp[maxn],a[maxn],b[maxn];
vector<int>vect[maxn];
bool Q;
struct Line{
    mutable ll b,k,inter;

    bool operator <(const Line& a) const{
        return Q?inter<a.inter:k>a.k;
    }
};
struct cht: multiset<Line>{

    ll inf=1e18;

    ll div(ll a,ll b){
        return a/b-((a^b)<0 && (a%b));
    }

    bool inter(iterator x,iterator y){

        if(y==end()){x->inter=inf;return false;}
        if(y->k==x->k){
            if(x->b>=y->b){x->inter=-inf;}
            else {x->inter=inf;}
        }
        else x->inter=div(x->b-y->b,y->k-x->k);

        return x->inter>=y->inter;
    }

    void add(Line a){

        Q=0;

        auto y=insert(a);
        iterator x=y;
        iterator z=y;
        z++;

        while(inter(y,z))z=erase(z);
        if(x!=begin() && inter(--x,y))inter(x,y=erase(y));
        while((y=x)!=begin() && inter(--x,y))inter(x,erase(y));
    }

    ll query(ll x){

        if(size()==0)return 0;

        Q=1;
        Line xx=*lower_bound({0,0,x});
        Q=0;

        return xx.b+xx.k*x;
    }

}st[maxn];
void go(int x,int prv){

    ind[x]=x;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv)continue;
        go(id,x);

        if(st[ind[x]].size()<st[ind[id]].size())swap(ind[x],ind[id]);

        for(auto it=st[ind[id]].begin();it!=st[ind[id]].end();it++)
            st[ind[x]].add(*it);
    }

    dp[x]=st[ind[x]].query(a[x]);
    st[ind[x]].add({dp[x],b[x],0});
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)scanf("%lld",&b[i]);

    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        vect[u].pb(v);
        vect[v].pb(u);
    }

    go(1,0);

    for(int i=1;i<=n;i++){
        printf("%lld ",dp[i]);
    }

	return 0;
}
