#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;
typedef long long ll;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxn=2e5+10;
ll inf=2e18;

struct pt{
    ll val,id;

    pt(){val=id=0;}
    pt(ll val,ll id){
        this->val=val;
        this->id=id;
    }

    bool operator <(const pt &b)const{
        if(val!=b.val)return val>b.val;
        return id<b.id;
    }

    pt operator +(ll x){
        pt ret=(*this);
        ret.val+=x;
        return ret;
    }

    bool operator ==(pt b){
        return (val==b.val)&&(id==b.id);
    }

    void ispis(){
        printf("%lld %lld ISPIS\n",id,val);
    }

};
pt min(pt a,pt b){
    if(a<b)return a;
    return b;
}

struct segtree{

    vector<pt>a;
    vector<ll>lazy;
    int n;

    segtree(){}
    segtree(int n){
        this->n=n;
        a.resize(n*4+10);
        lazy.resize(n*4+10);
    }
    void init(int n){
        this->n=n;
        a.resize(n*4+10);
        lazy.resize(n*4+10);
    }

    void build(int x,int l,int r,vector<pt>&niz){

        lazy[x]=0;
        if(l==r){
            a[x]=niz[l-1];
            return;
        }

        int mid=(l+r)/2;
        build(x*2,l,mid,niz);
        build(x*2+1,mid+1,r,niz);

        a[x]=min(a[x*2],a[x*2+1]);
    }
    void build_ex(vector<pt>&niz){
        init(niz.size());
        build(1,1,n,niz);
    }

    void push(int x){
        if(lazy[x]==0)return;

        a[x*2].val+=lazy[x];
        a[x*2+1].val+=lazy[x];
        lazy[x*2]+=lazy[x];
        lazy[x*2+1]+=lazy[x];

        lazy[x]=0;
    }

    void update(int x,int l,int r,int lp,int rp,ll val){
        if(l>rp || r<lp)return;
        if(l>=lp && r<=rp){
            a[x]=a[x]+val;
            lazy[x]+=val;
            return;
        }
        int mid=(l+r)/2;
        push(x);

        update(x*2,l,mid,lp,rp,val);
        update(x*2+1,mid+1,r,lp,rp,val);

        a[x]=min(a[x*2],a[x*2+1]);
    }
    void update_ex(int l,int r,ll val){
        update(1,1,n,l,r,val);
    }


    void query(int x,int l,int r,int lp,int rp,pt &ret){
        if(l>rp || r<lp)return;
        if(l>=lp && r<=rp){
            if(a[x]<ret)ret=a[x];
            return;
        }
        int mid=(l+r)/2;
        push(x);
        query(x*2,l,mid,lp,rp,ret);
        query(x*2+1,mid+1,r,lp,rp,ret);
    }
    pt query_ex(int l,int r){
        pt ret=pt(-inf,inf);
        query(1,1,n,l,r,ret);
        return ret;
    }


    void postavi(int x,int l,int r,int id,pt val){
        if(l>id || r<id)return;
        if(l==r){
            a[x]=val;
            return;
        }
        int mid=(l+r)/2;
        push(x);
        postavi(x*2,l,mid,id,val);
        postavi(x*2+1,mid+1,r,id,val);
        a[x]=min(a[x*2],a[x*2+1]);
    }
    void postavi_ex(pt val,int x){
        postavi(1,1,n,x,val);
    }


}chains[maxn],genstate,chain_upd;

int n;
ll a[maxn];
vector<pair<int,ll>>vect[maxn];
vector<int>chain_arrays[maxn];
int chain_par[maxn],chain_nxt[maxn],chain_id[maxn],chain_subtree_start[maxn],chain_subtree_end[maxn],chain_h[maxn];
int chain_time=1;
int disc_time=1;
int disc_start[maxn],disc_end[maxn],subtree_sz[maxn],disc_array[maxn];
ll tree_dist[maxn];
int tree_parent[maxn];
pt chain_val_prek[maxn],chain_full_subtree[maxn];

bool sz_sort(pair<int,ll> &x,pair<int,ll> &y){
    return subtree_sz[x.ff]>subtree_sz[y.ff];
}
void dfs0(int x){

    subtree_sz[x]=1;
    disc_array[disc_time]=x;
    disc_start[x]=disc_time++;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i].ff;
        ll w=vect[x][i].ss;
        tree_parent[id]=x;
        tree_dist[id]=tree_dist[x]+w;
        dfs0(id);
        subtree_sz[x]+=subtree_sz[id];
    }
    sort(vect[x].begin(),vect[x].end(),sz_sort);

    disc_end[x]=disc_time-1;

}
void dfs1(int x,int chain_parent){

    chain_par[x]=chain_parent;
    chain_nxt[x]=-1;
    if(chain_parent==-1)chain_id[x]=chain_time++;
    else chain_id[x]=chain_id[chain_parent];

    chain_subtree_start[x]=chain_time;
    chain_arrays[chain_id[x]].pb(x);
    chain_h[x]=chain_arrays[chain_id[x]].size();

    if(vect[x].size()==0){
        chain_nxt[x]=-1;
    }
    else{
        chain_nxt[x]=vect[x][0].ff;
        dfs1(vect[x][0].ff,x);
    }

    for(int i=1;i<vect[x].size();i++){
        int id=vect[x][i].ff;
        dfs1(id,-1);
    }

    chain_subtree_end[x]=chain_time-1;
}
void dfs2(int x){
    pt cval=pt(tree_dist[x]-a[x],x);
    pt cval2=cval;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i].ff;
        dfs2(id);
        if(id!=chain_nxt[x]){
            cval=min(cval,chain_full_subtree[id]);
        }
        cval2=min(cval2,chain_full_subtree[id]);
    }
    chain_val_prek[x]=cval;
    chain_full_subtree[x]=cval2;
}
void go_build(){

    dfs0(1);
    dfs1(1,-1);

    vector<pt>pom;
    for(int i=1;i<=n;i++){
        int id=disc_array[i];
        pom.pb({tree_dist[id]-a[id],id});
    }
    genstate.build_ex(pom);

    pom.clear();
    pom.resize(chain_time,pt(0,0));
    chain_upd.build_ex(pom);

    dfs2(1);

    for(int i=1;i<chain_time;i++){

        pom.clear();
        for(int j=0;j<chain_arrays[i].size();j++){
            int id=chain_arrays[i][j];
            pom.pb(chain_val_prek[id]+(-2*tree_dist[id]));
        }
        chains[i].build_ex(pom);

    }

}


pt recalculate_HLD_node(int x){

    int y=chain_nxt[x];

    pt ret=pt(-inf,inf);

    if(y==-1)ret=genstate.query_ex(disc_start[x],disc_end[x]);
    else{
        ret=genstate.query_ex(disc_start[x],disc_start[y]-1);
        ret=min(ret,genstate.query_ex(disc_end[y]+1,disc_end[x]));
    }

    int cid=chain_id[x];
    pt pom=chain_upd.query_ex(cid,cid);
    ret=ret+(-2*tree_dist[x]);
    ret=ret+(-pom.val);

    return ret;
}
void update_subtree(int x,ll val){

    genstate.update_ex(disc_start[x],disc_end[x],val);
    chain_upd.update_ex(chain_subtree_start[x],chain_subtree_end[x],val);

    int cid=chain_id[x];
    chains[cid].update_ex(chain_h[x],chain_arrays[cid].size(),val);

    x=chain_arrays[cid][0];
    while(1){

        if(tree_parent[x]==0)break;

        x=tree_parent[x];
        cid=chain_id[x];
        chains[cid].postavi_ex(recalculate_HLD_node(x),chain_h[x]);

        x=chain_arrays[cid][0];
    }

}

bool is_in_subtree(int x,int y){
    if(disc_start[y]<=disc_start[x] && disc_end[x]<=disc_end[y])return true;
    return false;
}
pt query_node(int x){

    pt ret=pt(-inf,inf);
    ret=genstate.query_ex(disc_start[x],disc_end[x])+(-2*tree_dist[x]);

    int qn=x;

    int prvx=x;
    x=tree_parent[x];

    while(x!=0){

        if(is_in_subtree(qn,chain_nxt[x])){
            ret=min(ret,chains[chain_id[x]].query_ex(1,chain_h[x])+chain_upd.query_ex(chain_id[x],chain_id[x]).val);
            x=chain_arrays[chain_id[x]][0];
            prvx=x;
            x=tree_parent[x];
        }
        else{

            pt pom=min(genstate.query_ex(disc_start[x],disc_start[prvx]-1),
                       genstate.query_ex(disc_end[prvx]+1,disc_end[x]));
            pom.val-=2*tree_dist[x];

            ret=min(ret,pom);

            prvx=x;
            x=tree_parent[x];

        }

    }

    ret.val+=tree_dist[qn];
    return ret;
}

int main(){

    ///freopen("test.txt","r",stdin);

    int q;
    scanf("%d %d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    for(int i=2;i<=n;i++){
        int p;
        ll v;
        scanf("%d %lld",&p,&v);
        vect[p].pb({i,v});
    }

    go_build();

    int qcnt=0;
    while(q--){

        qcnt++;

        int x,y;
        ll v;
        scanf("%d %d %lld",&x,&y,&v);
        v=-v;
        update_subtree(y,v);


        pt ret=query_node(x);
        printf("%lld %lld\n",ret.id,ret.val);

    }

    return 0;
}
