/*

    idea:   https://codeforces.com/blog/entry/57223

*/
#include<bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
using namespace std;
typedef pair<int,int> pii;

const int maxn=1e5+10;

int start[maxn],kraj[maxn],dp[18][maxn],niz[maxn],tim,level[maxn],n,sz[maxn];
vector<int>vect[maxn];
ll tree[maxn*4],lazy[maxn*4],a[maxn],sum;

void dfs(int x,int prv,int lvl){

    dp[0][x]=prv;
    niz[++tim]=x;
    start[x]=tim;
    level[x]=lvl;
    sz[x]=1;
    for(int i=0;i<vect[x].size();i++){

        int id=vect[x][i];
        if(id==prv)continue;

        dfs(id,x,lvl+1);
        sz[x]+=sz[id];
    }
    kraj[x]=tim;
}
void build(int x,int l,int r){

    if(l==r){
        tree[x]=a[niz[l]];
        return;
    }

    int mid=(l+r)/2;
    build(x*2,l,mid);
    build(x*2+1,mid+1,r);

    tree[x]=tree[x*2]+tree[x*2+1];
}

void push(int x,ll l,ll mid,ll r){

    if(lazy[x]==0)return;

    lazy[x*2]+=lazy[x];
    lazy[x*2+1]+=lazy[x];

    tree[x*2]+=((ll)mid-l+1)*lazy[x];
    tree[x*2+1]+=((ll)r-mid)*lazy[x];

    lazy[x]=0;
}
void update(int x,int l,int r,int lp,int rp,ll val){

    if(l>rp || r<lp)return;
    if(l>=lp && r<=rp){
        tree[x]+=((ll)r-l+1)*val;
        lazy[x]+=val;
        return;
    }

    int mid=(l+r)/2;
    push(x,l,mid,r);

    update(x*2,l,mid,lp,rp,val);
    update(x*2+1,mid+1,r,lp,rp,val);

    tree[x]=tree[x*2]+tree[x*2+1];
}
ll query(int x,int l,int r,int lp,int rp){

    if(l>rp || r<lp)return 0;
    if(l>=lp && r<=rp)return tree[x];

    int mid=(l+r)/2;
    push(x,l,mid,r);

    return query(x*2,l,mid,lp,rp)+query(x*2+1,mid+1,r,lp,rp);
}

void prek(){

    int h=log2(n);
    for(int i=1;i<=h;i++)
        for(int j=1;j<=n;j++)
            dp[i][j]=dp[i-1][dp[i-1][j]];

    build(1,1,n);
}

int lca(int x,int y){

    if(level[x]<level[y])swap(x,y);

    int h=log2(n);
    for(int i=h;i>=0;i--){
        if(level[dp[i][x]]<level[y])continue;
        x=dp[i][x];
    }

    if(x==y)return x;

    for(int i=h;i>=0;i--){
        if(dp[i][x]==dp[i][y])continue;
        x=dp[i][x];
        y=dp[i][y];
    }

    return dp[0][x];
}
int inSubtree(int x,int y){
    if(start[y]<=start[x] && kraj[y]>=start[x])return 1;
    return 0;
}

int lca(int r,int x,int y){

    int l1=lca(r,x);
    int l2=lca(r,y);

  ///  printf("%d %d %d %d L!L!L\n",l1,l2,x,y);

    if(l1==l2)return lca(x,y);

    int is1=inSubtree(x,r);
    int is2=inSubtree(y,r);

    if(is1^is2)return r;

    if(level[l1]>level[l2])return l1;
    else return l2;

}

int oneLess(int x,int r){

    int h=log2(n);

    for(int i=h;i>=0;i--){
        if(level[dp[i][r]]<=level[x])continue;
        r=dp[i][r];
    }

    return r;
}

void up(int r,int x,ll val){

    /// full update
    if(x==r){sum+=val;return;}

    if(inSubtree(x,r) || lca(r,x)!=x){/// normal update
        update(1,1,n,start[x],kraj[x],val);
    }
    else{/// inverse update
        x=oneLess(x,r);
       /// printf("%d %d %d DOSAO\n",x,start[x],kraj[x]);
        sum+=val;
        update(1,1,n,start[x],kraj[x],-val);

       /// printf("%lld AADSA\n",query(1,1,n,1,n));
    }
}

ll qq(int r,int x){

    /// full tree
    if(r==x)return sum*n+query(1,1,n,1,n);

    /// normal query
    ///printf("%d %d %d AAA\n",inSubtree(x,r),lca(x,r),x);
    if(inSubtree(x,r) || lca(x,r)!=x)return sum*sz[x]+query(1,1,n,start[x],kraj[x]);

    /// inverse query
   /// printf("%lld %lld | %d %lld\n",sum,query(1,1,n,1,n),sz[x],query(1,1,n,start[x],kraj[x]));
    x=oneLess(x,r);
    return sum*(ll)n+query(1,1,n,1,n)-(sum*sz[x]+query(1,1,n,start[x],kraj[x]));

}

int main(){

    ///freopen("test.txt","r",stdin);

    int q;
    int root=1;
    scanf("%d %d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }

    for(int i=1;i<n;i++){

        int u,v;
        scanf("%d %d",&u,&v);
        vect[u].pb(v);
        vect[v].pb(u);
    }

    dfs(1,0,1);
    prek();

    while(q--){

        int tip;
        scanf("%d",&tip);

        if(tip==1){

            int v;
            scanf("%d",&v);
            root=v;

        }
        else if(tip==2){

            int u,v;
            ll x;
            scanf("%d %d %lld",&u,&v,&x);

            ///printf("%d %d %d %lld DSA\n",root,u,v,x);
            int l=lca(root,u,v);
            up(root,l,x);

        }
        else{

            int u;
            scanf("%d",&u);

            printf("%lld\n",qq(root,u));
        }

    }


    return 0;
}
