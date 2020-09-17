/*

    idea: hld

*/
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ff first
#define ss second
#define ll long long
typedef pair<int,int> pii;
const int maxn=100010;
vector<int>vect[maxn];
int n;
struct hld{

    int sz[maxn],ind[maxn],ind2[maxn],cnt,p[maxn],val[maxn];
    ll subsum[maxn],dist[maxn];
    vector<int>chain[maxn];
    vector<ll>lazy1[maxn],lazy2[maxn],tree1[maxn],tree2[maxn],tree3[maxn],lazy3[maxn],pref[maxn];

    void prek_sz(int x,int prv,ll d){
        sz[x]=1;
        subsum[x]=0;
        dist[x]=d;
        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i];
            if(id==prv)continue;
            prek_sz(id,x,d+1);
            sz[x]+=sz[id];
            subsum[x]+=subsum[id];
            subsum[x]+=(ll)sz[id];
        }
    }

    void prek_chains(int x,int prv){

        p[x]=prv;

        if(ind[x]==-1){
            ind[x]=++cnt;
            ind2[x]=chain[cnt].size();
            chain[cnt].pb(x);
        }

        int maxx=-1;
        int id2=-1;
        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i];
            if(id==prv)continue;

            if(maxx<sz[id]){
                maxx=sz[id];
                id2=id;
            }
        }

        if(id2!=-1){
            ind[id2]=ind[x];
            ind2[id2]=chain[ind[x]].size();
            chain[ind[x]].pb(id2);
        }

        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i];
            if(id==prv)continue;

            prek_chains(id,x);
        }
    }

    void build(){

        cnt=0;
        memset(val,-1,sizeof(val));
        for(int i=1;i<=n;i++){
            chain[i].clear();
            lazy1[i].clear();
            lazy2[i].clear();
            lazy3[i].clear();
            tree1[i].clear();
            tree2[i].clear();
            tree3[i].clear();
            pref[i].clear();
        }
        prek_sz(1,0,0);
        memset(ind,-1,sizeof(ind));
        prek_chains(1,0);

        for(int i=1;i<=cnt;i++){

            lazy1[i].resize(4*(int)chain[i].size());
            lazy2[i].resize(4*(int)chain[i].size());
            tree1[i].resize(4*(int)chain[i].size());
            tree2[i].resize(4*(int)chain[i].size());
            tree3[i].resize(4*(int)chain[i].size());
            lazy3[i].resize(4*(int)chain[i].size());

            pref[i].resize((int)chain[i].size());
            for(int j=0;j<chain[i].size()-1;j++)
                pref[i][j]=sz[chain[i][j+1]];

            pref[i][chain[i].size()-1]=0;

            for(int j=1;j<chain[i].size();j++)
                pref[i][j]+=pref[i][j-1];
        }

    }

    ll get_pref(int l,int r,int ci){
        if(l==0)return pref[ci][r];
        else return pref[ci][r]-pref[ci][l-1];
    }

    void push1(int x,int l,int mid,int r,int ci){
        if(lazy1[ci][x]==0)return;

        tree1[ci][x*2]+=lazy1[ci][x]*(mid-l+1);
        tree1[ci][x*2+1]+=lazy1[ci][x]*(r-mid);
        lazy1[ci][x*2]+=lazy1[ci][x];
        lazy1[ci][x*2+1]+=lazy1[ci][x];

        lazy1[ci][x]=0;
    }

    void up(int x,int l,int r,int lp,int rp,ll val,int ci){

        if(l>rp || r<lp)return;
        if(l>=lp && r<=rp){
            lazy1[ci][x]+=val;
            tree1[ci][x]+=(r-l+1)*val;
            return;
        }
        int mid=(l+r)/2;
        push1(x,l,mid,r,ci);

        up(x*2,l,mid,lp,rp,val,ci);
        up(x*2+1,mid+1,r,lp,rp,val,ci);
        tree1[ci][x]=tree1[ci][x*2]+tree1[ci][x*2+1];
    }

    void push2(int x,int l,int mid,int r,int ci){
        if(lazy2[ci][x]==0)return;

        tree2[ci][x*2]=get_pref(l,mid,ci);
        tree2[ci][x*2+1]=get_pref(mid+1,r,ci);
        lazy2[ci][x*2]=1;
        lazy2[ci][x*2+1]=1;

        lazy2[ci][x]=0;
    }

    void setval(int x,int l,int r,int id,ll val,int ci){
        if(l>id || r<id)return;
        if(l==r){
            tree2[ci][x]=val;
            return;
        }
        int mid=(l+r)/2;
        push2(x,l,mid,r,ci);

        setval(x*2,l,mid,id,val,ci);
        setval(x*2+1,mid+1,r,id,val,ci);
        tree2[ci][x]=tree2[ci][x*2]+tree2[ci][x*2+1];
    }

    void setsw(int x,int l,int r,int lp,int rp,int val,int ci){
        if(l>rp || r<lp)return;
        if(l>=lp && r<=rp){
            lazy2[ci][x]=1;
            tree2[ci][x]=get_pref(l,r,ci);
            return;
        }
        int mid=(l+r)/2;
        push2(x,l,mid,r,ci);

        setsw(x*2,l,mid,lp,rp,val,ci);
        setsw(x*2+1,mid+1,r,lp,rp,val,ci);
        tree2[ci][x]=tree2[ci][x*2]+tree2[ci][x*2+1];
    }

    void push3(int x,int l,int mid,int r,int ci){
        if(lazy3[ci][x]==0)return;

        tree3[ci][x*2]=mid-l+1;
        tree3[ci][x*2+1]=r-mid;
        lazy3[ci][x*2]=1;
        lazy3[ci][x*2+1]=1;

        lazy3[ci][x]=0;
    }

    void setval2(int x,int l,int r,int id,ll val,int ci){
        if(l>id || r<id)return;
        if(l==r){
            tree3[ci][x]=val;
            return;
        }
        int mid=(l+r)/2;
        push3(x,l,mid,r,ci);

        setval2(x*2,l,mid,id,val,ci);
        setval2(x*2+1,mid+1,r,id,val,ci);
        tree3[ci][x]=tree3[ci][x*2]+tree3[ci][x*2+1];
    }

    void setsw2(int x,int l,int r,int lp,int rp,int val,int ci){
        if(l>rp || r<lp)return;
        if(l>=lp && r<=rp){
            lazy3[ci][x]=1;
            tree3[ci][x]=r-l+1;
            return;
        }
        int mid=(l+r)/2;
        push3(x,l,mid,r,ci);

        setsw2(x*2,l,mid,lp,rp,val,ci);
        setsw2(x*2+1,mid+1,r,lp,rp,val,ci);
        tree3[ci][x]=tree3[ci][x*2]+tree3[ci][x*2+1];
    }

    ll qry(int x,int l,int r,int lp,int rp,vector<ll> &tree,int tip,int ci){
        if(l>rp || r<lp)return 0;
        if(l>=lp && r<=rp)return tree[x];
        int mid=(l+r)/2;
        if(tip==1)push1(x,l,mid,r,ci);
        else if(tip==2)push2(x,l,mid,r,ci);
        else push3(x,l,mid,r,ci);
        return qry(x*2,l,mid,lp,rp,tree,tip,ci)+qry(x*2+1,mid+1,r,lp,rp,tree,tip,ci);
    }

    void update(int x){

        ll curr=0;
        ll prvval=0;
        int prvx=0;
        while(x!=0){

            val[x]=prvx;

            up(1,0,(int)chain[ind[x]].size()-1,0,ind2[x],curr,ind[x]);
            ll v1=qry(1,0,chain[ind[x]].size()-1,0,ind2[x],tree2[ind[x]],2,ind[x]);
            setval(1,0,chain[ind[x]].size()-1,ind2[x],prvval,ind[x]);
            setsw(1,0,chain[ind[x]].size()-1,0,ind2[x]-1,1,ind[x]);
            setval2(1,0,chain[ind[x]].size()-1,ind2[x],0,ind[x]);
            setsw2(1,0,chain[ind[x]].size()-1,0,ind2[x]-1,1,ind[x]);
            ll v2=qry(1,0,chain[ind[x]].size()-1,0,ind2[x],tree2[ind[x]],2,ind[x]);

            curr+=v2-v1;
            prvval=sz[chain[ind[x]][0]];

            prvx=chain[ind[x]][0];
            x=p[chain[ind[x]][0]];
        }

    }

    ll qry_path(int x){

        int prvx=x;
        x=p[x];
        ll ret=0;
        while(x!=0){

            if(ind[x]==ind[prvx])ret+=qry(1,0,chain[ind[x]].size()-1,ind2[x],ind2[x],tree3[ind[x]],3,ind[x]);
            else ret+=(prvx==val[x] && prvx!=0 && qry(1,0,chain[ind[x]].size()-1,ind2[x],ind2[x],tree3[ind[x]],3,ind[x])==0);

            ret+=qry(1,0,chain[ind[x]].size()-1,0,ind2[x]-1,tree3[ind[x]],3,ind[x]);

            prvx=chain[ind[x]][0];
            x=p[chain[ind[x]][0]];
        }

        return ret;
    }

    ll query(int x){

        ll pom=dist[x]-qry_path(x);

        return subsum[x]-
               qry(1,0,chain[ind[x]].size()-1,ind2[x],ind2[x],tree1[ind[x]],1,ind[x])-
               qry(1,0,chain[ind[x]].size()-1,ind2[x],chain[ind[x]].size()-1,tree2[ind[x]],2,ind[x])+
               pom*sz[x];
    }

}data;

int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    int t;
    scanf("%d",&t);
    while(t--){

        scanf("%d",&n);
        for(int i=1;i<=n;i++)vect[i].clear();
        for(int i=1;i<n;i++){
            int u,v;
            scanf("%d %d",&u,&v);
            u++;
            v++;
            vect[u].pb(v);
            vect[v].pb(u);
        }

        data.build();

        int q;
        scanf("%d",&q);
        while(q--){

            string s;
            int x;
            cin>>s>>x;

            if(s=="O")data.update(x+1);
            else{

                double rez=data.query(x+1);
                rez/=(double)data.sz[x+1];
                printf("%.6lf\n",rez);
                ///cout<<rez<<endl;

            }
        }

    }

    return 0;
}
