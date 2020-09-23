/*

    idea: https://codeforces.com/blog/entry/59713

*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
typedef set<pii>::iterator mit;
const int maxn=2e5+10;
ll tree[maxn*4],lazya[maxn*4],lazyd[maxn*4];
set<pii>st[maxn];
int n,q;
ll mod=998244353;
void push(int x,int l,int mid,int r){

    if(lazyd[x]!=0){
        tree[x*2]=(tree[x*2]*lazyd[x])%mod;
        tree[x*2+1]=(tree[x*2+1]*lazyd[x])%mod;
        lazyd[x*2]=(lazyd[x*2]*lazyd[x])%mod;
        lazyd[x*2+1]=(lazyd[x*2+1]*lazyd[x])%mod;
        lazya[x*2]=(lazya[x*2]*lazyd[x])%mod;
        lazya[x*2+1]=(lazya[x*2+1]*lazyd[x])%mod;
    }

    tree[x*2]=(tree[x*2]+lazya[x]*(mid-l+1))%mod;
    tree[x*2+1]=(tree[x*2+1]+lazya[x]*(r-mid))%mod;
    lazya[x*2]=(lazya[x*2]+lazya[x])%mod;
    lazya[x*2+1]=(lazya[x*2+1]+lazya[x])%mod;

    lazya[x]=0;
    lazyd[x]=1;
}
void upa(int x,int l,int r,int lp,int rp){
    if(l>rp || r<lp)return;
    if(l>=lp && r<=rp){
        lazya[x]=(lazya[x]+1)%mod;
        tree[x]=(tree[x]+r-l+1)%mod;
        return;
    }
    int mid=(l+r)/2;
    push(x,l,mid,r);

    upa(x*2,l,mid,lp,rp);
    upa(x*2+1,mid+1,r,lp,rp);
    tree[x]=(tree[x*2]+tree[x*2+1])%mod;
}
void upd(int x,int l,int r,int lp,int rp){

    if(l>rp || r<lp)return;
    if(l>=lp && r<=rp){
        tree[x]=(tree[x]*2)%mod;
        lazyd[x]=(lazyd[x]*2)%mod;
        lazya[x]=(lazya[x]*2)%mod;
        return;
    }
    int mid=(l+r)/2;
    push(x,l,mid,r);

    upd(x*2,l,mid,lp,rp);
    upd(x*2+1,mid+1,r,lp,rp);
    tree[x]=(tree[x*2]+tree[x*2+1])%mod;
}
void update(int x,int l,int r){

    if(st[x].size()==0){
        st[x].insert({l,0});
        st[x].insert({r,1});
        upa(1,1,n,l,r);
        return;
    }

    mit it=st[x].lower_bound({l,-1});
    if(it==st[x].end()){
        st[x].insert({l,0});
        st[x].insert({r,1});
        upa(1,1,n,l,r);
        return;
    }
    if((*it).ss==1)it--;

    vector<pii>cand;

    for(;it!=st[x].end();it++,it++){
        if((*it).ff>r)break;

        int lp=(*it).ff;
        it++;
        int rp=(*it).ff;
        it--;
        cand.pb({lp,rp});
    }


    int retl=l;
    int retr=r;
    for(int i=0;i<cand.size();i++){
        upd(1,1,n,max(l,cand[i].ff),min(r,cand[i].ss));
        retl=min(retl,cand[i].ff);
        retr=max(retr,cand[i].ss);

        st[x].erase({cand[i].ff,0});
        st[x].erase({cand[i].ss,1});

    }

    st[x].insert({retl,0});
    st[x].insert({retr,1});

    if(cand.size()==0){
        upa(1,1,n,l,r);
        return;
    }

    if(l<cand[0].ff)upa(1,1,n,l,cand[0].ff-1);
    if(r>cand.back().ss)upa(1,1,n,cand.back().ss+1,r);

    for(int i=1;i<cand.size();i++)
        upa(1,1,n,cand[i-1].ss+1,cand[i].ff-1);

}
ll query(int x,int l,int r,int lp,int rp){
    if(l>rp || r<lp)return 0;
    if(l>=lp && r<=rp)return tree[x];
    int mid=(l+r)/2;
    push(x,l,mid,r);
    return (query(x*2,l,mid,lp,rp)+query(x*2+1,mid+1,r,lp,rp))%mod;
}
int main(){

    ///freopen("test2.txt","r",stdin);

    scanf("%d %d",&n,&q);

    while(q--){

        int tip;
        scanf("%d",&tip);

        if(tip==1){

            int l,r,x;
            scanf("%d %d %d",&l,&r,&x);

            update(x,l,r);

        }
        else{

            int l,r;
            scanf("%d %d",&l,&r);
            printf("%lld\n",query(1,1,n,l,r));
        }

    }


    return 0;
}
