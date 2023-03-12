/*

    idea:https://codeforces.com/blog/entry/54233

*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
typedef set<int>::iterator sit;
const int maxn=1e5+10;
vector<int>vect[maxn*4];
vector<ll>tree[maxn*4];
int prv[maxn],nxt[maxn],ppos[maxn],n,a[maxn],qq,b[maxn];
struct ss{
    int tip,a,b;
}q[maxn];
set<int>st[maxn];
void reset_dp(){

    memset(prv,0,sizeof(prv));
    fill(nxt,nxt+n+1,n+1);
    memset(ppos,0,sizeof(ppos));

    for(int i=1;i<=n;i++){
        a[i]=b[i];
        if(ppos[a[i]]!=0)nxt[ppos[a[i]]]=i;
        prv[i]=ppos[a[i]];
        ppos[a[i]]=i;

        st[i].clear();
        st[i].insert(0);
        st[i].insert(n+1);
    }
    for(int i=1;i<=n;i++){
        st[a[i]].insert(i);
    }
}
void up1(int x,int l,int r,int lp,int rp,int val){

    if(l>rp || r<lp)return;
    vect[x].pb(val);
    if(l>=lp && r<=rp)return;
    int mid=(l+r)/2;

    up1(x*2,l,mid,lp,rp,val);
    up1(x*2+1,mid+1,r,lp,rp,val);
}
void up3(vector<ll> &tree,int id,ll val){
    for(;id<tree.size();id+=(id&(-id)))
        tree[id]+=val;
}
ll q3(vector<ll> &tree,int id){
    ll ret=0;
    for(;id>0;id-=(id&(-id)))
        ret+=tree[id];
    return ret;
}
void up2(int x,int l,int r,int id1,int id2,ll val){

    if(l>id1 || r<id1)return;

    int pos=lower_bound(vect[x].begin(),vect[x].end(),id2)-vect[x].begin();
    pos++;
    up3(tree[x],pos,val);

    if(l==r)return;

    int mid=(l+r)/2;

    up2(x*2,l,mid,id1,id2,val);
    up2(x*2+1,mid+1,r,id1,id2,val);
}
ll query(int x,int l,int r,int lp,int rp,int id){

    if(l>rp || r<lp)return 0;
    if(l>=lp && r<=rp)
        return q3(tree[x],tree[x].size()-1)-q3(tree[x],lower_bound(vect[x].begin(),vect[x].end(),id)-vect[x].begin()+1);


    int mid=(l+r)/2;
    return query(x*2,l,mid,lp,rp,id)+query(x*2+1,mid+1,r,lp,rp,id);
}
int main(){

    ///freopen("test2.txt","r",stdin);

    scanf("%d %d",&n,&qq);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        b[i]=a[i];
    }

    reset_dp();

    for(int i=1;i<=n;i++){
        up1(1,1,n,i,i,prv[i]);
    }


    for(int i=1;i<=qq;i++){
        scanf("%d %d %d",&q[i].tip,&q[i].a,&q[i].b);

        if(q[i].tip==1){
            int id=q[i].a;

            nxt[prv[id]]=nxt[id];
            prv[nxt[id]]=prv[id];

            up1(1,1,n,nxt[id],nxt[id],prv[nxt[id]]);
            up1(1,1,n,nxt[id],nxt[id],id);
            up1(1,1,n,id,id,prv[id]);
            st[a[q[i].a]].erase(id);

            a[q[i].a]=q[i].b;

            sit it=(st[q[i].b].insert(id)).ff;
            it++;
            int nn=*it;
            it--;it--;

            nxt[*it]=id;
            prv[nn]=id;

            up1(1,1,n,nn,nn,id);
            up1(1,1,n,nn,nn,*it);
            up1(1,1,n,id,id,*it);
            nxt[id]=nn;
            prv[id]=*it;
            up1(1,1,n,id,id,prv[id]);
        }
        else up1(1,1,n,q[i].a,q[i].b,q[i].a-1);
    }

    for(int i=0;i<maxn*4;i++){
        sort(vect[i].begin(),vect[i].end());
        vect[i].resize(unique(vect[i].begin(),vect[i].end())-vect[i].begin());
        tree[i].resize(vect[i].size()+1);
    }

    reset_dp();
    for(int i=1;i<=n;i++)
        if(prv[i]!=0)up2(1,1,n,i,prv[i],i-prv[i]);

    for(int i=1;i<=qq;i++){

        if(q[i].tip==1){

            int id=q[i].a;

            nxt[prv[id]]=nxt[id];
            prv[nxt[id]]=prv[id];
            up2(1,1,n,nxt[id],id,-(nxt[id]-id));
            if(prv[id]!=0)up2(1,1,n,nxt[id],prv[nxt[id]],nxt[id]-prv[id]);
            if(prv[id]!=0)up2(1,1,n,id,prv[id],-(id-prv[id]));
            st[a[q[i].a]].erase(id);


            a[q[i].a]=q[i].b;

            sit it=(st[q[i].b].insert(id)).ff;
            it++;
            int nn=*it;
            it--;it--;

            nxt[*it]=id;
            prv[nn]=id;
            nxt[id]=nn;
            prv[id]=*it;

            if(*it!=0)up2(1,1,n,nn,*it,-nn+*it);
            up2(1,1,n,nn,id,nn-id);
            if(*it!=0)up2(1,1,n,id,*it,id-*it);
        }
        else printf("%lld\n",query(1,1,n,q[i].a,q[i].b,q[i].a-1));
    }


    return 0;
}
