#include<bits/stdc++.h>
#define ss second
#define ff first
#define pb push_back
#define lld long long
using namespace std;
typedef pair<int,int> pii;
typedef pair<lld,int> pli;
typedef set<pii>::iterator sit;
typedef map<int,int>::iterator mit;
const int maxn=1e5+10;
const int maxq=1e5+10;
pli ftree[maxn*4];
int lazy[maxn*4],mn[maxn*4],mx[maxn*4],n,q,a[maxn],br,cnt;
map<int,int>mapa;
set<pii>intervals[maxn*2];
struct query{
    int tip,l,r,val;
}qv[maxq];
pli operator +(pli a,pli b){
    return {a.ff+b.ff,a.ss+b.ss};
}
void update1(int x,int l,int r,int id,pli val){

    if(l>id || r<id)return;
    if(l==r){
        ftree[x]=ftree[x]+val;
        return;
    }
    int mid=(l+r)/2;

    if(id<=mid)update1(x*2,l,mid,id,val);
    else update1(x*2+1,mid+1,r,id,val);

    ftree[x]=ftree[x*2]+ftree[x*2+1];
}
pli query(int x,int l,int r,int ll,int rr){
    if(l>rr || r<ll)return {0ll,0};
    if(l>=ll && r<=rr)return ftree[x];
    int mid=(l+r)/2;
    return query(x*2,l,mid,ll,rr)+query(x*2+1,mid+1,r,ll,rr);
}
void push(int x){
    if(lazy[x]==0)return;

    mn[x*2]=lazy[x];
    mx[x*2]=lazy[x];
    mn[x*2+1]=lazy[x];
    mx[x*2+1]=lazy[x];
    lazy[x*2]=lazy[x];
    lazy[x*2+1]=lazy[x];

    lazy[x]=0;
}
void update2(int x,int l,int r,int ll,int rr,int val){

    if(l>rr || r<ll)return;
    if(l>=ll && r<=rr){
        lazy[x]=val;
        mn[x]=val;
        mx[x]=val;
        return;
    }
    int mid=(l+r)/2;
    push(x);

    update2(x*2,l,mid,ll,rr,val);
    update2(x*2+1,mid+1,r,ll,rr,val);

    mn[x]=min(mn[x*2],mn[x*2+1]);
    mx[x]=max(mx[x*2],mx[x*2+1]);
}
int get_prv(int color,int x){/// vraca udaljenost od proslog

    sit it=intervals[color].lower_bound({x,0});
    it--;

    if((*it).ss>=x)return 0;
    else return x-(*it).ss-1;
}
int get_nxt(int color,int x){

    sit it=intervals[color].lower_bound({x,0});

    if((*it).ff>x)it--;
    if((*it).ss<=x)it++;

    if((*it).ff<=x)return 0;
    else return (*it).ff-x-1;

}
void remove_interval(int l,int r,int val){


    /// skini
    int prv=get_prv(val,l);
    int nxt=get_nxt(val,r);
    update1(1,1,n,prv,{-prv,-1});
    update1(1,1,n,nxt,{-nxt,-1});
    ///dodaj
    update1(1,1,n,nxt+prv+r-l+1,{nxt+prv+r-l+1,1});

    vector<pii>pom;
    sit it=intervals[val].lower_bound({l,0});
    it--;

    while((*it).ff<=r){
        if((*it).ss<l){}
        else pom.pb(*it);
        it++;
    }

    for(int i=0;i<pom.size();i++){
        intervals[val].erase(pom[i]);

        if(pom[i].ff>=l && pom[i].ss<=r){}
        else{
            pii inter={pom[i].ff,l-1};
            if(inter.ff<=inter.ss)intervals[val].insert(inter);
            inter={r+1,pom[i].ss};
            if(inter.ff<=inter.ss)intervals[val].insert(inter);
        }
    }

    if(intervals[val].size()==2)cnt--;

}
void add_interval(int l,int r,int val){

    if(intervals[val].size()==2)cnt++;

    int prv=get_prv(val,l);
    int nxt=get_nxt(val,r);
    ///skini
    update1(1,1,n,nxt+prv+r-l+1,{-(nxt+prv+r-l+1),-1});
    ///dodaj
    update1(1,1,n,prv,{prv,1});
    update1(1,1,n,nxt,{nxt,1});

    intervals[val].insert({l,r});

}
void update3(int x,int l,int r,int ll,int rr,int val){

    if(l>rr || r<ll)return;
    if(l>=ll && r<=rr && mn[x]==mx[x]){
        remove_interval(l,r,mn[x]);
        add_interval(l,r,val);

        mx[x]=val;
        mn[x]=val;
        lazy[x]=val;
        return;
    }

    int mid=(l+r)/2;
    push(x);

    update3(x*2,l,mid,ll,rr,val);
    update3(x*2+1,mid+1,r,ll,rr,val);

    mn[x]=min(mn[x*2],mn[x*2+1]);
    mx[x]=max(mx[x*2],mx[x*2+1]);

}
int main(){

   ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    scanf("%d %d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        mapa[a[i]]=0;
    }

    for(int i=1;i<=q;i++){
        scanf("%d",&qv[i].tip);
        if(qv[i].tip==1){
            scanf("%d %d %d",&qv[i].l,&qv[i].r,&qv[i].val);
            mapa[qv[i].val]=0;
        }
        else scanf("%d",&qv[i].val);
    }

    for(mit it=mapa.begin();it!=mapa.end();it++){
        it->ss=++br;
        intervals[br].insert({0,0});
        intervals[br].insert({n+1,n+1});
    }

    for(int i=1;i<=n;i++)a[i]=mapa[a[i]];
    for(int i=1;i<=q;i++)
        if(qv[i].tip==1)qv[i].val=mapa[qv[i].val];


    for(int i=1;i<=n;i++){
        if(intervals[a[i]].size()==2)cnt++;
        update1(1,1,n,get_prv(a[i],i),{get_prv(a[i],i),1});
        intervals[a[i]].insert({i,i});
        update2(1,1,n,i,i,a[i]);

    }

    for(int i=1;i<=br;i++){
        if(intervals[i].size()==2)continue;
        update1(1,1,n,get_prv(i,n+1),{get_prv(i,n+1),1});
    }

    for(int i=1;i<=q;i++){

        if(qv[i].tip==1)update3(1,1,n,qv[i].l,qv[i].r,qv[i].val);
        else{
            pli pom=query(1,1,n,qv[i].val,n-1);
            printf("%lld\n",(lld)cnt*((lld)n-(lld)qv[i].val+(lld)1)-(pom.ff-(lld)pom.ss*((lld)qv[i].val-1)));
        }
    }

return 0;
}
