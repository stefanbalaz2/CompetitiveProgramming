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

const int maxn=3e5+10;
ll tree[maxn*4],lazy[maxn*4],inf=2e18,tree2[maxn*4],a[maxn],b[maxn];
int n,m,lb[maxn],rb[maxn],c;
void build(int x,int l,int r){

    lazy[x]=inf;
    tree[x]=inf;
    tree2[x]=inf;
    if(l==r){
        return;
    }
    int mid=(l+r)/2;
    build(x*2,l,mid);
    build(x*2+1,mid+1,r);

}
void push(int x){

    if(lazy[x]==inf)return;

    tree[x*2]=lazy[x];
    tree[x*2+1]=lazy[x];
    tree2[x*2]=lazy[x];
    tree2[x*2+1]=lazy[x];
    lazy[x*2]=lazy[x];
    lazy[x*2+1]=lazy[x];

    lazy[x]=inf;

}
void update(int x ,int l,int r,int lp,int rp,ll val){

    ///printf("%d %d | %lld %lld \n",l,r,val,tree2[x]);
    if(l>rp || r<lp || tree2[x]<=val)return;
    if(l>=lp && r<=rp && tree[x]>=val){
        tree[x]=val;
        lazy[x]=val;
        tree2[x]=val;
        return;
    }
    int mid=(l+r)/2;
    push(x);

    update(x*2,l,mid,lp,rp,val);
    update(x*2+1,mid+1,r,lp,rp,val);
    tree[x]=min(tree[x*2],tree[x*2+1]);
    tree2[x]=max(tree2[x*2],tree2[x*2+1]);
}
ll qry(int x,int l,int r,int lp,int rp){

    if(l>rp || r<lp)return -inf;
    if(l>=lp && r<=rp)return tree2[x];
    int mid=(l+r)/2;
    push(x);
    return max(qry(x*2,l,mid,lp,rp),qry(x*2+1,mid+1,r,lp,rp));
}

int main(){

    freopen("test.txt","r",stdin);

    int t;
    scanf("%d",&t);
    while(t--){

        scanf("%d %d",&n,&c);
        for(int i=1;i<=n;i++){
            scanf("%d",&lb[i]);
        }
        for(int i=1;i<=n;i++){
            scanf("%d",&rb[i]);
        }
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
        }

        build(1,1,n+1);
        update(1,1,n+1,n+1,n+1,0);

        for(int i=n;i>=1;i--){

            b[i]=qry(1,1,n+1,min(n+1,i+lb[i]),min(i+rb[i],n+1) )+a[i];

            ///printf("%lld %d %lld II\n",b[i],i,qry(1,1,n+1,min(n+1,i+lb[i]),i+rb[i]));

            update(1,1,n+1,i,i+c,b[i]);
        }

        printf("%lld\n",b[1]-a[1]);

    }


    return 0;
}
